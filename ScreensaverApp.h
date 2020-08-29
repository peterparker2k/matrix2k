// ScreensaverApp.h: interface for the ScreensaverApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENSAVERAPP_H__E180E8E3_125A_43D2_AE95_E29D0B8B03A6__INCLUDED_)
#define AFX_SCREENSAVERAPP_H__E180E8E3_125A_43D2_AE95_E29D0B8B03A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>

#include <vector>

#include "Matrix/MatrixWindow.h"

#define SS_MODE_CONFIG		0x0001
#define SS_MODE_PREVIEW		0x0002
#define SS_MODE_PASSWORD	0x0003
#define SS_MODE_SAVER		0x0004

class MonitorInfo
{
public:
	HMONITOR hMonitor;  // handle to display monitor
	HDC hdcMonitor;     // handle to monitor-appropriate device context
	RECT rcMonitor; // pointer to monitor intersection rectangle
	LPARAM dwData;       // data passed from EnumDisplayMonitors
	MatrixWindow	Window;		// window which covers the Monitor
	BITMAPINFO* bmapinfo;
	unsigned char* mem;
};


class ScreensaverApp
{
private:
	bool isSingleInstance();
	static std::vector<MonitorInfo*> vecDisplays;
	void initialize();
	static BOOL CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static bool CALLBACK MonitorEnum(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	static bool isInitialized;
	int InterpreteCommandLine();
	HWND parentHwnd;
protected:
	int iScreensaverMode;
public:
	ScreensaverApp();
	virtual ~ScreensaverApp();
	static std::vector<MonitorInfo*> getDisplays(){return vecDisplays;}
	virtual int init();
	virtual int run();
	virtual int exit();

};
#endif // !defined(AFX_SCREENSAVERAPP_H__E180E8E3_125A_43D2_AE95_E29D0B8B03A6__INCLUDED_)
