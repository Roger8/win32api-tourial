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
	_class.lpszMenuName = NULL;//�Ѳ˵��趨Ϊ�༶��ģ�ֱ�������г�ʼ��
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
		CW_USEDEFAULT/2,          // witdh
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
	auto hmm = GetMenu(hwnd);
	auto hmsub1 = GetSubMenu(hmm, 0);
	
	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0; // return zero when processed
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
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
		POINT pt;//��ȡָ������Ļ����
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		//��ȡ�ͻ������С
		GetClientRect(hwnd, &rect);

		//��Ļ����ת��Ϊ�ͻ�������
		ScreenToClient(hwnd, &pt);
		//�ж��һ����Ƿ��ڿͻ�����
		if (!(PtInRect(&rect, pt)))
			return 0;
		HMENU hcm = LoadMenu((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDR_CONTEXTMENU));
		if (!hcm)
			return 0;
		HMENU hpop = GetSubMenu(hcm, 0);
		//�ѿͻ������껹ԭ
		ClientToScreen(hwnd, &pt);
		TrackPopupMenu(hpop, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
			pt.x, pt.y, 0, (HWND)wParam, NULL);
		//��������ٲ˵���Դ
		DestroyMenu(hcm);
		return 0;
		// In this simple program, this is the only message we are processing
	}
	// All the unprocessed messages go there, to be dealt in some default way
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
