
#include <windows.h>

#define IDM_OPT2 302
#define IDM_OPEN 303
#define IDM_ADDPOPUP 304
#define IDM_Exit    3
const char g_szClassName[] = "myWindowClass";
HMENU hmain;
void createmenu();//创建菜单
HWND hwndstatusbar;
void openfileDlg();

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hb = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hb2 = CreateSolidBrush(RGB(0, 255, 0));
	HMENU hsub,hm;

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
		case IDM_OPEN:
			//MessageBox(hwnd, "opt3", "caption3 ", MB_OKCANCEL);
			openfileDlg();
			break;

		case IDM_ADDPOPUP:
			CheckMenuItem(hmain,IDM_ADDPOPUP,MF_CHECKED);
			hsub = CreatePopupMenu();
			hm = GetSubMenu(hmain,0);
			AppendMenu(hm, MF_STRING|MF_POPUP, (UINT_PTR)hsub, "newadd");//POPUP 类型的可以加子菜单
			AppendMenu(hsub,MF_STRING, IDM_Exit, "dd");
			MessageBox(hwnd, "opt4", "captiion4", MB_OK);
			break;
		case IDM_Exit:
			exit(0);

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
		NULL, hmain, hInstance, NULL);

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
	hmain = CreateMenu();//整个菜单栏句柄
	if (!hmain)
		return;
	HMENU popfile = CreatePopupMenu();
	HMENU poptest = CreatePopupMenu();
	// 一种方法是使用AppendMenu函数  
	AppendMenu(hmain, MF_POPUP, (UINT_PTR)popfile, "文件(&F)");
	
	AppendMenu(popfile, MF_STRING, IDM_OPEN, "Open(&O)");
	AppendMenu(popfile, MF_POPUP|MF_UNCHECKED , IDM_ADDPOPUP, "addpopup");
	
	

	//另一种方法是使用InsertMenuItem函数  
	MENUITEMINFO mif;
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.cch = 100;
	mif.dwItemData = NULL;
	mif.dwTypeData = "other";
	mif.fMask = MIIM_ID  | MIIM_STATE|MIIM_TYPE;
	mif.fState = MFS_GRAYED|MFS_HILITE;//灰色图标
	mif.fType = MFT_STRING|MFT_MENUBARBREAK;//垂直分隔
	mif.wID = IDM_OPT2;
	
	InsertMenuItem(popfile, IDM_OPT2, false, &mif);
	//
	AppendMenu(popfile, MF_SEPARATOR,0,0);//添加分隔符
	AppendMenu(hmain, MF_STRING, IDM_Exit, "exit(&E)");//添加exit

	AppendMenu(GetSubMenu(hmain,0), MF_STRING|MF_POPUP, (UINT_PTR)poptest, "er");//添加exit
	AppendMenu(poptest, MF_STRING, IDM_Exit, "exit");
	AppendMenu(hmain, MF_SYSMENU, IDM_Exit, "&Test");
}

void openfileDlg()// 打开文件选择对话框
{
	OPENFILENAME ofn;  
    WCHAR* szFile = new WCHAR[512];  
    WCHAR* szFileTitle = new WCHAR[512];  
    memset(&ofn, 0, sizeof(ofn));  
    memset(szFile, 0, sizeof(WCHAR)*512);  
    memset(szFileTitle, 0, sizeof(WCHAR)*512);  
  
    ofn.lStructSize = sizeof(ofn);  
    ofn.hwndOwner = hwndstatusbar;  
    ofn.hInstance = 0;  
    ofn.lpstrFilter = "All File\0*.*\0";  
    ofn.nFilterIndex = 1;  
    ofn.lpstrFile = (char *)szFile;  
    ofn.nMaxFile = sizeof(WCHAR)*512;  
    ofn.lpstrFileTitle = (char *)szFileTitle;  
    ofn.nMaxFileTitle = sizeof(WCHAR)*512;  
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;  
  
    // 按下确定按钮  
    BOOL ok = GetOpenFileName(&ofn);  
    if( ok ){  
        MessageBox(hwndstatusbar, ofn.lpstrFile,"title",  MB_OK);  
    }  
  
    delete []szFile;  
    delete []szFileTitle; 

}