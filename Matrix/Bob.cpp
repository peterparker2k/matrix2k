// Bob.cpp: Implementierung der Klasse CBob.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "Bob.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBob::CBob()
{
	m_xc=0;
	m_yc=0;
	MaxAnimPhasen = 0;
	ActualFrame=0;
}

CBob::~CBob()
{

}

void CBob::Show(HDC dc, int x, int y)
{
	if (x != 10000) 
		m_xc=x;  // Neue Coords, falls welche da sind..
	if (y != 10000) 
		m_yc=y;
	BitBlt(dc,m_xc,m_yc,BobRect.right-BobRect.left, BobRect.bottom-BobRect.top, sourceDC, BobRect.left, BobRect.top,SRCCOPY);
}

void CBob::SetSrcRect(int x1, int y1, int x2, int y2)
{
	BobRect.left = x1;
	BobRect.top	 = y1;
	BobRect.right= x2;
	BobRect.bottom=y2;
}

void CBob::SetSrcRect(RECT src)
{
	BobRect = src ;
}

void CBob::SetPos(int x, int y)
{
	m_xc = x ;
	m_yc = y ;
}

void CBob::SetSrcRect(int index)
{
	if (index>=0 && index<MaxAnimPhasen)
	{
		RECT *temp=AnimRects[index];
		BobRect =  *temp;
	}
}

void CBob::AddAnimationRect(int x1, int y1, int x2, int y2)
{
	RECT * tmp =new RECT();
	tmp->left=x1;	tmp->top=y1;
	tmp->right=x2;	tmp->bottom=y2;
	AnimRects.push_back(tmp);
	MaxAnimPhasen=AnimRects.size();

}

void CBob::NextFrame()
{
	ActualFrame++;
	if (ActualFrame>MaxAnimPhasen) ActualFrame=0;
	SetSrcRect(ActualFrame);
}
