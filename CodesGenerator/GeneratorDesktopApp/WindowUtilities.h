#pragma once

#include <windows.h>
#include <string>
#include <vector>

#define IDM_SAVE 11
#define IDM_QUIT 12
#define IDM_PROGRAM 21
#define IDM_AUTHOR 22

#define IDB_GENERATE_QRCODE 31
#define IDB_GENERATE_BARCODE 32
#define IDB_RADIO_UPC 33
#define IDB_RADIO_EAN 34

#define IDE_QRCODE 41
#define IDE_BARCODE 42

void AddMainMenu(HWND hWnd);
void CenterWindow(HWND hWnd, int width, int height);
void DrawInterface(HDC hdc);
void DrawBarcode(HDC hdc, const std::vector<bool>& barcode, int scale);
void DrawQrcode(HDC hdc, const std::vector<std::vector<bool>>& qrcode, int scale);
bool IsValidInput(TCHAR *input, bool isUPC);
bool IsValidInput(TCHAR *input);
std::string WideStringToString(std::wstring wstr);
std::vector<unsigned char> WideStringToBytes(std::wstring wstr);
