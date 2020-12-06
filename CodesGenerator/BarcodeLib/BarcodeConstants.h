#pragma once

#include <vector>
#include <unordered_map>

const unsigned char BORDER_BYTE = 0b00000101;
const unsigned char MIDDLE_BYTE = 0b00001010;

const int UPC_STRING_MIDDLE_INDEX = 6;
const int EAN13_STRING_MIDDLE_INDEX = 7;

const int L_CODE = 0;
const int R_CODE = 1;
const int G_CODE = 2;

const std::unordered_map<char, std::vector<unsigned char>> UPC_CODES_TABLE // Digit, {L_CODE, R_CODE}
{
	{'0', {0b00001101, 0b01110010} },
	{'1', {0b00011001, 0b01100110} },
	{'2', {0b00010011, 0b01101100} },
	{'3', {0b00111101, 0b01000010} },
	{'4', {0b00100011, 0b01011100} },
	{'5', {0b00110001, 0b01001110} },
	{'6', {0b00101111, 0b01010000} },
	{'7', {0b00111011, 0b01000100} },
	{'8', {0b00110111, 0b01001000} },
	{'9', {0b00001011, 0b01110100} }
};

const std::unordered_map<char, std::vector<unsigned char>> EAN13_CODES_TABLE // Digit, {L_CODE, R_CODE, G_CODE}  
{
	{'0', {0b00001101, 0b01110010, 0b00100111} },
	{'1', {0b00011001, 0b01100110, 0b00110011} },
	{'2', {0b00010011, 0b01101100, 0b00011011} },
	{'3', {0b00111101, 0b01000010, 0b00100001} },
	{'4', {0b00100011, 0b01011100, 0b00011101} },
	{'5', {0b00110001, 0b01001110, 0b00111001} },
	{'6', {0b00101111, 0b01010000, 0b00000101} },
	{'7', {0b00111011, 0b01000100, 0b00010001} },
	{'8', {0b00110111, 0b01001000, 0b00001001} },
	{'9', {0b00001011, 0b01110100, 0b00010111} }
};

const std::unordered_map<char, std::vector<int>> EAN13_FIRST_DIGIT_PATTERNS
{
	{'0', {L_CODE, L_CODE, L_CODE, L_CODE, L_CODE, L_CODE} }, // LLLLLL
	{'1', {L_CODE, L_CODE, G_CODE, L_CODE, G_CODE, G_CODE} }, // LLGLGG
	{'2', {L_CODE, L_CODE, G_CODE, G_CODE, L_CODE, G_CODE} }, // LLGGLG
	{'3', {L_CODE, L_CODE, G_CODE, G_CODE, G_CODE, L_CODE} }, // LLGGGL
	{'4', {L_CODE, G_CODE, L_CODE, L_CODE, G_CODE, G_CODE} }, // LGLLGG
	{'5', {L_CODE, G_CODE, G_CODE, L_CODE, L_CODE, G_CODE} }, // LGGLLG
	{'6', {L_CODE, G_CODE, G_CODE, G_CODE, L_CODE, L_CODE} }, // LGGGLL
	{'7', {L_CODE, G_CODE, L_CODE, G_CODE, L_CODE, G_CODE} }, // LGLGLG
	{'8', {L_CODE, G_CODE, L_CODE, G_CODE, G_CODE, L_CODE} }, // LGLGGL
	{'9', {L_CODE, G_CODE, G_CODE, L_CODE, G_CODE, L_CODE} }  // LGGLGL
};
