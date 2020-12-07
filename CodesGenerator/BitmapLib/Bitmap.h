#pragma once

#include <string>
#include <vector>

namespace Bitmap 
{
    void WriteBarcodeToFile(std::vector<bool> barcode, int scale, std::string path);
}
