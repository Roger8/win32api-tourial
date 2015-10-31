//------------------------------------
//  winnie.cpp
//  (c) Bartosz Milewski, 1995
//------------------------------------

#include "winnie.h"
#include "resource.h"
#include <windowsx.h>
#include <CommCtrl.h>
#include <vector>

//#include <CommCtrl.h> //����ͷ�ļ�  
// ���뾲̬��  
//#pragma comment(lib, "Comctl32.lib")  
// �����Ӿ�Ч�� Copy from MSDN  
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
	_class.lpszMenuName = NULL;//�Ѳ˵��趨Ϊ�༶��ģ�ֱ�������г�ʼ��
	_class.lpszClassName = className;   // mandatory
}

WinMaker::WinMaker
(char const * caption, char const * className,HMENU hmenu, HINSTANCE hInstance)
{
	_hwnd = ::CreateWindow(
		className,              // name of a registered window class
		caption,                // window caption
		WS_OVERLAPPEDWINDOW,    // window style
		300, 140, 410, 400,
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
	HWND hListview=NULL,hcomb=NULL;
	std::vector<studentinfo> stu;
	stu = {
		{"aa",22,"xingxing"},
		{"bb",33,"earth"},
		{"ldll",43,"anywhere"},
		{"kie",12,"kekwjdk"}
	};
	

	switch (msg)
	{
		case WM_SYSCOMMAND:
			if (wParam == SC_CLOSE)
			{
				::PostQuitMessage(0);
			}
			return 0;
		case WM_INITDIALOG:
			//��ȡlistview�ؼ����
			hListview = GetDlgItem(hDlg, IDC_LIST4);
			//����listview ����ʾ����
			ListView_SetExtendedListViewStyle(hListview, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT|
				LVS_EX_HEADERDRAGDROP
				|LVS_EX_GRIDLINES|LVS_EX_AUTOCHECKSELECT|LVS_EX_AUTOSIZECOLUMNS);
			//����listview����
			LVCOLUMN vcl;//ʹ��LVCOLUMN��Ҫ���<CommCtrl.h>
			vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			//��һ��
			vcl.pszText = "��һ��";
			vcl.cx = 60;
			vcl.iSubItem = 0;
			ListView_InsertColumn(hListview, 0, &vcl);
			
			vcl.pszText = "�ڶ���";
			vcl.cx = 60;
			vcl.iSubItem = 1;
			ListView_InsertColumn(hListview, 1, &vcl);

			vcl.pszText = "������";
			vcl.cx = 60;
			vcl.iSubItem = 2;
			ListView_InsertColumn(hListview, 2, &vcl);

			vcl.pszText = "forth column";
			SendMessage(hListview, LVM_INSERTCOLUMN, 3, (LPARAM)&vcl);

			hcomb = GetDlgItem(hDlg, IDC_COMBO1);
			ComboBox_AddString(hcomb, "icon");
			ComboBox_AddString(hcomb, "list");
			ComboBox_AddString(hcomb, "details");
			ComboBox_AddString(hcomb, "samllicon");
			ComboBox_SetCurSel(hcomb, 0);
			return 0;
		case WM_COMMAND:
		{
			char str[MAXCHAR];
			hListview = GetDlgItem(hDlg, IDC_LIST4);
			//wparam ���ֽ�
			switch (LOWORD(wParam))
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
				case IDC_ADD:
				{
					LVITEM lv;
					
					lv.mask = LVIF_TEXT;
					//studentinfo var = stu[0];
					for each (studentinfo var in stu)
					{
						lv.pszText = var.name;
						lv.iItem = count++;
						lv.iSubItem = 0;
						ListView_InsertItem(hListview, &lv);
						lv.iSubItem = 1;
						char astr[5];
						wsprintf(astr, "%d", var.age);
						lv.pszText = astr;
						ListView_SetItem(hListview, &lv);

						lv.iSubItem = 2;
						lv.pszText = var.address;
						ListView_SetItem(hListview, &lv);

					}
				}
					//DestroyWindow(hDlg);
					flag = true;
					return 0;
				case IDC_DEList:
					ListView_DeleteAllItems(hListview);
					count = 0;
					return 0;
				case IDC_COMBO1:
					if (HIWORD(wParam)==CBN_SELCHANGE)
					{
						int index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
						DWORD lview;
						switch (index)
						{
						case 0:
							lview = LV_VIEW_ICON;
							break;
						case 1:
							lview = LV_VIEW_LIST;
							break;
						case 2:
							lview = LV_VIEW_DETAILS;
							break;
						default:
							lview = LV_VIEW_SMALLICON;
							break;
						}
						ListView_SetView(GetDlgItem(hDlg, IDC_LIST4), lview);
					}
					return 0;
				}
		}
			return 0;
	}
	return (INT_PTR)FALSE;
}