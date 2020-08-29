// BaseWindow.cpp: Implementierung der Klasse BaseWindow.
//
// Makes a simple Window
//////////////////////////////////////////////////////////////////////
#include <utility>
#include "BaseWindow.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

bool BaseWindow::isRegistered=false;

BaseWindow::BaseWindow()
{
	hWnd=parentHWND=NULL;		// Handle Window
	rctPosition.left=64;rctPosition.top=64;
	rctPosition.right=320;rctPosition.bottom=240;
	dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
	dwStyle	  = WS_POPUP;
	registerWindow();
}

BaseWindow::~BaseWindow()
{
	if (hWnd)
		DestroyWindow(hWnd);
}

HWND BaseWindow::getWindowHandle()
{
	return hWnd;
}

void BaseWindow::setParentHandle(HWND h)
{
	parentHWND=h;
	dwStyle		=WS_CHILD ;
	GetClientRect(parentHWND,&rctPosition);
}

RECT BaseWindow::getPosition()
{
	GetWindowRect(hWnd,&rctPosition);
	return rctPosition;
}

void BaseWindow::setPosition(RECT pos)
{
	rctPosition=pos;
	if (hWnd)
		SetWindowPos(hWnd,HWND_TOP,rctPosition.left,rctPosition.top, rctPosition.right,rctPosition.bottom,SWP_NOZORDER|SWP_SHOWWINDOW);
}

DWORD BaseWindow::getStyle(bool getExStyle)
{
	return (getExStyle? dwExStyle:dwStyle) ;
}

void BaseWindow::setStyles(DWORD exStyle, DWORD style)
{
	if((int)exStyle!=-1)
		dwExStyle=exStyle;
	if((int)style!=-1)
		dwStyle=style;
}

bool BaseWindow::registerWindow()
{
	if (!isRegistered){
		HINSTANCE		hInstance;
		WNDCLASSEX		wc;
		hInstance		= GetModuleHandle(NULL);		// Grab An Instance For Our Window
		wc.cbSize		= sizeof(WNDCLASSEX);
		wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window
		wc.lpfnWndProc		= staticWndProc;			// WndProc Handles Messages
		wc.cbClsExtra		= 0;					// No Extra Window Data
		wc.cbWndExtra		= 0;					// No Extra Window Data
		wc.hInstance		= hInstance;				// Set The Instance
		wc.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON));
		wc.hIconSm			= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON));
		wc.hCursor			= NULL;//LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1) );
		wc.hbrBackground	= CreateSolidBrush(COLOR_BACKGROUND);					// No Background Required For GL
		wc.lpszMenuName		= NULL;//MAKEINTRESOURCE(IDR_MENU1);
		wc.lpszClassName	= "BaseWindow";				// Set The Class Name

		if (!RegisterClassEx(&wc))
		{
			int i=GetLastError();
			MessageBox(NULL, "Failed to Register the WindowClass","WINDOWS ERROR", MB_OK|MB_ICONEXCLAMATION);
			isRegistered=false;
		}else {
			isRegistered=true;
		}
	}
	return isRegistered;
}

// TODO: TitleString into Basewindow::strTitle

bool BaseWindow::createWindow(int screen_index)
{
	this->screen_index = screen_index;
	BaseWindow* w=this;
// Install the CBT hook
// Note: hook the thread immediately before, and unhook it immediately after CreateWindow call.
// The hook procedure can only process window creation nofitications, and it shouldn't be called for other types of notifications
// Additionally, calling hook for other events is wasteful since it won't do anything useful anyway
	HHOOK hook = SetWindowsHookEx(WH_CBT, CBTHook, 0, GetCurrentThreadId());

// Create window
// Pass a pair consisting of window object pointer and hook as lpParam
	std::pair<BaseWindow *, HHOOK> hookData(w, hook);

	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"BaseWindow",
								"Matrix-Screensaver",
								dwStyle,
								rctPosition.left,rctPosition.top,rctPosition.right,rctPosition.bottom,
								parentHWND,
								NULL,
								GetModuleHandle(NULL),
								&hookData)))
	{
		UnhookWindowsHookEx(hook);
		int i=GetLastError();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	UnhookWindowsHookEx(hook);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	return true;
}

int BaseWindow::MessageLoop()
{
	MSG	msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
	    DispatchMessage(&msg);
	}
	return (msg.wParam);
}

LRESULT BaseWindow::windowProc(HWND hwnd,  UINT uMsg,   WPARAM wParam,  LPARAM lParam )
{
  switch (uMsg)
  {
  case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
  case WM_DESTROY:
		PostQuitMessage(0);
  }
LRESULT retVal=DefWindowProc(hwnd, uMsg, wParam, lParam);
return retVal;
}

LRESULT CALLBACK BaseWindow::staticWndProc(HWND hwnd,  UINT uMsg,   WPARAM wParam,  LPARAM lParam )
{
	BaseWindow *w = (BaseWindow *) GetWindowLong(hwnd, GWL_USERDATA);
// It should be valid, assert so
// Redirect messages to the window procedure of the associated window
return w->windowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK BaseWindow::CBTHook(int code,   WPARAM wParam,  LPARAM lParam )
{
	if (code != HCBT_CREATEWND) {
		return 0;
	}
	std::pair<BaseWindow *, HHOOK> *p = (std::pair<BaseWindow *, HHOOK> *) LPCBT_CREATEWND(lParam)->lpcs->lpCreateParams;
	if (p && p->first!=NULL) {
		SetWindowLong((HWND) wParam, GWL_USERDATA, (long) p->first);
		p->first = NULL;
	}
	if (p)
		return CallNextHookEx(p->second, code, wParam, lParam);
	return 0;
}
