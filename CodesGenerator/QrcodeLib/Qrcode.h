#pragma once
#include <string>

namespace Qrcode 
{
    typedef std::vector<std::vector<bool>> Qrcode;

    int Generate(std::vector<unsigned char> input, Qrcode& qrcode); // Bytes Coding with M correction level is used (1..20 versions)
}
