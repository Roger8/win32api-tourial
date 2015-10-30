//------------------------------------
//  winnie.cpp
//  (c) Bartosz Milewski, 1995
//------------------------------------

#include "winnie.h"
#include "resource.h"
#include <windowsx.h>

//#include <CommCtrl.h> //包含头文件  
// 导入静态库  
//#pragma comment(lib, "Comctl32.lib")  
// 开启视觉效果 Copy from MSDN  
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' \
processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

bool flag = false;

WinClass::WinClass(WNDPROC wndProc, char const * className, HINSTANCE hInst)
{
	_class.style = 0;
	_class.lpfnWndProc = wndProc;  // Window Procedure: mandatory
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hInstance = hInst;           // owner of the class: mandatory
	_class.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_MYICON));
	_class.hCursor = ::LoadCursor(0, IDC_ARROW); // optional
	_class.hbrBackground = (HBRUSH)(COLOR_WINDOW-1); // optional
	_class.lpszMenuName = NULL;//把菜单设定为类级别的，直接在类中初始化
	_class.lpszClassName = className;   // mandatory
}

WinMaker::WinMaker
(char const * caption, char const * className,HMENU hmenu, HINSTANCE hInstance)
{
	_hwnd = ::CreateWindow(
		className,              // name of a registered window class
		caption,                // window caption
		WS_OVERLAPPEDWINDOW,    // window style
		300, 140, 400, 400,
		//CW_USEDEFAULT,          // x position
		//CW_USEDEFAULT,          // y position
		//CW_USEDEFAULT,          // witdh
		//CW_USEDEFAULT,          // height
		0,                      // handle to parent window
		hmenu,//,LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)), // handle to menu
		hInstance,              // application instance
		0);                    // window creation data
}


// Window Procedure called by Windows with all kinds of messages
 //bool flag = false;

LRESULT CALLBACK WindowProcedure
(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hdlg;
	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0; // return zero when processed
	case WM_CREATE:
		{
			hdlg = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_FORMVIEW),hwnd,(DLGPROC)DlgProc);
			
			ShowWindow(hdlg, SW_SHOWNA);
		}
		return 0;
	}

	// All the unprocessed messages go there, to be dealt in some default way
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int count=0;

	switch (msg)
	{
	
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			::PostQuitMessage(0);
		}
		return 0;
	case WM_COMMAND:
	{
		char str[MAXCHAR];

		switch ((LOWORD(wParam)))
		{
			case IDOK:
			{
				count++;
				int n = wsprintf(str, "u clicked \"ok\" %d times", count);
				HWND hstatic = GetDlgItem(hDlg,IDC_COUNT);
				SetWindowText(hstatic, str);
			}
				return 0;
			case IDCANCEL:
				return 0;
				break;
			case IDC_Login:
				DestroyWindow(hDlg);
				flag = true;
				return 0;
			}
	}
		return 0;
	}
	return (INT_PTR)FALSE;
}