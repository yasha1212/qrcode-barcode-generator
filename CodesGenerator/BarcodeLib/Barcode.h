#pragma once

#include <vector>
#include <string>

namespace Barcode 
{
	int GenerateUPC(std::string input, std::vector<bool>& barcode);
	int GenerateEAN13(std::string input, std::vector<bool>& barcode);
}
