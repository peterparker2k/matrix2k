// StringLine.h: Schnittstelle für die Klasse CStringLine.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGLINE_H__5698D5F4_4C6F_11D3_B85C_0000E8699C86__INCLUDED_)
#define AFX_STRINGLINE_H__5698D5F4_4C6F_11D3_B85C_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringLine  
{
public:
	int GetBlinkType();
	int GetPosY();
	void SetHeight(int h);
	CStringLine(int h);
	int GetHeight();
	char* DisplayString();		// gibt den Matrix Codec-zurück, damit er mit VPrint ausgegeben werden kann..
	CStringLine();
	virtual ~CStringLine();

private:
	int m_iBlinkType;
	int actScroll;
	int ScrollSpeed;
	int Height;
	void InitString();
	int CharOffset;
	int PosY;
	char* String;
};

#endif // !defined(AFX_STRINGLINE_H__5698D5F4_4C6F_11D3_B85C_0000E8699C86__INCLUDED_)
