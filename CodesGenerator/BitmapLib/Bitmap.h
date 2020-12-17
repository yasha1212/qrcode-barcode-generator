#pragma once

#include <string>
#include <vector>

namespace Bitmap 
{
    void CreateBitmapFile(std::vector<bool> data, int width, int height, std::string path);
}
