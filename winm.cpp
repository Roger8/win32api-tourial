#include <Windows.h>
#include <iostream>

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class windowclass:public WNDCLASSEX
{
public:
	windowclass(WNDPROC WndProc ,char const * className, HINSTANCE hInst)
	{
		cbSize          = sizeof (WNDCLASSEX);
	    style           = CS_HREDRAW | CS_VREDRAW;
	    lpfnWndProc     = WndProc;
	    cbClsExtra      = 0;
	    cbWndExtra      = 0;
	    hInstance       = hInst;
	    hIcon           = 0;
	    hIconSm         = 0;
	    hCursor         = LoadCursor (0, IDC_ARROW);
	    hbrBackground   = (HBRUSH) (COLOR_WINDOW + 1);
	    lpszMenuName    = className;
	    lpszClassName   = className;

	}
	void Register()
	{
			if(!RegisterClassEx(this))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			return ;
		}
	}
};

class window
{
public:
	window():_hwnd(0){}
	window(char const* caption, char const* className, HINSTANCE hInstance)
	{
		_hwnd = CreateWindow(
			className,
			caption,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 400, 320,
			NULL, NULL, hInstance, NULL);

		if(_hwnd == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
				
		}
	}
	void Show(int nCmdShow)
	{
		ShowWindow(_hwnd, nCmdShow);
		UpdateWindow(_hwnd);
	}
	operator HWND(){return _hwnd;}
protected:
	HWND _hwnd;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	char className[]="roger";
	HWND hwnd;
	MSG msg;

	try
	{
		//Step 1: Registering the Window Class
		windowclass winClass(WndProc,className,hInstance);
		winClass.Register();
		// Step 2: Creating the Window
		window win(className,className,hInstance);
		win.Show(nCmdShow);

		/*window win2("winow2","win2",hInstance);
		win2.Show(nCmdShow);*/
		
	}
	catch(...)
	{
		MessageBox (0, "Unknown", "Exception", MB_ICONEXCLAMATION | MB_OK);
	}

	int status;
	// Step 3: The Message Loop
	while((status= GetMessage(&msg,0,0,0))!=0)
	{
		if(status == -1)
			return -1;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
		case WM_LBUTTONDOWN:
			{
			char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);

			HDC hdc;
			hdc = GetDC(hwnd);
			TextOut(hdc,0,50,"this is a test",10);
			ReleaseDC(hwnd,hdc);

			//
			//window win2("win2","window2",hInstance);
			//win2.Show(SW_SHOW);

            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
			}
			
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


/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
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
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
*/