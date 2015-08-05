// Bob.h: Schnittstelle für die Klasse CBob.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOB_H__EE1723AB_0241_11D3_A6F7_0080AD40DBC7__INCLUDED_)
#define AFX_BOB_H__EE1723AB_0241_11D3_A6F7_0080AD40DBC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <windows.h>
#include <wingdi.h>
#include <vector>
class CBob  
{
public:
	int ActualFrame;
	void NextFrame();
	RECT BobRect;
	int m_yc;		//ScreenCoordinate X
	int m_xc;		//ScreenCoordinate Y
	HDC sourceDC;		// von Hier wird geblittet..
	HWND destination;// hier wird hingeblittet...
	std::vector<RECT*> AnimRects;	//verkettete Liste der AnimPhasen
	int MaxAnimPhasen;			// Anzahl der AnimPhasen
	void SetSrcRect(int index=0);	// Setzt die AnimPhase index 
	void SetPos(int x,int y);	// Setzt die Pos des Bobs(Kein Blit!)
	void SetSrcRect(RECT src);	// Setzt beliebiges Rect
	void SetSrcRect(int x1,int y1,int x2,int y2);//Setzt beliebiges Rect
	void AddAnimationRect(int x1, int y1, int x2, int y2);//Addiert ein AnimRect
	void Show(HDC dc, int x=10000, int y=10000);//Blittet den Bob
	CBob();
	virtual ~CBob();

protected:
};

#endif // !defined(AFX_BOB_H__EE1723AB_0241_11D3_A6F7_0080AD40DBC7__INCLUDED_)
