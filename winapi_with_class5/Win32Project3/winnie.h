#pragma once
#if !defined WINNIE_H
#define WINNIE_H
//------------------------------------
//  winnie.h
//  (c) Bartosz Milewski, 1995, 97
//------------------------------------

#include <windows.h>

// Forward declaration of our Window Procedure
LRESULT CALLBACK WindowProcedure
(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// We'll be creating windows of this Class in our program
class WinClass
{
public:
	WinClass(WNDPROC wndProc, char const * className, HINSTANCE hInst);
	void Register()
	{
		::RegisterClass(&_class);
	}
private:
	WNDCLASS _class;
};

// Creates a window of a given Class
class WinMaker
{
public:
	WinMaker() : _hwnd(0) {}
	WinMaker(char const * caption, char const * className, HINSTANCE hInstance);
	void setRegion();
	void Show(int cmdShow)
	{
		::ShowWindow(_hwnd, cmdShow);
		::UpdateWindow(_hwnd);
	}
protected:
	HWND _hwnd;
};


//create a pen 
class PenMaker
{
public :
	PenMaker() : _hpen(0) {}
	PenMaker(int iStyle, int cWidth, COLORREF color);
	HPEN GetPen()
	{
		return _hpen;
	}
	HPEN SetPen(int iStyle, int cWidth, COLORREF color);
	~PenMaker()
	{
		DeleteObject(_hpen);
	}
protected:
	HPEN _hpen;
public:
	int iStyle;
	int cWidth;
	COLORREF color;
};

void paintfunc(HWND);

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
#endif
