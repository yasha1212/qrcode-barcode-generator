#include "pch.h"
#include "framework.h"
#include <fstream>
#include "Bitmap.h"
#include "BitmapConstants.h"

using namespace std;

unsigned char* CreateBitmapFileHeader(int height, int actualWidth);
unsigned char* CreateBitmapInfoHeader(int height, int width);

namespace Bitmap 
{
    void WriteBarcodeToFile(vector<bool> barcode, int scale, string path) 
    {
        ofstream file(path, ios::binary);

        int width = BARCODE_WIDTH * scale;
        int height = BARCODE_HEIGHT * scale;

        int widthInBytes = width * BMP_PIXEL_SIZE;

        unsigned char padding[3] = { 0, 0, 0 };
        int paddingSize = (4 - (widthInBytes % 4)) % 4;

        int actualWidth = widthInBytes + paddingSize;

        unsigned char* fileHeader = CreateBitmapFileHeader(height, actualWidth);
        unsigned char* infoHeader = CreateBitmapInfoHeader(height, width);

        file.write((char*)fileHeader, BMP_HEADER_SIZE);
        file.write((char*)infoHeader, BMP_INFO_HEADER_SIZE);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < BARCODE_WIDTH; j++) 
            {
                for (int k = 0; k < scale; k++)
                {
                    if (barcode[j] == 0)
                    {
                        file.write((char*)&WHITE_PIXEL, BMP_PIXEL_SIZE);
                    }
                    else
                    {
                        file.write((char*)&BLACK_PIXEL, BMP_PIXEL_SIZE);
                    }
                }
            }

            file.write((char*)padding, paddingSize);
        }

        file.close();
    }
}

unsigned char* CreateBitmapFileHeader(int height, int actualWidth) 
{
    int fileSize = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE + height * actualWidth;

    static unsigned char fileHeader[] =
    {
        0, 0,       // signature
        0, 0, 0, 0, // file size in bytes
        0, 0, 0, 0, // reserved
        0, 0, 0, 0  // pixels array offset
    };

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    fileHeader[2] = (fileSize);
    fileHeader[3] = (fileSize >> 8);
    fileHeader[4] = (fileSize >> 16);
    fileHeader[5] = (fileSize >> 24);
    fileHeader[10] = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

    return fileHeader;
}

unsigned char* CreateBitmapInfoHeader(int height, int width) 
{
    static unsigned char infoHeader[] =
    {
        0, 0, 0, 0, // info header size
        0, 0, 0, 0, // image width
        0, 0, 0, 0, // image height
        0, 0,       // number of color planes
        0, 0,       // bits per pixel
        0, 0, 0, 0, // compression
        0, 0, 0, 0, // image size
        0, 0, 0, 0, // horizontal resolution
        0, 0, 0, 0, // vertical resolution
        0, 0, 0, 0, // colors in color table
        0, 0, 0, 0  // important color count
    };

    infoHeader[0] = BMP_INFO_HEADER_SIZE;
    infoHeader[4] = (width);
    infoHeader[5] = (width >> 8);
    infoHeader[6] = (width >> 16);
    infoHeader[7] = (width >> 24);
    infoHeader[8] = (height);
    infoHeader[9] = (height >> 8);
    infoHeader[10] = (height >> 16);
    infoHeader[11] = (height >> 24);
    infoHeader[12] = 1;
    infoHeader[14] = BMP_PIXEL_SIZE * 8;

    return infoHeader;
}
