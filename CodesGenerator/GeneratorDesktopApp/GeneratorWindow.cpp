#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "WindowUtilities.h"

#define UNICODE
#define _UNICODE

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 700

static TCHAR szWindowClass[] = _T("GeneratorApp");
static TCHAR szTitle[] = _T("Qrcode & Barcode Generator");

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
    AddControls(hWnd, hInst);

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

    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam)) 
        {
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
