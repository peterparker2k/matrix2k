// Registry.cpp: Implementierung der Klasse CRegistry.
//
//////////////////////////////////////////////////////////////////////

#include "Registry.h"
#include "LMCONS.H"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
int CRegistry::MatrixShow[13]={TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE, TRUE};
char* CRegistry::Message="Default Message";
char* CRegistry::TelNo="00";
const std::string CRegistry::strOrig1="Hello ";
const std::string CRegistry::strOrig2="...\r\nThe Matrix has you...\r\nFollow the white rabbit\r\nKnock, knock, ";

CRegistry::CRegistry()
{

}

CRegistry::~CRegistry()
{

}

bool CRegistry::ReadRegistry()
{
	long	result;
	HKEY	sKey;
	DWORD	val, valType, valSize;
	result	=	RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH,0,KEY_ALL_ACCESS, &sKey);

	if (result!=ERROR_SUCCESS) {
		return false;
	}
	valSize	=	sizeof(val);
	result	=	RegQueryValueEx(sKey,"SFX",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_SFX]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"TITLE",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_TITLE]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"PHONE",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_PHONE]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"MESSAGE",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_MESSAGE]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"CODE",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_CODE]=(BOOL)val;

	result	=	RegQueryValueEx(sKey,"CLONE",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_CLONE]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"VIRTUAL",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_VIRTUAL]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"MSG_CUSTOM",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_MSG_CUSTOM]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"MSG_USER",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_MSG_USER]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"MSG_ORIG",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_MSG_ORIG]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"ACT_TIME",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_ACT_TIME]=(BOOL)val;
	result	=	RegQueryValueEx(sKey,"MTX_GLITCH",0,&valType, (LPBYTE)&val, &valSize);
	MatrixShow[REGISTRY_MTX_GLITCH]=(BOOL)val;

	int correct=0;
	correct+=MatrixShow[REGISTRY_MSG_CUSTOM]?1:0;
	correct+=MatrixShow[REGISTRY_MSG_USER]?1:0;
	correct+=MatrixShow[REGISTRY_MSG_ORIG]?1:0;
	if (correct!=1)
	{
		MatrixShow[REGISTRY_MSG_CUSTOM]=false;
		MatrixShow[REGISTRY_MSG_USER]=false;
		MatrixShow[REGISTRY_MSG_ORIG]=true;
	}

	if (MatrixShow[REGISTRY_CLONE]==MatrixShow[REGISTRY_VIRTUAL])
	{
		MatrixShow[REGISTRY_CLONE]=true;
		MatrixShow[REGISTRY_VIRTUAL]=false;
	}

	valSize=1024;
	char* temp=Message;
	temp[0]='\0';		// String ist leer
	result	=	RegQueryValueEx(sKey,"TEXT",0,&valType, (LPBYTE)temp, &valSize);

	valSize=11;
	char* temp2=new char[12];
	for (int x=0; x<12; x++) 
		temp2[x]=' ';
	temp2[0]='\0';		// String ist leer
	result	=	RegQueryValueEx(sKey,"TELNO",0,&valType, (LPBYTE)temp2, &valSize);
	if (result!=ERROR_SUCCESS){
		return false;
	}
	TelNo=temp2;

	RegCloseKey(sKey);
	return true;
}

void CRegistry::WriteRegistry()
{
	long	result;
	HKEY	sKey;
	DWORD	val, Disp;
	result=	RegCreateKeyEx(HKEY_CURRENT_USER, REGSTR_PATH,0,NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &sKey, &Disp);

	val=MatrixShow[REGISTRY_TITLE];
	result=RegSetValueEx(sKey, "TITLE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_PHONE];
	RegSetValueEx(sKey, "PHONE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_MESSAGE];
	RegSetValueEx(sKey, "MESSAGE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_CODE];
	RegSetValueEx(sKey, "CODE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_FACE];
	RegSetValueEx(sKey, "FACE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_SFX];
	RegSetValueEx(sKey, "SFX",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));

	val=MatrixShow[REGISTRY_CLONE];
	RegSetValueEx(sKey, "CLONE",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_VIRTUAL];
	RegSetValueEx(sKey, "VIRTUAL",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_MSG_CUSTOM];
	RegSetValueEx(sKey, "MSG_CUSTOM",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_MSG_USER];
	RegSetValueEx(sKey, "MSG_USER",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_MSG_ORIG];
	RegSetValueEx(sKey, "MSG_ORIG",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_ACT_TIME];
	RegSetValueEx(sKey, "ACT_TIME",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));
	val=MatrixShow[REGISTRY_MTX_GLITCH];
	RegSetValueEx(sKey, "MTX_GLITCH",0,REG_DWORD, (CONST BYTE*) &val, sizeof(val));

	if (MatrixShow[REGISTRY_MSG_CUSTOM])
		RegSetValueEx(sKey, "TEXT",0,REG_SZ, (CONST BYTE*) Message, strlen(Message));

	RegSetValueEx(sKey, "TELNO",0,REG_SZ, (CONST BYTE*) TelNo, strlen(TelNo));
	RegCloseKey(sKey);
}

void CRegistry::InitDefaults()
{
	MatrixShow[REGISTRY_SFX]	=true;
	MatrixShow[REGISTRY_TITLE]	=true;
	MatrixShow[REGISTRY_PHONE]	=true;
	MatrixShow[REGISTRY_MESSAGE]=true;
	MatrixShow[REGISTRY_CODE]	=true;
	MatrixShow[REGISTRY_FACE]	=true;

	MatrixShow[REGISTRY_CLONE]	=true;
	MatrixShow[REGISTRY_VIRTUAL]	=false;
	MatrixShow[REGISTRY_MSG_CUSTOM]	=false;
	MatrixShow[REGISTRY_MSG_USER]	=false;
	MatrixShow[REGISTRY_MSG_ORIG]	=true;
	MatrixShow[REGISTRY_ACT_TIME]	=false;
	MatrixShow[REGISTRY_MTX_GLITCH]	=false;

	std::string str="Neo";
	std::string strTmp=strOrig1;
	strTmp.append(str);
	strTmp.append(strOrig2);
	strTmp.append("Neo..    \r\n");
	
	const char* Orig=strTmp.c_str();
	const char* origTel="3525550690";
	Message=new char[1024];
	TelNo=new char[12];
	strcpy(Message, Orig);
	strcpy(TelNo, origTel);
}

char* CRegistry::getMessage()
{
	char* retVal=Message;

	if (MatrixShow[REGISTRY_MSG_ORIG])
	{
		std::string str="Neo";
		std::string strTmp=strOrig1;
		strTmp.append(str);
		strTmp.append(strOrig2);
		strTmp.append("Neo..    \r\n");
		strcpy(Message,strTmp.c_str());
	}
	if (MatrixShow[REGISTRY_MSG_USER])
	{
		DWORD len=UNLEN+1;
		char* strUserName=new char[len];
		GetUserName(strUserName, &len);
		std::string str=strUserName;
		std::string strTmp=strOrig1;
		strTmp.append(str);
		strTmp.append(strOrig2);
		strTmp.append(str);
		strTmp.append("..    \r\n");
		delete strUserName;
		strcpy(Message,strTmp.c_str());
	}
	
	return Message;
}
