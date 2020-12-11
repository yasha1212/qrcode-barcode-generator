#include "framework.h"
#include "pch.h"
#include <math.h>
#include "QrcodeConstants.h"
#include "Qrcode.h"

using namespace std;

typedef vector<bool> Bits;
typedef vector<unsigned char> Bytes;
typedef vector<vector<unsigned char>> BlocksOfBytes;

int ApplyMask(int x, int y);
int GetVersion(int bitsAmount);
bool IsValidInput(string input);
Bits EncodeString(string input);
void AddServiceFields(Bits& data, int version, int charAmount);
void FillSequence(Bits& data, int version);
Bytes BitsToBytes(Bits data);
BlocksOfBytes GetDataBlocks(Bits data, int version);
BlocksOfBytes GetCorrectionBlocks(BlocksOfBytes blocks, int version);
Bytes PrepareArray(Bytes block, int correctionBytesAmount);
unsigned char GetFirstByte(Bytes& bytes);
Bytes Copy(Bytes source, int amount);
Bytes UniteBlocks(BlocksOfBytes data, BlocksOfBytes correction);
Qrcode::QrCode BuildQrcode(Bytes data, int version);
Qrcode::QrCode Initialize(int version);
void AddSearchElements(Qrcode::QrCode& matrix);
void AddAlignmentPatterns(Qrcode::QrCode& matrix, int version);
void AddSynchronizationLines(Qrcode::QrCode& matrix);
void AddVersionCode(Qrcode::QrCode& matrix, int version);
void AddMaskCode(Qrcode::QrCode& matrix);
vector<vector<int>> GetCoordinates(vector<int> nodes);

namespace Qrcode 
{
    int Generate(string input, QrCode& qrcode) 
    {
        if (!IsValidInput(input)) 
        {
            return 2;
        }

        Bits data = EncodeString(input);
        int version = GetVersion(data.size());

        if (version == 0) 
        {
            return 1;
        }

        AddServiceFields(data, version, input.length());
        FillSequence(data, version);

        BlocksOfBytes dataBlocks = GetDataBlocks(data, version);
        BlocksOfBytes correctionBlocks = GetCorrectionBlocks(dataBlocks, version);

        Bytes sequence = UniteBlocks(dataBlocks, correctionBlocks);

        qrcode.clear();

        qrcode = BuildQrcode(sequence, version);

        return 0;
    }
}

bool IsValidInput(string input) 
{
    bool result = true;

    for (auto ch : input) 
    {
        if (CHARACTERS_CODES.find(ch) == CHARACTERS_CODES.end()) 
        {
            result = false;
            break;
        }
    }

    return result;
}

int ApplyMask(int x, int y) 
{
    return (x / 3 + y / 2) % 2;
}

Bits EncodeString(string input) 
{
    Bits result;

    int sum = 0;

    size_t stringEvenLength = input.length() % 2 == 0 ? input.length() : input.length() - 1;

    for (int i = 0; i < stringEvenLength; i++) 
    {
        if (i % 2 == 0) 
        {
            sum += CHARACTERS_CODES.at(input[i]) * 45;
        }
        else 
        {
            sum += CHARACTERS_CODES.at(input[i]);

            for (int j = 10; j >= 0; j--) // copy last 11 bits
            {
                bool bit = sum & (1 << j);
                result.push_back(bit);
            }

            sum = 0;
        }
    }

    if (input.length() > stringEvenLength) 
    {
        sum = CHARACTERS_CODES.at(input[stringEvenLength]);

        for (int i = 5; i >= 0; i--) // copy last 6 bits
        {
            bool bit = sum & (1 << i);
            result.push_back(bit);
        }
    }

    return result;
}

int GetVersion(int bitsAmount) 
{
    int version = 0;

    for (int i = 1; i <= VERSION_PARAMETERS.size(); i++) 
    {
        if (VERSION_PARAMETERS.at(i)[MAX_BITS] >= bitsAmount + CODING_TYPE_FIELD.size() + VERSION_PARAMETERS.at(i)[DATA_FIELD_LENGTH]) 
        {
            version = i;
            break;
        }
    }

    return version;
}

void AddServiceFields(Bits& data, int version, int charAmount) 
{
    Bits result;

    for (auto bit : CODING_TYPE_FIELD) 
    {
        result.push_back(bit);
    }

    for (int i = VERSION_PARAMETERS.at(version)[DATA_FIELD_LENGTH] - 1; i >= 0; i--) // copy predefined for version amount of bits
    {
        bool bit = charAmount & (1 << i);
        result.push_back(bit);
    }

    for (auto bit : data) 
    {
        result.push_back(bit);
    }

    data.clear();

    for (auto bit : result) 
    {
        data.push_back(bit);
    }
}

void FillSequence(Bits& data, int version) 
{
    const Bits PADDING_BYTE_1 {1,1,1,0,1,1,0,0};
    const Bits PADDING_BYTE_2 {0,0,0,1,0,0,0,1};

    int paddingBitsAmount = 8 - (data.size() % 8);

    for (int i = 0; i < paddingBitsAmount; i++) 
    {
        data.push_back(0);
    }

    bool iterator = false;

    while (data.size() != VERSION_PARAMETERS.at(version)[MAX_BITS]) 
    {
        Bits paddingByte = iterator == false ? PADDING_BYTE_1 : PADDING_BYTE_2;

        for (auto bit : paddingByte) 
        {
            data.push_back(bit);
        }

        iterator = !iterator;
    }
}

Bytes BitsToBytes(Bits data)
{
    Bytes result;

    for (int i = 0; i < data.size(); i += 8) 
    {
        unsigned char byte = 0;

        for (int j = 0; j < 8; j++) 
        {
            byte += data[i + j] * (pow(2, 7 - j));
        }

        result.push_back(byte);
    }

    return result;
}

BlocksOfBytes GetDataBlocks(Bits data, int version) 
{
    Bytes dataBytes = BitsToBytes(data);

    int blocksAmount = VERSION_PARAMETERS.at(version)[BLOCKS_AMOUNT];

    BlocksOfBytes result;

    int bytesInBlock = dataBytes.size() / blocksAmount;
    int extendedBlocksCount = dataBytes.size() % blocksAmount;
    int dataIndex = 0;

    for (int i = 0; i < blocksAmount; i++) 
    {
        Bytes bytes;

        int extraByte = i < blocksAmount - extendedBlocksCount ? 0 : 1;

        for (int j = 0; j < bytesInBlock + extraByte; j++) 
        {
            bytes.push_back(dataBytes[dataIndex]);
            dataIndex++;
        }

        result.push_back(bytes);
    }

    return result;
}

BlocksOfBytes GetCorrectionBlocks(BlocksOfBytes blocks, int version)
{
    int correctionBytesAmount = VERSION_PARAMETERS.at(version)[CORRECTION_BYTES_AMOUNT];
    Bytes polynomial = POLYNOMIALS.at(correctionBytesAmount);

    BlocksOfBytes correctionBytesBlocks;

    for (auto block : blocks) 
    {
        Bytes temp = PrepareArray(block, correctionBytesAmount);

        for (int i = 0; i < block.size(); i++) 
        {
            unsigned char A = GetFirstByte(temp);
            
            if (A == 0) 
            {
                continue;
            }

            unsigned char B = GALOIS_TABLE.at(A)[REVERSE];

            for (int j = 0; j < correctionBytesAmount; j++) 
            {
                unsigned char C = (polynomial[j] + B) % 255;

                temp[j] ^= GALOIS_TABLE.at(C)[DEFAULT];
            }
        }

        Bytes correctionBlock = Copy(temp, correctionBytesAmount);

        correctionBytesBlocks.push_back(correctionBlock);
    }

    return correctionBytesBlocks;
}

Bytes PrepareArray(Bytes block, int correctionBytesAmount) 
{
    Bytes result;

    for (auto byte : block) 
    {
        result.push_back(byte);
    }

    while (result.size() < correctionBytesAmount) 
    {
        result.push_back(0);
    }

    return result;
}

unsigned char GetFirstByte(Bytes& bytes) 
{
    unsigned char firstByte = bytes[0];

    bytes.erase(bytes.begin());
    bytes.push_back(0);

    return firstByte;
}

Bytes Copy(Bytes source, int amount) 
{
    Bytes result;

    for (int i = 0; i < amount; i++) 
    {
        result.push_back(source[i]);
    }

    return result;
}

Bytes UniteBlocks(BlocksOfBytes data, BlocksOfBytes correction) 
{
    int dataBytesInBlock = data[data.size() - 1].size();
    int correctionBytesInBlock = correction[0].size();

    Bytes result;

    for (int i = 0; i < dataBytesInBlock; i++) 
    {
        for (int j = 0; j < data.size(); j++) 
        {
            if (i > data[j].size() - 1) 
            {
                continue;
            }

            result.push_back(data[j][i]);
        }
    }

    for (int i = 0; i < correctionBytesInBlock; i++) 
    {
        for (int j = 0; j < correction.size(); j++) 
        {
            result.push_back(correction[j][i]);
        }
    }

    return result;
}

Qrcode::QrCode BuildQrcode(Bytes data, int version) 
{
    Qrcode::QrCode matrix = Initialize(version);
    AddSearchElements(matrix);

    if (version > 1) 
    {
        AddAlignmentPatterns(matrix, version);
    }

    AddSynchronizationLines(matrix);

    if (version > 6) 
    {
        AddVersionCode(matrix, version);
    }

    AddMaskCode(matrix);

    return matrix;
}

Qrcode::QrCode Initialize(int version) 
{
    int valueSize;

    if (version == 1) 
    {
        valueSize = 21;
    }
    else 
    {
        vector<int> nodesCoords = ALIGNMENT_PATTERNS.at(version);
        valueSize = nodesCoords[nodesCoords.size() - 1] + 7;
    }

    int realSize = valueSize + 8;

    Qrcode::QrCode result;

    for (int i = 0; i < realSize; i++) 
    {
        vector<Qrcode::Module> temp;

        for (int j = 0; j < realSize; j++) 
        {
            Qrcode::Module tempModule;
            tempModule.isFree = true;
            tempModule.value = 0;

            temp.push_back(tempModule);
        }

        result.push_back(temp);
    }

    return result;
}

void AddSearchElements(Qrcode::QrCode& matrix) 
{
    const vector<Bits> TOP_LEFT
    {
        {1,1,1,1,1,1,1,0},
        {1,0,0,0,0,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,0,0,0,0,1,0},
        {1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0}
    };
    const vector<Bits> BOTTOM_LEFT
    {
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,0},
        {1,0,0,0,0,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,1,1,1,0,1,0},
        {1,0,0,0,0,0,1,0},
        {1,1,1,1,1,1,1,0}
    };
    const vector<Bits> TOP_RIGHT
    {
        {0,1,1,1,1,1,1,1},
        {0,1,0,0,0,0,0,1},
        {0,1,0,1,1,1,0,1},
        {0,1,0,1,1,1,0,1},
        {0,1,0,1,1,1,0,1},
        {0,1,0,0,0,0,0,1},
        {0,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
    };

    for (int i = 0; i < TOP_LEFT.size(); i++) 
    {
        for (int j = 0; j < TOP_LEFT.size(); j++) 
        {
            matrix[BORDER_PADDING + i][BORDER_PADDING + j].value = TOP_LEFT[i][j];
            matrix[BORDER_PADDING + i][BORDER_PADDING + j].isFree = false;
        }
    }

    for (int i = 0; i < TOP_RIGHT.size(); i++)
    {
        for (int j = 0; j < TOP_RIGHT.size(); j++)
        {
            int currentPaddingX = matrix.size() - BORDER_PADDING - TOP_RIGHT.size();

            matrix[BORDER_PADDING + i][currentPaddingX + j].value = TOP_RIGHT[i][j];
            matrix[BORDER_PADDING + i][currentPaddingX + j].isFree = false;
        }
    }

    for (int i = 0; i < BOTTOM_LEFT.size(); i++)
    {
        for (int j = 0; j < BOTTOM_LEFT.size(); j++)
        {
            int currentPaddingY = matrix.size() - BORDER_PADDING - BOTTOM_LEFT.size();

            matrix[currentPaddingY + i][BORDER_PADDING + j].value = BOTTOM_LEFT[i][j];
            matrix[currentPaddingY + i][BORDER_PADDING + j].isFree = false;
        }
    }
}

void AddAlignmentPatterns(Qrcode::QrCode& matrix, int version) 
{
    const vector<Bits> PATTERN
    {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    };

    vector<vector<int>> coordinates = GetCoordinates(ALIGNMENT_PATTERNS.at(version));

    for (auto pair : coordinates) 
    {
        int startX = BORDER_PADDING + pair[1] - 2;
        int startY = BORDER_PADDING + pair[0] - 2;

        for (int i = 0; i < PATTERN.size(); i++) 
        {
            for (int j = 0; j < PATTERN.size(); j++)
            {
                matrix[startY + i][startX + j].value = PATTERN[i][j];
                matrix[startY + i][startX + j].isFree = false;
            }
        }
    }
}

vector<vector<int>> GetCoordinates(vector<int> nodes) 
{
    vector<vector<int>> coordinates;

    for (int i = 0; i < nodes.size(); i++) 
    {
        for (int j = 0; j < nodes.size(); j++) 
        {
            if (((j == (nodes.size() - 1) && i == 0) ||
                (j == 0 && i == 0) ||
                (j == 0 && i == (nodes.size() - 1))) && (nodes.size() > 1)) 
            {
                continue;
            }

            vector<int> pair = { nodes[j], nodes[i] };
            coordinates.push_back(pair);
        }
    }

    return coordinates;
}

void AddSynchronizationLines(Qrcode::QrCode& matrix) 
{
    const int START_COORD = 10;

    int length = matrix.size() - BORDER_PADDING - 8 - START_COORD;

    bool bitValue = true;

    for (int i = 0; i < length; i++) 
    {
        matrix[START_COORD + i][START_COORD].value = bitValue;
        matrix[START_COORD][START_COORD + i].value = bitValue;

        matrix[START_COORD + i][START_COORD].isFree = false;
        matrix[START_COORD][START_COORD + i].isFree = false;

        bitValue = !bitValue;
    }
}

void AddVersionCode(Qrcode::QrCode& matrix, int version) 
{
    const int WIDTH = 6;
    const int HEIGHT = 3;

    int startCoordY = matrix.size() - BORDER_PADDING - 11;
    int startCoordX = 4;

    Bits versionCode = VERSION_CODES.at(version);

    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
            matrix[startCoordY + i][startCoordX + j].value = versionCode[i * WIDTH + j];
            matrix[startCoordX + j][startCoordY + i].value = versionCode[i * WIDTH + j];

            matrix[startCoordY + i][startCoordX + j].isFree = false;
            matrix[startCoordX + j][startCoordY + i].isFree = false;
        }
    }
}

void AddMaskCode(Qrcode::QrCode& matrix) 
{
    int blStartCoordX = 12;
    int blStartCoordY = matrix.size() - BORDER_PADDING - 1;
    
    int trStartCoordX = matrix.size() - BORDER_PADDING - 8;
    int trStartCoordY = 12;

    for (int i = 0; i < 8; i++) // add mask code from bottom-left to top-right
    {
        if (i == 7) 
        {
            matrix[blStartCoordY - i][blStartCoordX].value = 1;
        }
        else 
        {
            matrix[blStartCoordY - i][blStartCoordX].value = MASK_CODE[i];
        }
        
        matrix[trStartCoordY][trStartCoordX + i].value = MASK_CODE[i + 7];

        matrix[trStartCoordY][trStartCoordX + i].isFree = false;
        matrix[blStartCoordY - i][blStartCoordX].isFree = false;
    }

    int tlCoordX = 4;
    int tlCoordY = 12;

    for (int i = 0; i < MASK_CODE.size(); i++) // add mask code on the top-left
    {
        matrix[tlCoordY][tlCoordX].value = MASK_CODE[i];
        matrix[tlCoordY][tlCoordX].isFree = false;

        if (i < 7) 
        {
            tlCoordX++;

            if (!matrix[tlCoordY][tlCoordX].isFree)
            {
                tlCoordX++;
            }
        }
        else 
        {
            tlCoordY--;

            if (!matrix[tlCoordY][tlCoordX].isFree)
            {
                tlCoordY--;
            }
        }
    }
}
