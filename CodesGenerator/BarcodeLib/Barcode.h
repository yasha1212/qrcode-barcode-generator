#pragma once

#include <vector>
#include <string>

namespace Barcode 
{
	std::vector<bool> GenerateUPC(std::string input);
	std::vector<bool> GenerateEAN13(std::string input);
}
