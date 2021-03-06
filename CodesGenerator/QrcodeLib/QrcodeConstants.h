#pragma once
#include <unordered_map>

const int BORDER_PADDING = 4;

const std::unordered_map<char, int> CHARACTERS_CODES // Character, Code
{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15},
    {'G', 16},
    {'H', 17},
    {'I', 18},
    {'J', 19},
    {'K', 20},
    {'L', 21},
    {'M', 22},
    {'N', 23},
    {'O', 24},
    {'P', 25},
    {'Q', 26},
    {'R', 27},
    {'S', 28},
    {'T', 29},
    {'U', 30},
    {'V', 31},
    {'W', 32},
    {'X', 33},
    {'Y', 34},
    {'Z', 35},
    {' ', 36},
    {'$', 37},
    {'%', 38},
    {'*', 39},
    {'+', 40},
    {'-', 41},
    {'.', 42},
    {'/', 43},
    {':', 44},
};

const int MAX_BITS = 0;
const int BLOCKS_AMOUNT = 1;
const int CORRECTION_BYTES_AMOUNT = 2;
const int DATA_FIELD_LENGTH = 3;

const std::unordered_map<int, std::vector<int>> VERSION_PARAMETERS // Version, {Maximum amount of bits, Blocks amount, Correction bytes amount, Data amount field length}
{
    {1, {128, 1, 10, 8} },
    {2, {224, 1, 16, 8} },
    {3, {352, 1, 26, 8} },
    {4, {512, 2, 18, 8} },
    {5, {688, 2, 24, 8} },
    {6, {864, 4, 16, 8} },
    {7, {992, 4, 18, 8} },
    {8, {1232, 4, 22, 8} },
    {9, {1456, 5, 22, 8} },
    {10, {1728, 5, 26, 16} },
    {11, {2032, 5, 30, 16} },
    {12, {2320, 8, 22, 16} },
    {13, {2672, 9, 22, 16} },
    {14, {2920, 9, 24, 16} },
    {15, {3320, 10, 24, 16} },
    {16, {3624, 10, 28, 16} },
    {17, {4056, 11, 28, 16} },
    {18, {4504, 13, 26, 16} },
    {19, {5016, 14, 26, 16} },
    {20, {5352, 16, 26, 16} },
};

const std::vector<bool> CODING_TYPE_FIELD
{
    0,1,0,0
};

const std::unordered_map<int, std::vector<unsigned char>> POLYNOMIALS // Correction bytes amount, Generating polynomial
{
    {7, {87, 229, 146, 149, 238, 102, 21} },
    {10, {251, 67, 46, 61, 118, 70, 64, 94, 32, 45} },
    {13, {74, 152, 176, 100, 86, 100, 106, 104, 130, 218, 206, 140, 78} },
    {15, {8, 183, 61, 91, 202, 37, 51, 58, 58, 237, 140, 124, 5, 99, 105} },
    {16, {120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120} },
    {17, {43, 139, 206, 78, 43, 239, 123, 206, 214, 147, 24, 99, 150, 39, 243, 163, 136} },
    {18, {215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153} },
    {20, {17, 60, 79, 50, 61, 163, 26, 187, 202, 180, 221, 225, 83, 239, 156, 164, 212, 212, 188, 190} },
    {22, {210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231} },
    {24, {229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0, 117, 232, 87, 96, 227, 21} },
    {26, {173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13, 102, 48, 227, 153, 145, 218, 70} },
    {28, {168, 223, 200, 104, 224, 234, 108, 180, 110, 190, 195, 147, 205, 27, 232, 201, 21, 43, 245, 87, 42, 195, 212, 119, 242, 37, 9, 123} },
    {30, {41, 173, 145, 152, 216, 31, 179, 182, 50, 48, 110, 86, 239, 96, 222, 125, 42, 173, 226, 193, 224, 130, 156, 37, 251, 216, 238, 40, 192, 180} },
};

const int DEFAULT = 0;
const int REVERSE = 1;

const std::unordered_map<int, std::vector<int>> GALOIS_TABLE // Number, {Default, Reverse}
{
    { 0, {1, 0} },
    { 1, {2, 0} },
    { 2, {4, 1} },
    { 3, {8, 25} },
    { 4, {16, 2} },
    { 5, {32, 50} },
    { 6, {64, 26} },
    { 7, {128, 198} },
    { 8, {29, 3} },
    { 9, {58, 223} },
    { 10, {116, 51} },
    { 11, {232, 238} },
    { 12, {205, 27} },
    { 13, {135, 104} },
    { 14, {19, 199} },
    { 15, {38, 75} },
    { 16, {76, 4} },
    { 17, {152, 100} },
    { 18, {45, 224} },
    { 19, {90, 14} },
    { 20, {180, 52} },
    { 21, {117, 141} },
    { 22, {234, 239} },
    { 23, {201, 129} },
    { 24, {143, 28} },
    { 25, {3, 193} },
    { 26, {6, 105} },
    { 27, {12, 248} },
    { 28, {24, 200} },
    { 29, {48, 8} },
    { 30, {96, 76} },
    { 31, {192, 113} },
    { 32, {157, 5} },
    { 33, {39, 138} },
    { 34, {78, 101} },
    { 35, {156, 47} },
    { 36, {37, 225} },
    { 37, {74, 36} },
    { 38, {148, 15} },
    { 39, {53, 33} },
    { 40, {106, 53} },
    { 41, {212, 147} },
    { 42, {181, 142} },
    { 43, {119, 218} },
    { 44, {238, 240} },
    { 45, {193, 18} },
    { 46, {159, 130} },
    { 47, {35, 69} },
    { 48, {70, 29} },
    { 49, {140, 181} },
    { 50, {5, 194} },
    { 51, {10, 125} },
    { 52, {20, 106} },
    { 53, {40, 39} },
    { 54, {80, 249} },
    { 55, {160, 185} },
    { 56, {93, 201} },
    { 57, {186, 154} },
    { 58, {105, 9} },
    { 59, {210, 120} },
    { 60, {185, 77} },
    { 61, {111, 228} },
    { 62, {222, 114} },
    { 63, {161, 166} },
    { 64, {95, 6} },
    { 65, {190, 191} },
    { 66, {97, 139} },
    { 67, {194, 98} },
    { 68, {153, 102} },
    { 69, {47, 221} },
    { 70, {94, 48} },
    { 71, {188, 253} },
    { 72, {101, 226} },
    { 73, {202, 152} },
    { 74, {137, 37} },
    { 75, {15, 179} },
    { 76, {30, 16} },
    { 77, {60, 145} },
    { 78, {120, 34} },
    { 79, {240, 136} },
    { 80, {253, 54} },
    { 81, {231, 208} },
    { 82, {211, 148} },
    { 83, {187, 206} },
    { 84, {107, 143} },
    { 85, {214, 150} },
    { 86, {177, 219} },
    { 87, {127, 189} },
    { 88, {254, 241} },
    { 89, {225, 210} },
    { 90, {223, 19} },
    { 91, {163, 92} },
    { 92, {91, 131} },
    { 93, {182, 56} },
    { 94, {113, 70} },
    { 95, {226, 64} },
    { 96, {217, 30} },
    { 97, {175, 66} },
    { 98, {67, 182} },
    { 99, {134, 163} },
    { 100, {17, 195} },
    { 101, {34, 72} },
    { 102, {68, 126} },
    { 103, {136, 110} },
    { 104, {13, 107} },
    { 105, {26, 58} },
    { 106, {52, 40} },
    { 107, {104, 84} },
    { 108, {208, 250} },
    { 109, {189, 133} },
    { 110, {103, 186} },
    { 111, {206, 61} },
    { 112, {129, 202} },
    { 113, {31, 94} },
    { 114, {62, 155} },
    { 115, {124, 159} },
    { 116, {248, 10} },
    { 117, {237, 21} },
    { 118, {199, 121} },
    { 119, {147, 43} },
    { 120, {59, 78} },
    { 121, {118, 212} },
    { 122, {236, 229} },
    { 123, {197, 172} },
    { 124, {151, 115} },
    { 125, {51, 243} },
    { 126, {102, 167} },
    { 127, {204, 87} },
    { 128, {133, 7} },
    { 129, {23, 112} },
    { 130, {46, 192} },
    { 131, {92, 247} },
    { 132, {184, 140} },
    { 133, {109, 128} },
    { 134, {218, 99} },
    { 135, {169, 13} },
    { 136, {79, 103} },
    { 137, {158, 74} },
    { 138, {33, 222} },
    { 139, {66, 237} },
    { 140, {132, 49} },
    { 141, {21, 197} },
    { 142, {42, 254} },
    { 143, {84, 24} },
    { 144, {168, 227} },
    { 145, {77, 165} },
    { 146, {154, 153} },
    { 147, {41, 119} },
    { 148, {82, 38} },
    { 149, {164, 184} },
    { 150, {85, 180} },
    { 151, {170, 124} },
    { 152, {73, 17} },
    { 153, {146, 68} },
    { 154, {57, 146} },
    { 155, {114, 217} },
    { 156, {228, 35} },
    { 157, {213, 32} },
    { 158, {183, 137} },
    { 159, {115, 46} },
    { 160, {230, 55} },
    { 161, {209, 63} },
    { 162, {191, 209} },
    { 163, {99, 91} },
    { 164, {198, 149} },
    { 165, {145, 188} },
    { 166, {63, 207} },
    { 167, {126, 205} },
    { 168, {252, 144} },
    { 169, {229, 135} },
    { 170, {215, 151} },
    { 171, {179, 178} },
    { 172, {123, 220} },
    { 173, {246, 252} },
    { 174, {241, 190} },
    { 175, {255, 97} },
    { 176, {227, 242} },
    { 177, {219, 86} },
    { 178, {171, 211} },
    { 179, {75, 171} },
    { 180, {150, 20} },
    { 181, {49, 42} },
    { 182, {98, 93} },
    { 183, {196, 158} },
    { 184, {149, 132} },
    { 185, {55, 60} },
    { 186, {110, 57} },
    { 187, {220, 83} },
    { 188, {165, 71} },
    { 189, {87, 109} },
    { 190, {174, 65} },
    { 191, {65, 162} },
    { 192, {130, 31} },
    { 193, {25, 45} },
    { 194, {50, 67} },
    { 195, {100, 216} },
    { 196, {200, 183} },
    { 197, {141, 123} },
    { 198, {7, 164} },
    { 199, {14, 118} },
    { 200, {28, 196} },
    { 201, {56, 23} },
    { 202, {112, 73} },
    { 203, {224, 236} },
    { 204, {221, 127} },
    { 205, {167, 12} },
    { 206, {83, 111} },
    { 207, {166, 246} },
    { 208, {81, 108} },
    { 209, {162, 161} },
    { 210, {89, 59} },
    { 211, {178, 82} },
    { 212, {121, 41} },
    { 213, {242, 157} },
    { 214, {249, 85} },
    { 215, {239, 170} },
    { 216, {195, 251} },
    { 217, {155, 96} },
    { 218, {43, 134} },
    { 219, {86, 177} },
    { 220, {172, 187} },
    { 221, {69, 204} },
    { 222, {138, 62} },
    { 223, {9, 90} },
    { 224, {18, 203} },
    { 225, {36, 89} },
    { 226, {72, 95} },
    { 227, {144, 176} },
    { 228, {61, 156} },
    { 229, {122, 169} },
    { 230, {244, 160} },
    { 231, {245, 81} },
    { 232, {247, 11} },
    { 233, {243, 245} },
    { 234, {251, 22} },
    { 235, {235, 235} },
    { 236, {203, 122} },
    { 237, {139, 117} },
    { 238, {11, 44} },
    { 239, {22, 215} },
    { 240, {44, 79} },
    { 241, {88, 174} },
    { 242, {176, 213} },
    { 243, {125, 233} },
    { 244, {250, 230} },
    { 245, {233, 231} },
    { 246, {207, 173} },
    { 247, {131, 232} },
    { 248, {27, 116} },
    { 249, {54, 214} },
    { 250, {108, 244} },
    { 251, {216, 234} },
    { 252, {173, 168} },
    { 253, {71, 80} },
    { 254, {142, 88} },
    { 255, {1, 175} }
};

const std::unordered_map<int, std::vector<int>> ALIGNMENT_PATTERNS // Version, Coordinate number
{
    {2, {18} },
    {3, {22} },
    {4, {26} },
    {5, {30} },
    {6, {34} },
    {7, {6, 22, 38} },
    {8, {6, 24, 42} },
    {9, {6, 26, 46} },
    {10, {6, 28, 50} },
    {11, {6, 30, 54} },
    {12, {6, 32, 58} },
    {13, {6, 34, 62} },
    {14, {6, 26, 46, 66} },
    {15, {6, 26, 48, 70} },
    {16, {6, 26, 50, 74} },
    {17, {6, 30, 54, 78} },
    {18, {6, 30, 56, 82} },
    {19, {6, 30, 58, 86} },
    {20, {6, 34, 62, 90} }
};

const std::unordered_map<int, std::vector<bool>> VERSION_CODES // Version, Code (starts from 7-th version)
{
    {7, {0,0,0,0,1,0, 0,1,1,1,1,0, 1,0,0,1,1,0} },
    {8, {0,1,0,0,0,1, 0,1,1,1,0,0, 1,1,1,0,0,0} },
    {9, {1,1,0,1,1,1, 0,1,1,0,0,0, 0,0,0,1,0,0} },
    {10, {1,0,1,0,0,1, 1,1,1,1,1,0, 0,0,0,0,0,0} },
    {11, {0,0,1,1,1,1, 1,1,1,0,1,0, 1,1,1,1,0,0} },
    {12, {0,0,1,1,0,1, 1,0,0,1,0,0, 0,1,1,0,1,0} },
    {13, {1,0,1,0,1,1, 1,0,0,0,0,0, 1,0,0,1,1,0} },
    {14, {1,1,0,1,0,1, 0,0,0,1,1,0, 1,0,0,0,1,0} },
    {15, {0,1,0,0,1,1, 0,0,0,0,1,0, 0,1,1,1,1,0} },
    {16, {0,1,1,1,0,0, 0,1,0,0,0,1, 0,1,1,1,0,0} },
    {17, {1,1,1,0,1,0, 0,1,0,1,0,1, 1,0,0,0,0,0} },
    {18, {1,0,0,1,0,0, 1,1,0,0,1,1, 1,0,0,1,0,0} },
    {19, {0,0,0,0,1,0, 1,1,0,1,1,1, 0,1,1,0,0,0} },
    {20, {0,0,0,0,0,0, 1,0,1,0,0,1, 1,1,1,1,1,0} },
};

const std::vector<bool> MASK_CODE
{
    1,0,1,1,0,1,1,0,1,0,0,1,0,1,1
};
