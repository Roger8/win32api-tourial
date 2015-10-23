//------------------------------------
//  winnie.cpp
//  (c) Bartosz Milewski, 1995
//------------------------------------

#include "winnie.h"
#include "resource.h"

// This is the entry point of every Windows program
int WINAPI WinMain
(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow)
{
	char className[] = "Winnie";

	// Define a Window Class and register it under the name "Winnie"
	WinClass winClass(WindowProcedure, className, hInst);
	winClass.Register();

	// Create and show a window
	WinMaker win("Hello Windows!", className, hInst);
	win.Show(cmdShow);

	MSG  msg;
	int status;
	// Keep pumping messages--they end up in our Window Procedure
	while ((status = ::GetMessage(&msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return -1;
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}

WinClass::WinClass(WNDPROC wndProc, char const * className, HINSTANCE hInst)
{
	_class.style = 0;
	_class.lpfnWndProc = wndProc;  // Window Procedure: mandatory
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hInstance = hInst;           // owner of the class: mandatory
	_class.hIcon = 0;
	_class.hCursor = ::LoadCursor(0, IDC_ARROW); // optional
	_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // optional
	_class.lpszMenuName = 0;
	_class.lpszClassName = className;   // mandatory
}

WinMaker::WinMaker
(char const * caption, char const * className, HINSTANCE hInstance)
{
	_hwnd = ::CreateWindow(
		className,              // name of a registered window class
		caption,                // window caption
		WS_OVERLAPPEDWINDOW,    // window style
		CW_USEDEFAULT,          // x position
		CW_USEDEFAULT,          // y position
		CW_USEDEFAULT,          // witdh
		CW_USEDEFAULT,          // height
		0,                      // handle to parent window
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)), // handle to menu
		hInstance,              // application instance
		0);                    // window creation data
}

// Window Procedure called by Windows with all kinds of messages

LRESULT CALLBACK WindowProcedure
(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_OPEN:
			MessageBox(hwnd, "open info", "open", MB_OK);
			break;
		case IDM_NEW:
			MessageBox(hwnd, "create new file or not ?", "new file window ", MB_OKCANCEL);
			break;
		default:
			break;
		}
		return 0;
		// In this simple program, this is the only message we are processing
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0; // return zero when processed

	}
	// All the unprocessed messages go there, to be dealt in some default way
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}



