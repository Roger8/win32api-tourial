#pragma once
#if !defined WINNIE_H
#define WINNIE_H
//------------------------------------
//  winnie.h
//  (c) Bartosz Milewski, 1995, 97
//------------------------------------

#include <windows.h>
extern bool flag;

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
	WinMaker(char const * caption, char const * className, HMENU hmenu, HINSTANCE hInstance);
	
	void Show(int cmdShow)
	{
		::ShowWindow(_hwnd, cmdShow);
		::UpdateWindow(_hwnd);
	}
protected:
	HWND _hwnd;
};

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

struct studentinfo
{
	char name[6];
	unsigned int age;
	char address[10];
};
#endif
