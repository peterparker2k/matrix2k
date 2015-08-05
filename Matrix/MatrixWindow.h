// MatrixWindow.h: interface for the MatrixWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXWINDOW_H__C6AA774E_D143_4F86_ACBC_7C6ADF48764E__INCLUDED_)
#define AFX_MATRIXWINDOW_H__C6AA774E_D143_4F86_ACBC_7C6ADF48764E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ScreensaverWindow.h"
#include "Bob.h"
#include "Show.h"

class MatrixWindow : public ScreensaverWindow  
{
private:
	void loadGFX(HWND h, int wid, int hei);
	void UpdateFunction(int dTime);
	int ilter;

	CBob		Team,Text,Cursor ;
	Show		*Screen;		

public:
	MatrixWindow();
	virtual ~MatrixWindow();

	virtual void paintPreviewFirstFrame(HDC hdc);
	virtual void paintPreview(HDC hdc);
	virtual void paintFirstFrame(HDC hdc);
	virtual void paint(HDC hdc);

};

#endif // !defined(AFX_MATRIXWINDOW_H__C6AA774E_D143_4F86_ACBC_7C6ADF48764E__INCLUDED_)
