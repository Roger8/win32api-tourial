#include "winnie.h"

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