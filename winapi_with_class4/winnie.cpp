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
	SetWindowRgn(_hwnd, hrg2, TRUE);
}

// Window Procedure called by Windows with all kinds of messages

LRESULT CALLBACK WindowProcedure
(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto hmm = GetMenu(hwnd);
	auto hmsub1 = GetSubMenu(hmm, 0);

	PenMaker pen(PS_SOLID, 2, RGB(255, 0, 0));
	HINSTANCE ghInstance;
	ghInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

	static POINT curPoint;

	switch (message)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0; // return zero when processed
	case WM_LBUTTONDOWN:
	{
		curPoint.x = GET_X_LPARAM(lParam);
		curPoint.y = GET_Y_LPARAM(lParam);
		
		HDC hdc = GetDC(hwnd);
		char zuobiao[100];
		wsprintf(zuobiao, "x:%d y: %d", curPoint.x, curPoint.y);
		TextOut(hdc, curPoint.x, curPoint.y, zuobiao, strlen(zuobiao));
		ReleaseDC(hwnd, hdc);//释放hdc
		return 0;
	}
		break;
	case WM_PAINT:
	{
		
		//paintfunc(hwnd);
		break;
	}
		return 0;

	case WM_COMMAND:
	{
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
		case IDM_GO:
		{
			//这里的画不出来？？
			//PAINTSTRUCT ps;//PAINTSTRUCT只用在WM_PAINT中
			//BeginPaint(hwnd, &ps);
			HDC hdc = GetDC(hwnd);
			//// 创建钢笔  
			HPEN pen = CreatePen(PS_DASH, 2, RGB(25, 255, 50));
			// 把笔选到DC中  
			SelectObject(hdc, pen);
			// 设定线段的起点  
			MoveToEx(hdc, 11, 12, NULL);
			LineTo(hdc, 110, 120);
			DeleteObject(pen);
			ReleaseDC(hwnd, hdc);
			//EndPaint(hwnd, &ps);
			return 0;
		}
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

PenMaker::PenMaker(int iStyle=PS_SOLID, int cWidth=1, COLORREF color=0)
	
{
	_hpen = CreatePen(iStyle, cWidth, color);
}

HPEN PenMaker::SetPen(int iStyle, int cWidth, COLORREF color)
{
	_hpen = CreatePen(iStyle, cWidth, color);
	return _hpen;
}

void paintfunc(HWND hwnd) {
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);
	// 创建钢笔  
	HPEN pen = CreatePen(PS_DASH, 2, RGB(255, 0, 50));
	// 把笔选到DC中  
	SelectObject(ps.hdc, pen);
	// 设定线段的起点  
	MoveToEx(ps.hdc, 110, 12, NULL);
	LineTo(ps.hdc, 12, 33);

	SelectObject(ps.hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(ps.hdc, RGB(0, 0, 255));
	Rectangle(ps.hdc, 20, 18, 68, 50);
	SetDCBrushColor(ps.hdc, RGB(220, 32, 70));
	Rectangle(ps.hdc, 125, 100, 230, 300);
	SetDCBrushColor(ps.hdc, RGB(30, 235, 12));
	Ellipse(ps.hdc, 270, 80, 390, 223);
	SetDCBrushColor(ps.hdc, RGB(35, 160, 242));
	Chord(ps.hdc, 185, 260, 420, 480, 190, 260, 405, 479);
	SetDCBrushColor(ps.hdc, RGB(211, 254, 41));
	Pie(ps.hdc, 35, 320, 300, 600, 56, 470, 60, 360);

	DeleteObject(pen);
	EndPaint(hwnd, &ps);
}