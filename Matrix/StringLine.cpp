// StringLine.cpp: Implementierung der Klasse CStringLine.
//
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>		//for Random
#include "StringLine.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CStringLine::CStringLine()
{
	Height=20;								//Standardwert bei falschem Aufruf
	InitString();
	PosY=0;
}
CStringLine::CStringLine(int h)
{
	Height=h;
	InitString();
	PosY=0;
}

CStringLine::~CStringLine()
{
	delete String;
}
//////////////////////////////////////////////////////////////////////
// Methoden.....
//////////////////////////////////////////////////////////////////////

char* CStringLine::DisplayString()
{
	char* ptrTemp;
	ptrTemp=String;
	ptrTemp+=PosY;
	if ((actScroll--)<=0)
	{
		actScroll=ScrollSpeed;
		if ((PosY--)<0)
		{
			delete String;
			InitString();	//Wenn die Line unten ist neu konfig..
			PosY=2*Height;
		}
	}
	return ptrTemp;
}

void CStringLine::InitString()
{
	char* strDummy="Dies ist der Dummy String, aus dem später die MATRIX CODES werden, Er sollte schon etwas laenger SEIN..";
	PosY=rand()%2*Height;
	ScrollSpeed=rand()%4;
	actScroll=ScrollSpeed;
	m_iBlinkType=rand()%4;
	int	 iHoehe=GetHeight();
	String=new char[2*iHoehe+3];		//String mit doppelter Screenhoehe...
	char* strPointer=String;

	for (int i=0; i<iHoehe;i++)
		{
			*strPointer++ =' '	;								//zweite hälfte voll schrott...
		}
	for (int  i=0; i<iHoehe;i++)
		{
			*strPointer++ =rand()%24+65;//(*strDummy++);		//zweite hälfte voll schrott...
		}
		*strPointer++ =(char)0;
		*strPointer++ =(char)'Y';
		*strPointer++ =(char)0;
}

int CStringLine::GetHeight()
{
return Height;
}


void CStringLine::SetHeight(int h)	//Re-define the height of th String..
{
	delete String;
	Height=h;
	InitString();
}

int CStringLine::GetPosY()
{
	return PosY;
}

int CStringLine::GetBlinkType()
{
	return m_iBlinkType;
}
