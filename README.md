# win32api-tourial2
using window class 

**开启视觉效果加上下面的代码**
```cpp
//  Copy from MSDN  
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' \
processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
```

**实现窗口半透明**
```cpp
// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 540, 420,
		NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);
	//------------------------------------
	//下面两行设置窗口为半透明状态
	::SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, (255 * 90) / 150, LWA_ALPHA);
//-----------------------------------
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
```
&copy;Roger
