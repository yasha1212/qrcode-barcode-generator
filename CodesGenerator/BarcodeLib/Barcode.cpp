#include "pch.h"
#include "framework.h"
#include <unordered_map>
#include "Barcode.h"

using namespace std;

const unsigned char BORDER_BYTE = 0b00000101;
const unsigned char MIDDLE_BYTE = 0b00001010;
const int STRING_MIDDLE_INDEX = 6;
const int LEFT_CODE = 0;
const int RIGHT_CODE = 1;

const unordered_map<char, vector<unsigned char>> UPC_CODES_TABLE
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

int CharToInt(char c);
char IntToChar(int i);
char GetControlNumber(string input);
void PushByte(unsigned char byte, vector<bool>& barcode);
void PushBorderGuard(vector<bool>& barcode);
void PushMiddleGuard(vector<bool>& barcode);

namespace Barcode 
{
	vector<bool> GenerateUPC(string input) 
	{
		if (input.size() != 11)
		{
			vector<bool> empty;

			return empty;
		}

		vector<bool> barcode;
		PushBorderGuard(barcode);

		for (int i = 0; i < input.size(); i++)
		{
			if (i == STRING_MIDDLE_INDEX)
			{
				PushMiddleGuard(barcode);
			}

			int codeType = i < STRING_MIDDLE_INDEX ? LEFT_CODE : RIGHT_CODE;
			PushByte(UPC_CODES_TABLE.at(input[i])[codeType], barcode);
		}

		PushByte(UPC_CODES_TABLE.at(GetControlNumber(input))[RIGHT_CODE], barcode);
		PushBorderGuard(barcode);

		return barcode;
	}
}

int CharToInt(char c)
{
	return c - '0';
}

char IntToChar(int i)
{
	return '0' + i;
}

char GetControlNumber(string input)
{
	int sum = 0;

	for (int i = 0; i < input.size(); i++)
	{
		int coeff = i % 2 == 0 ? 3 : 1;

		sum += CharToInt(input[i]) * coeff;
	}

	int result = (10 - (sum % 10)) % 10;

	return IntToChar(result);
}

void PushByte(unsigned char byte, vector<bool>& barcode)
{
	for (int i = 6; i >= 0; i--)
	{
		barcode.push_back(byte & (1 << i));
	}
}

void PushBorderGuard(vector<bool>& barcode)
{
	for (int i = 2; i >= 0; i--)
	{
		barcode.push_back(BORDER_BYTE & (1 << i));
	}
}

void PushMiddleGuard(vector<bool>& barcode)
{
	for (int i = 4; i >= 0; i--) 
	{
		barcode.push_back(MIDDLE_BYTE & (1 << i));
	}
}
