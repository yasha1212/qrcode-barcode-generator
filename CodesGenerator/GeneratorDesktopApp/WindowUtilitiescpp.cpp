#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "WindowUtilities.h"

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

void AddControls(HWND hWnd, HINSTANCE hInst) 
{
    HWND hEditQrcode = CreateWindow(_T("edit"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
        20, 360,
        310, 45,
        hWnd, (HMENU)IDE_QRCODE,
        hInst, NULL);

    HWND hEditBarcode = CreateWindow(_T("edit"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        370, 370,
        120, 20,
        hWnd, (HMENU)IDE_BARCODE,
        hInst, NULL);

    HWND hGenerateQrcodeBtn = CreateWindow(_T("button"), _T("Generate"),
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        115, 420,
        120, 20,
        hWnd, (HMENU)IDB_GENERATE_QRCODE,
        hInst, NULL);

    HWND hGenerateBarcodeBtn = CreateWindow(_T("button"), _T("Generate"),
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        370, 410,
        120, 20,
        hWnd, (HMENU)IDB_GENERATE_BARCODE,
        hInst, NULL);

    HWND hStaticQrcode = CreateWindow(_T("static"), _T("QR-Code"),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        20, 500,
        310, 20,
        hWnd, (HMENU)-1,
        hInst, NULL);

    HWND hStaticBarcode = CreateWindow(_T("static"), _T("Barcode"),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        370, 500,
        310, 20,
        hWnd, (HMENU)-1,
        hInst, NULL);

    HWND hRadioGroup = CreateWindow(_T("button"), _T("Barcode Type"),
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        530, 360,
        120, 80,
        hWnd, (HMENU)-1,
        hInst, NULL);

    HWND hRadioUPC = CreateWindow(_T("button"), _T("UPC"),
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        5, 25,
        100, 20,
        hRadioGroup, (HMENU)IDB_RADIO_UPC,
        hInst, NULL);

    HWND hRadioEAN = CreateWindow(_T("button"), _T("EAN-13"),
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        5, 50,
        100, 20,
        hRadioGroup, (HMENU)IDB_RADIO_UPC,
        hInst, NULL);
}

void DrawInterface(HDC hdc) 
{
    MoveToEx(hdc, 0, 350, NULL);
    LineTo(hdc, 700, 350);
    MoveToEx(hdc, 350, 350, NULL);
    LineTo(hdc, 350, 600);
}
