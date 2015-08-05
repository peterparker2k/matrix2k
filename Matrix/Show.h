// Show.h: interface for the Show class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOW_H__7CACA21A_0638_410E_A20B_B4508D0835AD__INCLUDED_)
#define AFX_SHOW_H__7CACA21A_0638_410E_A20B_B4508D0835AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"
#include "MatrixGlitch.h"	// Added by ClassView

class Show : public CScreen
{
public:
	Show(int w, int h);
	virtual ~Show();

	char* EmptyLine;
	void ResetPrintManager();
	void TheMatrixShow(int dTime);
	bool ShowTitle(bool fullscreen=true);
	bool ShowMessage();
	bool ShowPhone();
	bool ShowTheMatrix(bool timeout=true);
private:
	MatrixGlitch glitch;
	std::string getActualTimeString();
	void nextShow(bool blnClearScreen=true);
	static int iShowType;
	static int iWindowIDCounter;
	int iID;
	int intPause;
	std::vector<std::string> MessageText;
	void initMessage();
	int iOldType;
	int MessageRows;
	static int m_iPrintManagerCount;
	CStringLine *m_ptrLines;
};

#endif // !defined(AFX_SHOW_H__7CACA21A_0638_410E_A20B_B4508D0835AD__INCLUDED_)
