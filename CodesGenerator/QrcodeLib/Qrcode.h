#pragma once
#include <string>

namespace Qrcode 
{
    struct Module
    {
        bool value;
        bool isFree;
    };

    typedef std::vector<std::vector<Module>> QrCode;

    int Generate(std::string input, QrCode& qrcode); // Alphanumeric Coding with M correction level is used (1..20 versions)
}
