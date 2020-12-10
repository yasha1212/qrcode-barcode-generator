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

}
