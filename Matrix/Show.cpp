// Show.cpp: implementation of the Show class.
//
//////////////////////////////////////////////////////////////////////

#include "Show.h"
#include "../resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Show::iShowType=0;
int Show::m_iPrintManagerCount=0;
int Show::iWindowIDCounter=0;

Show::Show(int w, int h) : CScreen(w,h)
{
	m_ptrLines = new CStringLine[Width];
	for (int x=0; x<Width;x++)
		m_ptrLines[x].SetHeight(Height);
	intPause=iShowType=0;
	ResetPrintManager();
	initMessage();
	iID=iWindowIDCounter++;
}

Show::~Show()
{
	delete[] m_ptrLines;
}

void Show::ResetPrintManager()
{
	m_iPrintManagerCount=0;
}

//###################### Show Funktionen ###############################
/*
          HIER SIND DIE MATRIX SHOW FUNCTIONS!!!!

*/

bool Show::ShowTheMatrix(bool timeout)
{
	static int iTimer=-1;
	int y,type;
	SetCrypto(true);

	UpdateArea->left=0;
	UpdateArea->top	=0;
	UpdateArea->right=Width;
	UpdateArea->bottom=Height;

	for (int x=0;x<Width;x++)
	{
		VPrint(x,0,m_ptrLines[x].DisplayString(),0);
		y=2*Height-m_ptrLines[x].GetPosY();

		type=m_ptrLines[x].GetBlinkType();
		switch(type)
		{
		case 0:
			SetIntensity(x,y-1, 2);
			break;
		case 1:
			SetIntensity(x,y, 2);
			AddChar(x,y,rand()%25);
			break;
		case 2:
			SetIntensity(x,y, 3);
			break;
		case 3:
			SetIntensity(x,y, 3);
			AddChar(x,y,rand()%25);
			break;
		default:
			break;
		}
	}

// wake the glitch
	if (glitch.iTimer==0 && glitch.iSleep!=0 && timeGetTime()>glitch.iSleep)
	{
		glitch.iTimer=-1;
		glitch.iSleep=0;
	}
	//	init the glitch
	if (glitch.iTimer==-1 && glitch.iSleep==0)
	{
		glitch.iTimer=timeGetTime();
		glitch.xc=rand()%Width;
		glitch.yc=rand()%Height;
		glitch.w=10;
		glitch.h=3;
	}

	if (glitch.iSleep==0 && timeGetTime()-glitch.iTimer>10){
		glitch.w*=1.2;
		glitch.h=glitch.w/1.5;
		glitch.iTimer=timeGetTime();
		if (glitch.w>2*Width){
			glitch.iTimer=0;
			glitch.iSleep=timeGetTime()+6000+( (rand()%10000) -5000) ;
		}
	}
	// drawing the glitch....
	if (CRegistry::MatrixShow[REGISTRY_MTX_GLITCH])
	{
		for (int a=0; a<3; a++)
		{
			for (int x=-a;x<glitch.w+a;x++){
				SetIntensity(glitch.xc-glitch.w/2+x,glitch.yc-glitch.h/2-a,3-a);
				SetIntensity(glitch.xc-glitch.w/2+x,glitch.yc+glitch.h/2+a,3-a);
			}
			for (int x=-a;x<glitch.h+a;x++){
				SetIntensity(glitch.xc-glitch.w/2-a,glitch.yc-glitch.h/2+x,3-a);
				SetIntensity(glitch.xc+glitch.w/2+a,glitch.yc-glitch.h/2+x,3-a);
			}
		}
		for (int a=1; a<3; a++)
		{
			for (int x=a;x<glitch.w-a;x++){
				SetIntensity(glitch.xc-glitch.w/2+x,glitch.yc-glitch.h/2+a,3-a);
				SetIntensity(glitch.xc-glitch.w/2+x,glitch.yc+glitch.h/2-a,3-a);
			}
			for (int x=a;x<glitch.h-a;x++){
				SetIntensity(glitch.xc-glitch.w/2+a,glitch.yc-glitch.h/2+x,3-a);
				SetIntensity(glitch.xc+glitch.w/2-a,glitch.yc-glitch.h/2+x,3-a);
			}
		}
	}
	Print (-1,-1,"");
	if (timeout){
		if (iTimer==-1)
			iTimer=timeGetTime();
		if (timeGetTime()-iTimer>120000)
		{
			iTimer=-1;
			Print(0,0,"");
			return true;
		} else
			return false;
	}else{
		iTimer=-1;
		return false;
	}
}

bool Show::ShowPhone()
{
# define MESSAGENUM 4
	int		absLen,len[MESSAGENUM],tempLen;
	int	numberPos[11]={8,10,12,16,18,20,24,26,28,30,32};

	static bool DialOn=false;	//flag for SOUNDFX
	static bool SearchOn=false;		//flag for SOUNDFX
	static int foundNumber=0;		// Number of found digits..

	static int iTimer=-1;

	std::string	Message1=	"Call trans opt:";
	std::string	Message2=	"> received.";
	std::string	Message3=	"02-19-98  13:24:18  REC:Log";
	std::string	Message4=	"> Searching...";
	std::string	Message5=	"Found:  X X X   X X X   X X X X   ";
	std::string	Message6=	"Found:  3 5 2   5 5 5   0 6 9 0   ";
	std::string	NumString=  " Num:.. 0 0 0   0 0 0   0 0 0 0   ";
	std::string	strNumber=  "                                  ";
	std::string*	Field [MESSAGENUM]={&Message1, &Message2, &Message3, &Message4};


	if (CRegistry::MatrixShow[REGISTRY_ACT_TIME])
		Message3=getActualTimeString();

	unsigned int	matchTimer[]={1700,2600,3400,3900,4600,5600,6800,7400,8000,8500};

	// Falls der String kürzer als 10 ist, alle ausgaben kürzen..
	int SearchReady=strlen(CRegistry::TelNo);
	Message5[numberPos[SearchReady]]='\0';
	NumString[numberPos[SearchReady]]='\0';
	Message6[numberPos[SearchReady]]='\0';

	// Erstmal den Registry String in die Message6 kopieren...
	for (int x=0;x<SearchReady;x++)
	{
		Message6[numberPos[x]]=CRegistry::TelNo[x];
	}

	if (iShowType==iOldType)
	{
		UpdateArea->left=0;
		UpdateArea->top	=0;
		UpdateArea->right=34;
		UpdateArea->bottom=Height;
	}

	if (foundNumber!=SearchReady)
	{
		SetCrypto(false);
		absLen=m_iPrintManagerCount;		// Anzahl der Zeichen die ausgegeben werden..
		for (int a=0; a<MESSAGENUM ; a++)
		{
			tempLen=Field[a]->length();
			if (absLen>tempLen)
			{
				len[a]=tempLen;
				absLen-=tempLen;
			}
			else
			{
				len[a]=absLen;
				absLen=0;
			}
			PrintLen(0,a,*Field[a],len[a],0);
		}
		if (len[MESSAGENUM-1]==tempLen)	//Wenn alle Strings gedruckt worden sind.....
		{
			if (iTimer==-1)
				iTimer=timeGetTime();
			if (!SearchOn) {
				PlaySound(NULL, GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
				if (CRegistry::MatrixShow[REGISTRY_SFX])
					PlaySound(MAKEINTRESOURCE (ID_SOUND_SEARCH), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC | SND_LOOP);
				SearchOn=true;
			}
			Scroll(MESSAGENUM+1);
			Print(0, Height-1,NumString,1);
			Print(0,4,Message5,1);

			for (int a=0; a<1000;a++)			//Number racing Glitter FX
			{
				SetIntensity(rand()%20+numberPos[foundNumber], rand()%(Height-5)+6,rand()%4);
			}

			for (int a=0;a<SearchReady;a++)
			{
				if (a<foundNumber)
					strNumber[0]=Message6[numberPos[a]];
				else
					strNumber[0]=((rand()%10)+'0');

				PrintLen(numberPos[a], Height-1,strNumber,1,1);
			}

			for (int a=0;a<foundNumber;a++)
			{
				strNumber[0]=Message6[numberPos[a]];
				for (int b=5;b<Height;b++)
					PrintLen(numberPos[a], b,strNumber,1,1);
			}

			if (iID==0)
			{
				if (timeGetTime()-iTimer > matchTimer[foundNumber])
				{
					strNumber[0]=Message6[numberPos[foundNumber]];
					for (int a=5;a<Height;a++)
						PrintLen(numberPos[foundNumber], a,strNumber,1,1);

					foundNumber++;
					if (foundNumber>SearchReady) foundNumber=SearchReady;

					PlaySound(NULL, GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
					if (CRegistry::MatrixShow[REGISTRY_SFX])
						PlaySound(MAKEINTRESOURCE (ID_SOUND_FIND), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
					SearchOn=false;
				}
			}
			PrintLen(0,4,Message6,numberPos[foundNumber],2);
		} else {
			if (!DialOn) {
				PlaySound(NULL, GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
				if (CRegistry::MatrixShow[REGISTRY_SFX])
					PlaySound(MAKEINTRESOURCE (ID_SOUND_DIAL), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
				DialOn=true;
			}
		}
		SetIntensity(0,1,3);
		SetIntensity(0,3,3);
		if (iID==0)
			m_iPrintManagerCount++;
	}

	if (foundNumber==SearchReady)
	{
		DialOn=false;
		SearchOn=false;
		iTimer=-1;
		foundNumber=0;
		Clear();
		ResetPrintManager();
		return true;
	}else return false;
}

void Show::initMessage()		//Registry Text vorbereiten: \r\n entfernen und durch \0 erstezen und in ein Array packen...
{
	std::string NewMessage;
	int tempLen=strlen(CRegistry::getMessage())+1;
	int index=0;

	if (tempLen<=0)
		MessageRows=-1;
	else
	{
		int index=0;	// remember start of next Line..
		for (int a=0; a<tempLen; a++)	// replace all \r\n  to \0 and pack it in std::string
		{
			if (CRegistry::Message[a]=='\n' || CRegistry::Message[a]=='\0')
			{
				bool blnCR=false;
				if (a>0)
					blnCR=(CRegistry::Message[a-1]=='\r');
				if (blnCR)
					a--;

				char cRemember=CRegistry::Message[a];
				CRegistry::Message[a]='\0';
				std::string tmp="";
				tmp.append(CRegistry::Message+index);
				if (tmp.length()>0)
					MessageText.push_back(tmp);

				CRegistry::Message[a]=cRemember;

				if (blnCR)
					a++;

				index=a+1;
			}
		}
	}
	MessageRows=MessageText.size();
	EmptyLine=new char[Width];		//Leerzeile erzeugen, die über den ganzen Screen reicht...
	for (int a=0;a<Width; a++)
		EmptyLine[a]=' ';
}

bool Show::ShowMessage()
{
	int	  absLen,tempLen,len;
	static long iTimer=-1;

	int	matchTimer[]={450,120,200,35,950,30,180,400,20,350};
// use this line for rapid typing..
//	int	matchTimer[]={45,12,20,35,90,30,18,40,20,35};

	if (iShowType==iOldType)
	{
		UpdateArea->left=0;
		UpdateArea->top	=0;
		UpdateArea->right=Width;
		UpdateArea->bottom=7;
	}

	if (m_iPrintManagerCount==0 && iTimer==-1)
		iTimer=timeGetTime();

	SetCrypto(false);
	absLen=m_iPrintManagerCount;
	Print(0,0,EmptyLine,0);
	for (int a=0; a<MessageRows; a++)
	{
		tempLen=MessageText[a].length();
		if (absLen>tempLen)
		{
			len=0;
			absLen-=tempLen;
		}
		else
		{
			// the last row will be printed at all
			if ((absLen>0) &&
				(iID==0) &&
				(intPause!=3000) &&
				(a==MessageRows-1) &&
				(CRegistry::MatrixShow[REGISTRY_MSG_CUSTOM]==false))
			{
				intPause=3000;// 3 sec pause for playing sample ...
				len=MessageText[a].length()-1;
				iTimer=timeGetTime();
				m_iPrintManagerCount+=len;
				if (CRegistry::MatrixShow[REGISTRY_SFX])
					PlaySound(MAKEINTRESOURCE (ID_SOUND_KNOCK), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);

			} else
			{
				if (intPause==-1)
				{
					intPause=matchTimer[m_iPrintManagerCount%10];
					iTimer=timeGetTime();
				}
				len=absLen;
				absLen=0;
			}
			PrintLen(0,0,MessageText[a],len,0);
		}
	}
	if (iID==0){	// only the first window controls the keyboard input..
		if ((int)(timeGetTime()-iTimer)>intPause)
		{
			m_iPrintManagerCount++;

			if (CRegistry::MatrixShow[REGISTRY_SFX])
				PlaySound(MAKEINTRESOURCE (ID_SOUND_FIND), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
			intPause=-1;
		}
	}

	tempLen=0;
	for (int  a=0; a<MessageRows ; a++)
		tempLen+=MessageText[a].length();

	if (m_iPrintManagerCount > tempLen && iID==0)
	{
		Clear();
		ResetPrintManager();
		Print(0,0," ");
		iTimer=-1;
		return true;
	}else
		return false;
}

bool Show::ShowTitle(bool fullscreen)	//Fullscreen means without matrix in Background...
{
# define MESSAGENUM3 6
	std::string	Message1="T h e  M a t r i x  -  R e l o a d e d#";
	std::string	Message2="Multi-Monitor Screensaver 2003";
	std::string	Message3="Movies by the Wachowski Brothers";
	std::string	Message4="Send Comments to:";
	std::string	Message5="burning_Thornbush@yahoo.com";
	std::string	Message6="http://www.angeltowns.com/members/thornbush";
	std::string	ClearMsg="                                       ";
	int		absLen,len,tempLen;

	static bool SoundStarted=false;		// flag for Sound FX

	std::string*	Field [MESSAGENUM3]={&Message1, &Message2, &Message3, &Message4, &Message5, &Message6};

	if (fullscreen)
	{
		UpdateArea->left=0;
		UpdateArea->top	=Height/2-2;
		UpdateArea->right=Width;
		UpdateArea->bottom=Height/2+3;
	} else {
		UpdateArea->left=0;
		UpdateArea->top	=0;
		UpdateArea->right=Width;
		UpdateArea->bottom=Height;
	}

	if (fullscreen && !SoundStarted)
	{
		if (CRegistry::MatrixShow[REGISTRY_SFX])
		{
			PlaySound(NULL, GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
			PlaySound(MAKEINTRESOURCE (ID_SOUND_TITLE), GetModuleHandle(NULL) ,SND_RESOURCE | SND_ASYNC);
			SoundStarted=true;
		}
	}

	absLen=m_iPrintManagerCount;
	Print((Width-ClearMsg.length())/2,Height/2,ClearMsg,0);
	for (int a=0; a<MESSAGENUM3 ; a++)
	{
		tempLen=Field[a]->length();
		if (absLen>tempLen)
		{
			len=0;
			absLen-=tempLen;
		}
		else
		{
			if ((tempLen==absLen) && (intPause==-1)) // Wenn ende der Pause und Ende der MessageZeile
				intPause=30;
			len=absLen;
			SetCrypto(false);

			PrintLen((Width-Field[a]->length())/2 ,Height/2 ,*Field[a] ,len,0);

			if (len!=tempLen)	//Flash Malen...
			{
				int charHell=15;
				for (int ch=len;ch>=1;ch--)
				{
					SetIntensity((Width-Field[a]->length())/2+ch ,Height/2 ,charHell/4);
					if (charHell>0) charHell--;
				}
			}

			if (tempLen==absLen)	//In der Pause...
			{
				int HellWert=0;
//				if (intPause>15)
					HellWert= (intPause<15) ? (intPause)/5 : 3-((intPause-15)/5);
				PrintLen((Width-Field[a]->length())/2 ,Height/2 ,*Field[a] ,len ,HellWert);
			}
			absLen=0;
			SetCrypto(true);
		}
	}

	if ((intPause--)<1) //Ende der Pause erreicht...?
	{
		if (iID==0)
			m_iPrintManagerCount++;
		intPause=-1;
	}

	tempLen=0;
	for (int a=0;a<MESSAGENUM3; a++)
		tempLen+=Field[a]->length();

	if (m_iPrintManagerCount>tempLen)
	{
		SoundStarted=false;
		Print(0,0," ");
		ResetPrintManager();
		return true;
	}else return false;
}


////////////////////////////////////////////////////////////////////////////////////////////

void Show::TheMatrixShow(int dTime)
{
	bool nextType;
	switch(iShowType)
	{
		case 0:
			if (CRegistry::MatrixShow[REGISTRY_TITLE]) {
				nextType	=	ShowTitle(true);
				if (nextType )
				{
						nextShow();
						iShowType=1;
				}
				break;
			} else
				iShowType=1;
		case 1:
			if (CRegistry::MatrixShow[REGISTRY_PHONE]){
				nextType	=	ShowPhone();
				if (nextType )
				{
						nextShow();
						iShowType=2;
				}
				break;
			} else
				iShowType=2;
		case 2:
			if (CRegistry::MatrixShow[REGISTRY_MESSAGE]){
				nextType	=	ShowMessage();
				if (nextType )
				{
						nextShow();
						iShowType=3;
				}
				break;
			} else
				iShowType=3;
		case 3:
			if (CRegistry::MatrixShow[REGISTRY_CODE]) {
				nextType	=	ShowTheMatrix();
				if (nextType )
				{
						nextShow(!CRegistry::MatrixShow[REGISTRY_TITLE]);
						iShowType=4;
				}
				break;
			} else
				iShowType=4;
		case 4:
			if (CRegistry::MatrixShow[REGISTRY_CODE] && CRegistry::MatrixShow[REGISTRY_TITLE]) {
				ShowTheMatrix(false);
				nextType	=	ShowTitle(false);
				if (nextType )
				{
						nextShow();
						iShowType=1;
				}
			}
			else
				iShowType=-1;	//Wird in if am Ende wieder auf 0 gesetzt...
	}

	if (iShowType>4)
		iShowType=1;
	if (iShowType <0)
		iShowType=0;
	if (iShowType!=iOldType)
	{
		iOldType=iShowType;
		nextShow();
	}
}

void Show::nextShow(bool blnClearScreen)
{
	if (blnClearScreen)
		Clear();
	ResetPrintManager();
}

std::string Show::getActualTimeString()
{
	std::string retVal="";
	char* strstd="02-19-98  13:24:18  REC:Log    ";
	char* strTmp=new char[strlen(strstd)];
	SYSTEMTIME myTime;
	GetLocalTime(&myTime);
	wsprintf(strTmp,"%02d-%02d-%02d  %02d:%02d:%02d  REC:Log",myTime.wMonth,myTime.wDay,myTime.wYear,myTime.wHour,myTime.wMinute, myTime.wSecond);
	retVal=strTmp;
	delete strTmp;
	return retVal;
}
