// Screen.h: Schnittstelle für die Klasse CScreen.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREEN_H__C8FAE5F3_3AF1_11D3_B83F_0000E8699C86__INCLUDED_)
#define AFX_SCREEN_H__C8FAE5F3_3AF1_11D3_B83F_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StringLine.h"
#include "Registry.h"
#include "Bob.h"

#include <string>
#include <vector>

#define CHARWIDTH	16
#define CHARHEIGHT	24

class CScreen
{
public:
	int GetIntensity(int x, int y);
	void AddChar(int x,int y,int wert);
	int m_iCursor_Y;
	int m_iCursor_X;
	int GetChar(int x, int y);
	void SetIntensity(int x,int y, int hell);
	int GetWidth();
	int GetHeight();
	bool SetCrypto(bool newCrypto);
	void Print(int x, int y, std::string str,int intensity=0);
	void PrintLen(int x, int y, std::string str, int len,int intensity=-1);
	void VPrint(int x, int y, std::string str,int intensity=0);
	void ShowScreen(CBob *Letter, CBob* Cursor, int screen_index);
	void Scroll(int Line);
	void Clear();
	virtual void transformMultiScreen();
	RECT clipRectangle(RECT src, RECT clip);
	void SetChar(int x, int y, int wert, int intensity=0);
	CScreen(int x, int y);
	virtual ~CScreen();

private:
	int* m_ptrMemory;
protected:
	RECT* UpdateArea;
	std::vector<RECT*> monitor_dimensions;
	bool IsVisible(int x, int y);
	bool m_bolCryptic;
	int Translate(int Zeichen);
	int Height;
	int Width;
};

#endif // !defined(AFX_SCREEN_H__C8FAE5F3_3AF1_11D3_B83F_0000E8699C86__INCLUDED_)
