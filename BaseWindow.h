// BaseWindow.h: Schnittstelle für die Klasse BaseWindow.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_)
#define AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "resource.h"

class BaseWindow
{
private:
	static bool isRegistered;
	static bool	registerWindow();
	static LRESULT CALLBACK staticWndProc (HWND, UINT, WPARAM, LPARAM);
	static LRESULT CALLBACK CBTHook(int code, WPARAM wp, LPARAM lp);
protected:
	HWND	hWnd,parentHWND;		// Handle Window
	virtual LRESULT windowProc(HWND, UINT, WPARAM, LPARAM);
	DWORD	dwExStyle;
	DWORD	dwStyle;
	RECT	rctPosition;
	int 	screen_index;
public:
	HWND	getWindowHandle();
	void	setParentHandle(HWND h);

	RECT	getPosition();
	void	setPosition(RECT pos);
	DWORD	getStyle(bool getExStyle=false);
	void	setStyles(DWORD exStyle=-1, DWORD style=-1);

	bool	createWindow(int screen_index);
	int		MessageLoop();

	BaseWindow();
	virtual ~BaseWindow();
};


#endif // !defined(AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_)
