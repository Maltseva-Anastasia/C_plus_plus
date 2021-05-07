#include <Windows.h>
#include "Manager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  HWND hWnd;
  MSG lpMsg;
  WNDCLASSEX wc;

  wchar_t szClassName[] = L"LAB_2";
  int screen_size = 700;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = szClassName;
  wc.cbSize = sizeof(WNDCLASSEX);

  if (!RegisterClassEx(&wc))
    return 0;

  hWnd = CreateWindowEx(0, szClassName, L"Отрезок", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screen_size, screen_size, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, lpCmdLine);

  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&lpMsg, NULL, 0, 0))
  {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return lpMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam){
  PAINTSTRUCT ps;
  RECT Rect;
  HDC hdc, hCmpDC;
  HBITMAP hBmp;

  const unsigned int TIMER_SEC = 1;
  const unsigned int INTERVAL = 1;

  static Manager manager;

  switch (messg)
  {
  case WM_CREATE:
    SetTimer(hWnd, TIMER_SEC, INTERVAL, NULL);
    break;

  case WM_TIMER:
    manager.update();
    InvalidateRect(hWnd, NULL, FALSE);
    break;

  case WM_SIZE:
    GetClientRect(hWnd, &Rect);
    GVector::setWindowSize(Rect.right - Rect.left, Rect.bottom - Rect.top);
    break;

  case WM_KEYDOWN:
    switch (wParam) {
    case 'W':
    case VK_UP: manager += GVector::defLen; break;
    case 'S':
    case VK_DOWN:  manager -= GVector::defLen; break;
    case 'A':
    case VK_LEFT: manager << PI / 18; break;
    case 'D':
    case VK_RIGHT: manager >> PI / 18; break;
    case 'E': manager.operator++(); break;
    case 'Q': manager.operator--(); break;
    }
    InvalidateRect(hWnd, NULL, true);
    break;

  case WM_PAINT:
    GetClientRect(hWnd, &Rect);
    hdc = BeginPaint(hWnd, &ps);

    hCmpDC = CreateCompatibleDC(hdc);
    hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
      Rect.bottom - Rect.top);
    SelectObject(hCmpDC, hBmp);

    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = RGB(224, 100, 255);
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(hCmpDC, &Rect, brush);
    DeleteObject(brush);

    manager.paint(hCmpDC);

    SetStretchBltMode(hdc, COLORONCOLOR);
    BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
      hCmpDC, 0, 0, SRCCOPY);

    DeleteDC(hCmpDC);
    DeleteObject(hBmp);
    hCmpDC = NULL;

    EndPaint(hWnd, &ps);
    break;

  case WM_ERASEBKGND:
    return 1;
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, messg, wParam, lParam);
  }

  return 0;
}