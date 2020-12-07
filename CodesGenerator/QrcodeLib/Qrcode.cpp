#include "framework.h"
#include "pch.h"
#include "QrcodeConstants.h"
#include "Qrcode.h"

using namespace std;

int ApplyMask(int x, int y);

namespace Qrcode 
{
    QrCode Generate(string input) 
    {

    }
}

int ApplyMask(int x, int y) 
{
    return (x / 3 + y / 2) % 2;
}
