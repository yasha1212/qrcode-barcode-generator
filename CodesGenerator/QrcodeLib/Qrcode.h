#pragma once
#include <string>

namespace Qrcode 
{
    struct QrCode
    {

    };

    int Generate(std::string input, Qrcode::QrCode& qrcode); // Alphanumeric Coding with M correction level is used (1..20 versions)
}
