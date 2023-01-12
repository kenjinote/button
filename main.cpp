#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>

#define ID_BUTTON1 100

TCHAR szClassName[]=TEXT("window");

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg)
	{
		case WM_CREATE:
			CreateWindow(
				TEXT("BUTTON"),
				TEXT("Close"),
				WS_CHILD|WS_VISIBLE,
				10,10,128,30,
				hWnd,
				(HMENU)ID_BUTTON1,
				((LPCREATESTRUCT)lParam)->hInstance,
				0
			);
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_BUTTON1:
					SendMessage(hWnd,WM_CLOSE,0,0);
					break;
			}
			break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd,msg,wParam,lParam);
    }
    return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	const HINSTANCE hInstance=GetModuleHandle(0);
	const WNDCLASS wndclass={
		CS_HREDRAW|CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	const HWND hWnd=CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,0,CW_USEDEFAULT,0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(msg.wParam);
}

#if _DEBUG
void main(){}
#endif