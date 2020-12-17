#include <stdlib.h>
#include <tchar.h>
#include <locale>
#include <codecvt>
#include "WindowUtilities.h"

using namespace std;

void AddMainMenu(HWND hWnd) 
{
    HMENU hMainMenu = CreateMenu();
    HMENU hPopMenuFile = CreatePopupMenu();
    HMENU hPopMenuAbout = CreatePopupMenu();

    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, _T("&File"));
    {
        AppendMenu(hPopMenuFile, MF_STRING, IDM_SAVE, _T("&Save As..."));
        AppendMenu(hPopMenuFile, MF_SEPARATOR, 0, _T(""));
        AppendMenu(hPopMenuFile, MF_STRING, IDM_QUIT, _T("&Quit"));
    }

    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuAbout, _T("&About"));
    {
        AppendMenu(hPopMenuAbout, MF_STRING, IDM_PROGRAM, _T("&Program"));
        AppendMenu(hPopMenuAbout, MF_STRING, IDM_AUTHOR, _T("&Author"));
    }

    SetMenu(hWnd, hMainMenu);
}

void CenterWindow(HWND hWnd, int width, int height) 
{
    int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    SetWindowPos(hWnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void DrawInterface(HDC hdc) 
{
    MoveToEx(hdc, 0, 350, NULL);
    LineTo(hdc, 700, 350);
    MoveToEx(hdc, 350, 350, NULL);
    LineTo(hdc, 350, 600);
}

bool IsValidInput(TCHAR *input, bool isUPC) 
{
    wstring str = input;

    if (str.size() != (isUPC ? 11 : 12)) 
    {
        return false;
    }

    for (auto ch : str) 
    {
        if (!iswdigit(ch)) 
        {
            return false;
        }
    }

    return true;
}

bool IsValidInput(TCHAR* input) 
{
    wstring str = input;

    if (str.size() > 330) 
    {
        return false;
    }

    return true;
}

string WideStringToString(wstring wstr) 
{
    string result;

    for (char ch : wstr) 
    {
        result += ch;
    }

    return result;
}

std::vector<unsigned char> WideStringToBytes(std::wstring wstr) 
{
    wstring_convert<codecvt_utf8<wchar_t>> cv;
    string str = cv.to_bytes(wstr);

    vector<unsigned char> bytes;

    for (auto byte : str)
    {
        bytes.push_back(byte);
    }

    return bytes;
}
