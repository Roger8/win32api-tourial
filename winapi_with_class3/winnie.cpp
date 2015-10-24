//------------------------------------
//  winnie.cpp
//  (c) Bartosz Milewski, 1995
//------------------------------------

#include "winnie.h"
#include "resource.h"
#include <windowsx.h>



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
	_class.lpszMenuName = NULL;//把菜单设定为类级别的，直接在类中初始化
	_class.lpszClassName = className;   // mandatory
}

WinMaker::WinMaker
(char const * caption, char const * className, HINSTANCE hInstance)
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
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)), // handle to menu
		hInstance,              // application instance
		0);                    // window creation data
}

void WinMaker::setRegion()
{
	POINT pt[3] = {
		{200,400},
		{100,0},
		{300,0}	
	};
	
	HRGN hrg1 = CreatePolygonRgn(pt, 3, WINDING);
	HRGN hrg2 = CreateRoundRectRgn(0, 0, 400, 400, 20, 20);
	HRGN hrg=NULL;
	CombineRgn(hrg, hrg1, hrg2, RGN_AND);
	SetWindowRgn(_hwnd, hrg2, FALSE);
}

// Window Procedure called by Windows with all kinds of messages

LRESULT CALLBACK WindowProcedure
(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto hmm = GetMenu(hwnd);
	auto hmsub1 = GetSubMenu(hmm, 0);
	HWND hButton, hCombo, hEdit, hList, hScroll, hStatic;
	HINSTANCE ghInstance;
	ghInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0; // return zero when processed
	
	case WM_CREATE:
		hButton = CreateWindowEx(
			NULL,
			"Button",
			"Button 1",
			WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0,
			100, 30,
			hwnd, NULL,
			ghInstance,
			NULL);
		hCombo = CreateWindowEx(
			NULL,
			"ComboBox",
			"darkblue red",
			WS_BORDER | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			0, 30,
			100, 100,
			hwnd, NULL,
			ghInstance,
			NULL);
		hEdit = CreateWindowEx(
			NULL,
			"Edit",
			"edit box 1",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			0, 60,
			100, 30,
			hwnd, NULL,
			ghInstance,
			NULL);
		hList = CreateWindowEx(
			NULL,
			"ListBox",
			"db db db",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			100, 0,
			100, 200,
			hwnd, NULL,
			ghInstance,
			NULL);
		hScroll = CreateWindowEx(
			NULL,
			"ScrollBar",
			"scroll",
			WS_BORDER | WS_CHILD | WS_VISIBLE | SBS_VERT,
			210, 0,
			40, 200,
			hwnd, NULL,
			ghInstance,
			NULL);
		hStatic = CreateWindowEx(
			NULL,
			"Static",
			"kaldj",
			WS_BORDER | WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
			0, 90,
			100, 30,
			hwnd, NULL,
			ghInstance,
			NULL);
		break;
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			::PostQuitMessage(0);
			return 0;
		case IDM_OPEN:
			CheckMenuRadioItem(hmm, IDM_OPEN, IDM_NEW, IDM_OPEN, MF_BYCOMMAND);
			MessageBox(hwnd, "open info", "open", MB_OK);
			break;
		case IDM_NEW:
			CheckMenuRadioItem(hmm, IDM_OPEN, IDM_NEW, IDM_NEW, MF_BYCOMMAND);
			MessageBox(hwnd, "create new file or not ?", "new file window ", MB_OKCANCEL);
			break;
		case IDM_P1:
			CheckMenuRadioItem(hmm, IDM_P1, IDM_P2, IDM_P1, MF_BYCOMMAND);
			MessageBox(hwnd, "program 1", "pro window", MB_OK);
			break;
		case IDM_P2:
			CheckMenuRadioItem(hmm, IDM_P1, IDM_P2, IDM_P2, MF_BYCOMMAND);
			MessageBox(hwnd, "program 2", "pro window", MB_OK);
			break;
		case IDM_PRE:
			MessageBox(hwnd, "previous click", "pre win", MB_OK);
			break;
		case IDM_NEXT:
			MessageBox(hwnd, "next click", "the next win", MB_OK);
			break;
		default:
			break;
		}
		return 0;
	case WM_CONTEXTMENU:
		RECT rect;
		POINT pt;//获取指针在屏幕坐标
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		//获取客户区域大小
		GetClientRect(hwnd, &rect);

		//屏幕坐标转换为客户区坐标
		ScreenToClient(hwnd, &pt);
		//判断右击点是否在客户区内
		if (!(PtInRect(&rect, pt)))
			return 0;
		HMENU hcm = LoadMenu((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_CONTEXTMENU));
		if (!hcm)
			return 0;
		HMENU hpop = GetSubMenu(hcm, 0);
		//把客户区坐标还原
		ClientToScreen(hwnd, &pt);
		TrackPopupMenu(hpop, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
			pt.x, pt.y, 0, (HWND)wParam, NULL);
		//用完后销毁菜单资源
		DestroyMenu(hcm);
		return 0;
		// In this simple program, this is the only message we are processing
	}
	// All the unprocessed messages go there, to be dealt in some default way
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
