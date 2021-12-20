#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//#include <GdiPlus.h>

//using namespace Gdiplus;

static TCHAR szWindowClass[] = _T("SquareApp");


static TCHAR szTitle[] = _T("Square");

HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);





int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Colored Figure Application"),
            NULL);

        return 1;
    }


    hInst = hInstance;


    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Colored Figure Application"),
            NULL);

        return 1;
    }


    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}




HBITMAP hBitmap = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Square");

    UINT color = RGB(0xA3, 0x49, 0xA4);

    RECT square;
    BITMAP  bmp;

    switch (message)
    {
    case WM_CREATE:
        //hBitmap = (HBITMAP)LoadImage(hInst, L"c:\\Figure.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        //HBITMAP 
        hBitmap = (HBITMAP)LoadImage(NULL, L"nabmp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      /*  HBITMAP old = (HBITMAP)SelectObject(hdcMem, hBitmap);

        HBITMAP bmap;
        HPALETTE pal;
        CPalette  p1;
        LoadBitmapFromBMPFile(L"nabmp.bmp", &bmap, &pal);
        HDC filedc = CreateCompatibleDC(NULL);
        SelectObject(filedc, bmap);
        COLORREF color = GetPixel(filedc, 777, 258);
        int r2 = GetRValue(color);
        int g2 = GetGValue(color);
        int b2 = GetBValue(color);
        std::cout << r2 << " " << g2 << " " << b2;



        GetObject(hBitmap, sizeof(bmp), &bmp);

        for (int x = 0; x < bmp.bmWidth; x++)
        {
            for (int y = 0; y < bmp.bmHeight; y++)
            {

            }

        }*/

        break;

    case WM_PAINT:

        PAINTSTRUCT     ps;
        HDC             hdc;
        BITMAP          bitmap;
        HDC             hdcMem;
        HGDIOBJ         oldBitmap;


        RECT rect;
        GetClientRect(hWnd, &rect);


        hdc = BeginPaint(hWnd, &ps);


        hdcMem = CreateCompatibleDC(hdc);
        oldBitmap = SelectObject(hdcMem, hBitmap);

        GetObject(hBitmap, sizeof(bitmap), &bitmap);

        BitBlt(hdc, 0, (rect.bottom-rect.top-273)/2, 282, 273, hdcMem, 443, 159, SRCCOPY);
        
        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);


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