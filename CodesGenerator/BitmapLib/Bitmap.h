#pragma once

#include <string>
#include <vector>

namespace Bitmap 
{
    void WriteBarcodeToFile(std::vector<bool> barcode, std::string path);
}
