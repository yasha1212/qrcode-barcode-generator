#pragma once
#include <string>

namespace Qrcode 
{
    struct QrCode
    {

    };

    QrCode Generate(std::string input); // Alphanumeric Coding with M correction level is used (1..20 versions)
}
