// Screen.cpp: Implementierung der Klasse CScreen.
//
//////////////////////////////////////////////////////////////////////

//#include "screensave.h"
#include "Bob.h"
#include "Screen.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
//int CScreen::m_iPrintManagerCount=0;

CScreen::CScreen(int xw, int yh)
{
	Height	=	yh;
	Width	=	xw;
	int Mem	=	Width*Height;
	m_ptrMemory = new int[Mem];
	SetCrypto(false);				//Wenn Crypto , dann erzeugt V/Print nur seltsame Zeichen auf dem Screen..
	Clear();
	UpdateArea= new RECT();
	UpdateArea->left=0;
	UpdateArea->top=0;
	UpdateArea->right=Width;
	UpdateArea->bottom=Height;

}

CScreen::~CScreen()
{
	delete m_ptrMemory;
	Width=0;
	Height=0;
}


void CScreen::Clear()
{
	int* laufpointer=m_ptrMemory;
	*laufpointer=0;
	for (int x=0; x<Width;x++)
		for (int y=0;y<Height;y++)
			*laufpointer++=Translate((int)(' '));
}

void inline  CScreen::SetChar(int x, int y, int wert, int intensity)
{
	wert=Translate(wert);
	if (intensity<4) 
		wert+=intensity; 
	else 
		wert+=rand()%4;

	if (IsVisible(x,y)) 
		m_ptrMemory[x + y*Width] = wert;
}

void CScreen::Scroll(int Line)
{
	int Offset=Line*Width;
	int Size=(Height-Line)*Width;
	for (int y=Line;y<Height-1; y++){
		int RowOffset=y*Width;
		for (int x=0;x<Width;x++)
			m_ptrMemory[x + RowOffset]=m_ptrMemory[x + (RowOffset+Width)];
	}
}

void CScreen::ShowScreen(CBob* Letter, CBob* Cursor)
{
	long iTimeStart=timeGetTime();
 
	int* DisplayMem = m_ptrMemory ;
	int character;
	int xpos, ypos;
	DisplayMem+=UpdateArea->top*Width;

	HDC dc=GetDC(Letter->destination);

	for (int i=UpdateArea->top; i<UpdateArea->bottom;i++)
	{
		for (int a=UpdateArea->left; a<UpdateArea->right;a++)
		{
				character=*DisplayMem++;
				xpos=((character>>2)%40)*CHARWIDTH;
				ypos=( (character & 0x03)*3 + (character/160) )*CHARHEIGHT;

				Letter->SetSrcRect(xpos,ypos,xpos+CHARWIDTH, ypos+CHARHEIGHT);
				if (m_iCursor_X==a && m_iCursor_Y==i)
					Cursor->Show(dc, CHARWIDTH*a,CHARHEIGHT*i);
				else
					Letter->Show(dc, CHARWIDTH*a,CHARHEIGHT*i);
		}
		DisplayMem+=(Width - UpdateArea->right + UpdateArea->left);
	}

	// FPS Counter..
	long iTimeEnd=timeGetTime()-iTimeStart;
	char message[50];
	wsprintf(message,"elapsed Time: %d", iTimeEnd);
	//TextOut(dc,100,100,message, strlen(message));
	ReleaseDC(Letter->destination, dc);
}

int CScreen::Translate(int Zeichen)
{
	int		Returnwert;
	char TranslationMap[]=" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-+*/.,;:<> $_§'!%[]{}()@#~|&";
	int translation=0;
	char TransByte=(char)(Zeichen);
	while (TranslationMap[translation]!=0)	//Texte werden normal ausgegeben
	{
		if (TranslationMap[translation]==TransByte) break;
		translation++;
	}
	if (m_bolCryptic) 
		while (translation>0) 
			translation-=25;	//Texte werden verschluesselt!
	Returnwert=(translation+25)<<2;
	return (Returnwert);
}

void CScreen::Print(int x, int y, std::string  str, int intensity)
{
	if (IsVisible(x,y))
	{
		int index=0;
		while ((str[index]!=0) && (x<Width))
		{
			SetChar(x++,y,(int)(str[index++]), intensity);
		}
	}
	m_iCursor_X=x;
	m_iCursor_Y=y;
}
void CScreen::VPrint(int x, int y, std::string  str, int intensity)
{
	if (IsVisible(x,y))
	{
		int index=0;
		while ((str[index]!=0) && (y<Height))
		{
			SetChar(x,y++,(int)(str[index++]), intensity);
		}
		m_iCursor_X=x;
		m_iCursor_Y=y;
	}
}
void CScreen::PrintLen(int x, int y, std::string  str,int Len, int intensity)
{
	int count=0;
	if (Len>0)
	{
		int index=0;
		while ((count<Len) && (x<Width)  && (str[index]!=0))
		{
			if (intensity==-1) 
			{
				SetChar(x,y,(int)(str[index++]), GetIntensity(x,y));
				x++;
			}
			else
				SetChar(x++,y,(int)(str[index++]), intensity);
			count++;
		}
		m_iCursor_X=x;
		m_iCursor_Y=y;
	}
}

bool CScreen::SetCrypto(bool newCrypto)
{
	bool oldcrypto;
	oldcrypto=m_bolCryptic;
	m_bolCryptic=newCrypto;
return (oldcrypto);
}

int CScreen::GetHeight()
{
return (Height);
}

int CScreen::GetWidth()
{
return (Width);
}

void CScreen::SetIntensity(int x, int y, int hell)
{
	if (IsVisible(x,y))
	{
		int wert=0;
		if (hell<4 && hell>=0)
		{
			wert= m_ptrMemory[x + y*Width] & 0xFFFC;
			wert+=hell;
			m_ptrMemory[x + y*Width]=wert;
		}
	}
}
int CScreen::GetIntensity(int x, int y)
{
	int retVal=0;
	if (IsVisible(x,y))
		retVal= m_ptrMemory[x + y*Width] & 0x0003;
	return retVal;
}

int CScreen::GetChar(int x, int y)
{
	return m_ptrMemory[x + y*Width];
}

bool CScreen::IsVisible(int x, int y)
{
	bool Vis=false;
	if ((x>=0) && (x<Width) && (y>=0) && (y<Height)) 
		Vis=true;
	return Vis;
}

void CScreen::AddChar(int x, int y, int wert)
{
	if (IsVisible(x,y))
	{
		m_ptrMemory[x + y*Width]+=wert;
		m_ptrMemory[x + y*Width]=m_ptrMemory[x + y*Width] %25;
	}
}


