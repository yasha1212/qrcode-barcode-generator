#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "WindowUtilities.h"
#include "Barcode.h"
#include "Qrcode.h"

using namespace std;

#define UNICODE
#define _UNICODE

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 700
#define SCALE 7

static TCHAR szWindowClass[] = _T("GeneratorApp");
static TCHAR szTitle[] = _T("Qrcode & Barcode Generator");

bool isUPC = true;
vector<bool> barcode;
Qrcode::Qrcode qrcode;
TCHAR barcodeInput[1024];
TCHAR qrcodeInput[1024];

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Qrcode & Barcode Generator"),
            MB_ICONWARNING);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Qrcode & Barcode Generator"),
            MB_ICONWARNING);

        return 1;
    }

    CenterWindow(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
    AddMainMenu(hWnd);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static HWND hEditQrcode;
    static HWND hEditBarcode;
    static HWND hGenerateQrcodeBtn;;
    static HWND hGenerateBarcodeBtn;
    static HWND hStaticQrcode;
    static HWND hStaticBarcode;
    static HWND hRadioGroup;
    static HWND hRadioUPC;
    static HWND hRadioEAN;

    switch (message)
    {
    case WM_CREATE:

        hEditQrcode = CreateWindow(_T("edit"), NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
            20, 360,
            310, 45,
            hWnd, (HMENU)IDE_QRCODE,
            hInst, NULL);

        hEditBarcode = CreateWindow(_T("edit"), NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            370, 370,
            120, 20,
            hWnd, (HMENU)IDE_BARCODE,
            hInst, NULL);

        hGenerateQrcodeBtn = CreateWindow(_T("button"), _T("Generate"),
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            115, 420,
            120, 20,
            hWnd, (HMENU)IDB_GENERATE_QRCODE,
            hInst, NULL);

        hGenerateBarcodeBtn = CreateWindow(_T("button"), _T("Generate"),
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            370, 410,
            120, 20,
            hWnd, (HMENU)IDB_GENERATE_BARCODE,
            hInst, NULL);

        hStaticQrcode = CreateWindow(_T("static"), _T("QR-Code"),
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            20, 500,
            310, 20,
            hWnd, (HMENU)-1,
            hInst, NULL);

        hStaticBarcode = CreateWindow(_T("static"), _T("Barcode"),
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            370, 500,
            310, 20,
            hWnd, (HMENU)-1,
            hInst, NULL);

        hRadioGroup = CreateWindow(_T("button"), _T("Barcode Type"),
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            530, 360,
            120, 80,
            hWnd, (HMENU)-1,
            hInst, NULL);

        hRadioUPC = CreateWindow(_T("button"), _T("UPC"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            535, 385,
            100, 20,
            hWnd, (HMENU)IDB_RADIO_UPC,
            hInst, NULL);

        SendMessage(hRadioUPC, BM_SETCHECK, 1, 0);

        hRadioEAN = CreateWindow(_T("button"), _T("EAN-13"),
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            535, 410,
            100, 20,
            hWnd, (HMENU)IDB_RADIO_EAN,
            hInst, NULL);

        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) 
        {
        case IDM_SAVE:
            if (!barcode.empty()) 
            {
                Barcode::WriteToBitmapFile(barcode, SCALE, "D:\\BARCODE_TEST.bmp");
            }
            if (!qrcode.empty()) 
            {
                Qrcode::WriteToBitmapFile(qrcode, SCALE, "D:\\QRCODE_TEST.bmp");
            }

            MessageBox(hWnd, _T("Files were successfully saved!"),
                _T("Qrcode & Barcode Generator"), MB_ICONINFORMATION);

            break;

        case IDM_QUIT:
            DestroyWindow(hWnd);
            break;

        case IDM_PROGRAM:
            MessageBox(hWnd, _T("This program can generate barcodes (UPC, EAN13) and qrcodes (<20 version of M-correction level)"),
                _T("Qrcode & Barcode Generator"), MB_ICONINFORMATION);
            break;

        case IDM_AUTHOR:
            MessageBox(hWnd, _T("Shukan Aleksey, 851005\nBSUIR, Minsk, 2020"),
                _T("Qrcode & Barcode Generator"), MB_ICONINFORMATION);
            break;

        case IDB_RADIO_EAN:
            isUPC = false;
            break;

        case IDB_RADIO_UPC:
            isUPC = true;
            break;

        case IDE_QRCODE:
            GetWindowText(hEditQrcode, qrcodeInput, 1024);
            break;

        case IDE_BARCODE:
            GetWindowText(hEditBarcode, barcodeInput, 1024);
            break;

        case IDB_GENERATE_BARCODE:
            if (IsValidInput(barcodeInput, isUPC)) 
            {
                if (isUPC) 
                {
                    Barcode::GenerateUPC(WideStringToString(barcodeInput), barcode);
                }
                else 
                {
                    Barcode::GenerateEAN13(WideStringToString(barcodeInput), barcode);
                }
            }
            else 
            {
                MessageBox(hWnd, _T("Input is not valid!"),
                    _T("Qrcode & Barcode Generator"), MB_ICONWARNING);
            }
            break;

        case IDB_GENERATE_QRCODE:
            if (IsValidInput(qrcodeInput)) 
            {
                Qrcode::Generate(WideStringToBytes(qrcodeInput), qrcode);
            }
            else 
            {
                MessageBox(hWnd, _T("Input is not valid!"),
                    _T("Qrcode & Barcode Generator"), MB_ICONWARNING);
            }
            break;
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawInterface(hdc);

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
