// Registry.h: Schnittstelle für die Klasse CRegistry.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRY_H__55F37108_856C_45F0_9109_F16A401421F3__INCLUDED_)
#define AFX_REGISTRY_H__55F37108_856C_45F0_9109_F16A401421F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <regstr.h>
#include <string>
#define REGSTR_PATH ("Software\\burning_Thornbush\\Matrix Screensaver")

#define REGISTRY_TITLE		0
#define REGISTRY_PHONE		1
#define REGISTRY_MESSAGE	2
#define REGISTRY_CODE		3
#define REGISTRY_FACE		4	//UNUSED IN THIS VERSION!!
#define REGISTRY_CLONE		5
#define REGISTRY_VIRTUAL	6
#define REGISTRY_SFX		7
#define REGISTRY_MSG_CUSTOM	8
#define REGISTRY_MSG_USER	9
#define REGISTRY_MSG_ORIG	10
#define REGISTRY_ACT_TIME	11
#define REGISTRY_MTX_GLITCH	12


class CRegistry  
{
public:
	static char* getMessage();
	const static std::string strOrig1;
	const static std::string strOrig2;

	static int MatrixShow[13] ;
	static char * TelNo;
	static char* Message;
	static void InitDefaults();
	static void WriteRegistry();
	static bool ReadRegistry();
	CRegistry();
	virtual ~CRegistry();

};

#endif // !defined(AFX_REGISTRY_H__55F37108_856C_45F0_9109_F16A401421F3__INCLUDED_)
