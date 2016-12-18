#include <windows.h>

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
bool extraSpeed = false,
active = false;

HINSTANCE hInstG;
HWND hWndP;
HWND hWndD[5];

int WINAPI WinMain(HINSTANCE hInst,	HINSTANCE hPrev, LPSTR szCmdLine, int nShowCmd)					
{
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX); 
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WndProc;
	wcx.hInstance = hInst;	
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW+(5 + rand() % 20));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.lpszClassName = TEXT("Win32");

	if (!RegisterClassEx(&wcx))	return 1;

	hWndP = CreateWindowEx(0,
		TEXT("Win32"),
		TEXT("Win32API. Лабораторная работа №11"),
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0,
		600, 600,
		0,
		0,
		hInst,
		0);
		
	for (int i = 0; i < 5; i++)
	{
		hWndD[i] = CreateWindowEx(
			0,
			TEXT("Win32"),
			TEXT("Здравствуй"),
			WS_OVERLAPPEDWINDOW,
			100 + (i * 10),
			100 + (i * 10),
			500,
			500,
			hWndP,
			NULL,
			hInst,
			0
			);
	}

	hInstG = hInst;

	if (!hWndP) return 2;
	ShowWindow(hWndP, nShowCmd);
	UpdateWindow(hWndP);

	MSG msg = { 0 };
	while (GetMessage(&msg,
		0,
		0, 0))
	{	
		TranslateMessage(&msg);	
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			if (IDOK == MessageBox(hWnd, L"До новых встреч!", L"окно", MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1))
				SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		break;

	

		case WM_LBUTTONDOWN:
			if (hWnd != hWndP) break;
			if (!extraSpeed)
			{
				MessageBox(hWnd, L"Молодец!", L"окно", 0);
				extraSpeed = true;
			}
			if (!active)
			{
				for (int i = 0; i < 5; i++)
				{
					ShowWindow(hWndD[i], 1);
					UpdateWindow(hWndD[i]);
					HBRUSH brush = CreateSolidBrush(RGB(0 + rand() % 255, 0 + rand() % 255, 0 + rand() % 255));
					SetClassLongPtr(hWndD[i], GCLP_HBRBACKGROUND, (LONG)brush);	
				}
			}
		break;

		case WM_KEYDOWN:
		
				SetWindowPos(hWnd, NULL, 100 + rand() % 700, 100 + rand() % 150, 400 + rand() % 450, 400 + rand() % 450, NULL);
					
		break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}