//添加menu菜单

#include <windows.h>

#define IDM_OPT2 302
#define IDM_OPT3 303
#define IDM_OPT4 304

const char g_szClassName[] = "myWindowClass";
HMENU hmroot;
void createmenu();//创建菜单
HWND hwndstatusbar;

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
		/*hwndstatusbar = CreateWindowEx(0,"status",NULL,
			WS_CHILD|WS_VISIBLE,
			0,0,0,0,hwnd,
			);*/
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDM_OPT2:
			MessageBox(hwnd, "opt2", "caption", MB_OK);
			break;
		case IDM_OPT3:
			MessageBox(hwnd, "opt3", "caption3 ", MB_OKCANCEL);
			break;

		case IDM_OPT4:
			MessageBox(hwnd, "opt4", "captiion4", MB_OK);
			break;
		default:
			break;
		}
		return 0;
	case WM_PAINT:
	
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(ps.hdc, hb);

		SetTextColor(ps.hdc,RGB(100,22,255));
		
		TextOut(hdc, 100, 100, psString, strlen(psString));
		
		Rectangle(ps.hdc, 120, 140, 70, 100);
		SelectObject(hdc, hb2);
		Rectangle(ps.hdc, 200, 100, 180, 180);
		
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
	createmenu();

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
		NULL, hmroot, hInstance, NULL);

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

void createmenu()
{
	hmroot = CreateMenu();
	if (!hmroot)
		return;
	HMENU pop1 = CreatePopupMenu();
	// 一种方法是使用AppendMenu函数  
	AppendMenu(hmroot, MF_POPUP, (UINT_PTR)pop1, "文&件");
	AppendMenu(pop1, MF_STRING, IDM_OPT3, "文件2");
	AppendMenu(pop1, MF_POPUP, IDM_OPT4, "文件3");
	
	//另一种方法是使用InsertMenuItem函数  
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = "other";
	mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	mif.fState = MFS_ENABLED;
	mif.fType = MIIM_STRING;
	mif.wID = IDM_OPT2;
	
	InsertMenuItem(hmroot, IDM_OPT2, false, &mif);
	
	
}