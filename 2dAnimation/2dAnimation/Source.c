
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define massSize 5
RECT mas[massSize];
RECT rct;

LRESULT _stdcall WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (message == WM_DESTROY) {
		PostQuitMessage(0);
	}
	else if (message == WM_SIZE) {
		GetClientRect(hwnd, &rct);
	}
	else return DefWindowProcA(hwnd, message, wparam, lparam);
}

void FullMas() {
	srand(5);
	for (int i = 0; i < massSize; i++) {
		mas[i].left = rand() % 800 - 100;
		mas[i].top = rand() % 400;
		mas[i].right = mas[i].left + 100;
		mas[i].bottom = mas[i].top + 100;
	}
}

void Drawing(HDC dc) {
	HDC memDC = CreateCompatibleDC(dc);
	HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right - rct.left, rct.bottom - rct.top);
	SelectObject(memDC, memBM);

	SelectObject(memDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC, RGB(255, 255, 255));
	Rectangle(memDC, 0, 0, 640, 480);

	SelectObject(memDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC, RGB(0, 255, 0));
	SelectObject(memDC, GetStockObject(DC_PEN));
	SetDCPenColor(memDC, RGB(0, 255, 0));
	for (int i = 0; i < massSize; i++) {
		Rectangle(memDC, mas[i].left,  mas[i].top, mas[i].right, mas[i].bottom);
	}
	BitBlt(dc, 0, 0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}

void Move() {
	for (int i = 0; i < massSize; i++) {
		mas[i].left += 3;
		if (mas[i].left > 700) {
			mas[i].left = -100;
		}
		mas[i].right = mas[i].left + 100;
		mas[i].bottom = mas[i].top + 100;
	}
}

void main() {
	WNDCLASSA wcl;
	memset(&wcl, 0, sizeof(WNDCLASSA));
	wcl.lpszClassName = "my windows";
	wcl.lpfnWndProc = WndProc;
	RegisterClassA(&wcl);

	HWND hwnd;
	hwnd = CreateWindowA("My Windows", "Windows Name", WS_OVERLAPPEDWINDOW, 10, 10, 640, 480, NULL, NULL, NULL, NULL);

	HDC dc = GetDC(hwnd);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	FullMas();
	MSG msg;
	while (1) 
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			Move();
			Drawing(dc);
			Sleep(5);
		}
	}

	return 0;
}