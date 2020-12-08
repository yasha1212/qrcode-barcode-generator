#include "pch.h"
#include "framework.h"
#include <unordered_map>
#include "Barcode.h"
#include "BarcodeConstants.h"

using namespace std;

int CharToInt(char c);
char IntToChar(int i);
char GetControlNumber(string input);
void PushByte(unsigned char byte, vector<bool>& barcode);
void PushBorderGuard(vector<bool>& barcode);
void PushMiddleGuard(vector<bool>& barcode);

namespace Barcode 
{
	int GenerateUPC(string input, vector<bool>& barcode)
	{
		if (input.size() != 11)
		{
			return 1;
		}

		barcode.clear();

		PushBorderGuard(barcode);

		for (int i = 0; i < input.size(); i++)
		{
			if (i == UPC_STRING_MIDDLE_INDEX)
			{
				PushMiddleGuard(barcode);
			}

			char digit = input[i];
			int codeType = i < UPC_STRING_MIDDLE_INDEX ? L_CODE : R_CODE;

			PushByte(UPC_CODES_TABLE.at(digit)[codeType], barcode);
		}

		PushByte(UPC_CODES_TABLE.at(GetControlNumber(input))[R_CODE], barcode);
		PushBorderGuard(barcode);

		return 0;
	}

	int GenerateEAN13(string input, vector<bool>& barcode)
	{
		if (input.size() != 12) 
		{
			return 1;
		}

		barcode.clear();

		PushBorderGuard(barcode);

		char firstDigit = input[0];

		for (int i = 1; i < input.size(); i++) 
		{
			if (i == EAN13_STRING_MIDDLE_INDEX) 
			{
				PushMiddleGuard(barcode);
			}

			int codeType = R_CODE;
			char digit = input[i];

			if (i < EAN13_STRING_MIDDLE_INDEX) 
			{
				codeType = EAN13_FIRST_DIGIT_PATTERNS.at(firstDigit)[i - 1];
			}

			PushByte(EAN13_CODES_TABLE.at(digit)[codeType], barcode);
		}

		PushByte(EAN13_CODES_TABLE.at(GetControlNumber(input))[R_CODE], barcode);
		PushBorderGuard(barcode);

		return 0;
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
		int coeff = 1;

		switch (input.size())
		{
			case 11: coeff = i % 2 == 0 ? 3 : 1; break;
			case 12: coeff = i % 2 == 0 ? 1 : 3; break;
		}

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
