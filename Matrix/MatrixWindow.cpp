// MatrixWindow.cpp: implementation of the MatrixWindow class.
//
//////////////////////////////////////////////////////////////////////
#include <math.h>
#include "MatrixWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MatrixWindow::MatrixWindow()
{
	ilter=0;
}

MatrixWindow::~MatrixWindow()
{

}

void MatrixWindow::paint(HDC hdc)
{
	UpdateFunction(ilter++);
}
void MatrixWindow::paintFirstFrame(HDC hdc)
{
	RECT bildschirm;
	GetClientRect(this->hWnd,&bildschirm);
	loadGFX(this->hWnd,bildschirm.right,bildschirm.bottom);
}
void MatrixWindow::paintPreview(HDC hdc)
{
	double y,x;
	const double WI=3.14/180; // 1 Grad
	RECT bildschirm;
	GetClientRect(this->hWnd,&bildschirm);
	HDC ScrDC=GetDC(this->hWnd);
	FillRect(ScrDC,&bildschirm,(HBRUSH) GetStockObject(BLACK_BRUSH));

	int r=0;
	static int roff=-1;
	for (int x2=0 ;x2<360;x2++)
	{
		if (r>=60 || r<=0) roff=-roff;
		r+=roff;
			y=sin(WI*x2+8*ilter*WI)*40+50;
			x=sin(WI*x2+2.5*ilter*WI)*40+bildschirm.right/2;
			SetPixel(ScrDC,(int) x,(int) y,RGB(0,255-4*r,0));
			SetPixel(ScrDC,(int) (bildschirm.right-x),(int) y,RGB(0,4*r,0));
	}

	ReleaseDC(hWnd,ScrDC);
	ilter++;
}
void MatrixWindow::paintPreviewFirstFrame(HDC hdc)
{
	paintPreview(hdc);
}


void MatrixWindow::UpdateFunction(int dTime)
{
	Cursor.NextFrame();
	Screen->TheMatrixShow(dTime);
	Screen->ShowScreen(&Text, &Cursor, screen_index);	// Zeigt den Textbildschirm an....
}

void MatrixWindow::loadGFX(HWND GMainHwnd, int wid, int hei)
{
	HANDLE bmap=LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_SPRITES),IMAGE_BITMAP, 0,0,0);
	HDC dc=GetDC(GMainHwnd);
	HDC src=CreateCompatibleDC(dc);
	HANDLE oldBmap=SelectObject(src,bmap);
	ReleaseDC(GMainHwnd, dc);

	Screen=new Show(wid/CHARWIDTH,hei/CHARHEIGHT);
	Screen->transformMultiScreen();
	Team.destination=GMainHwnd;
	Team.sourceDC=src;
	Team.AddAnimationRect(368,289,639,479);
	Team.AddAnimationRect(0,289,256,311);
	Team.AddAnimationRect(0,313,128,335);

	Text.destination=GMainHwnd;
	Text.sourceDC=src;

	Cursor.destination=GMainHwnd;
	Cursor.sourceDC=src;
	Cursor.AddAnimationRect(34*CHARWIDTH, 2*CHARHEIGHT, 35*CHARWIDTH, 3*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH, 5*CHARHEIGHT, 35*CHARWIDTH, 6*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH, 8*CHARHEIGHT, 35*CHARWIDTH, 9*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH,11*CHARHEIGHT, 35*CHARWIDTH,12*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH, 8*CHARHEIGHT, 35*CHARWIDTH, 9*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH, 5*CHARHEIGHT, 35*CHARWIDTH, 6*CHARHEIGHT);
	Cursor.AddAnimationRect(34*CHARWIDTH, 2*CHARHEIGHT, 35*CHARWIDTH, 3*CHARHEIGHT);
	Cursor.AddAnimationRect(36*CHARWIDTH, 2*CHARHEIGHT, 37*CHARWIDTH, 3*CHARHEIGHT);

}
