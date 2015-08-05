// MatrixGlitch.h: interface for the MatrixGlitch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXGLITCH_H__CB23F729_F165_46C3_AFB3_51914A754010__INCLUDED_)
#define AFX_MATRIXGLITCH_H__CB23F729_F165_46C3_AFB3_51914A754010__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MatrixGlitch
{
public:
	MatrixGlitch();
	virtual ~MatrixGlitch();
public:
	unsigned int iSleep;
	int xc,yc,w,h;
	int iTimer;
};

#endif // !defined(AFX_MATRIXGLITCH_H__CB23F729_F165_46C3_AFB3_51914A754010__INCLUDED_)
