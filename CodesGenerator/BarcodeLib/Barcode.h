#pragma once

#include <vector>
#include <string>
#include "Bitmap.h"

namespace Barcode 
{
	int GenerateUPC(std::string input, std::vector<bool>& barcode);
	int GenerateEAN13(std::string input, std::vector<bool>& barcode);
	void WriteToBitmapFile(const std::vector<bool>& barcode, int scale, std::string path);
}
