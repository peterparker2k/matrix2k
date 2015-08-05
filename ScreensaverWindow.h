// ScreensaverWindow.h: interface for the ScreensaverWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENSAVERWINDOW_H__0805CE15_0E3F_47FF_A8B0_9CE2EC2F2DB4__INCLUDED_)
#define AFX_SCREENSAVERWINDOW_H__0805CE15_0E3F_47FF_A8B0_9CE2EC2F2DB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseWindow.h"

class ScreensaverWindow : public BaseWindow  
{
protected:
	void GetRegSettings();
	BOOL blnUsePassword;
	int iScreensaverMode;
	int		iTimerRate,idTimer;
	virtual LRESULT windowProc(HWND, UINT, WPARAM, LPARAM);

public:
	void setScreensaverMode(int i);
	ScreensaverWindow();
	virtual ~ScreensaverWindow();

	virtual void paintPreviewFirstFrame(HDC hdc);
	virtual void paintPreview(HDC hdc);
	virtual void paintFirstFrame(HDC hdc);
	virtual void paint(HDC hdc);
	virtual BOOL VerifyPassword(HWND hwnd);

	BITMAPINFO* binfo;	// The desktop's Snapshot
	unsigned char* mem;

private:
	POINT mousePos;
	bool isFirstFrame;
};

#endif // !defined(AFX_SCREENSAVERWINDOW_H__0805CE15_0E3F_47FF_A8B0_9CE2EC2F2DB4__INCLUDED_)
