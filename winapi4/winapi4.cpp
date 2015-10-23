//通过资源文件来建立菜单

#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hb = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hb2 = CreateSolidBrush(RGB(0, 255, 0));

	char * psString = "hello world";
	switch (msg)
	{
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDM_ABT:
				MessageBox(hwnd, "about info", "about", MB_OK);
				break;
			case ID_UPDATE:
				MessageBox(hwnd, "update or not ?", "update window ", MB_OKCANCEL);
				break;
			default:
				break;
		}
		return 0;
	case WM_PAINT:
	
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(ps.hdc, hb);

		SetTextColor(ps.hdc,RGB(100,22,255));
		
		Rectangle(ps.hdc, 120, 140, 70, 100);
		SelectObject(hdc, hb2);
		Rectangle(ps.hdc, 200, 100, 180, 180);
		TextOut(hdc, 100, 100, psString, strlen(psString));
		DeleteObject(hb2);
		DeleteObject(hb);
		EndPaint(hwnd, &ps);
		
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 540, 420,
		NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
