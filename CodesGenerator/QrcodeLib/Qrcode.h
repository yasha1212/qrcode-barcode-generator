#pragma once
#include <string>
#include "Bitmap.h"

namespace Qrcode 
{
    typedef std::vector<std::vector<bool>> Qrcode;

    int Generate(std::vector<unsigned char> input, Qrcode& qrcode);
    void WriteToBitmapFile(const Qrcode& qrcode, int scale, std::string path);
}
