// ScreensaverApp.cpp: implementation of the ScreensaverApp class.
//
//////////////////////////////////////////////////////////////////////
#include "ScreensaverApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	std::vector<MonitorInfo*> ScreensaverApp::vecDisplays;
	bool ScreensaverApp::isInitialized=false;

ScreensaverApp::ScreensaverApp()
{
	if (!isInitialized)
		initialize();
}

ScreensaverApp::~ScreensaverApp()
{
	for (unsigned int x=0;x<vecDisplays.size();x++)
	{
		delete[] vecDisplays[x]->bmapinfo;
		delete[] vecDisplays[x]->mem;
		delete vecDisplays[x];
	}
	isInitialized=false;
}

// is Called before Application runs and windows are showed up should be used to
// load settings, or Files
int ScreensaverApp::init()
{
	CRegistry::InitDefaults();
	CRegistry::ReadRegistry();
	return 0;
}


// is Called before Application exists should be used to
// save settings, and cleanup/ freeing Memory/Handles
int ScreensaverApp::exit()
{
	return 0;
}

int ScreensaverApp::run()
{

	int retVal=0;

	switch (iScreensaverMode)
	{
		case	SS_MODE_PREVIEW:	// PreviewWindow .........
		{
			RECT rcPos;

			GetClientRect(parentHwnd, &rcPos);
			vecDisplays[0]->Window.setStyles(0,0);
			vecDisplays[0]->Window.setParentHandle(parentHwnd);
			vecDisplays[0]->Window.setPosition(rcPos);
			vecDisplays[0]->Window.setScreensaverMode(iScreensaverMode);

			if (vecDisplays[0]->Window.createWindow())
				retVal=vecDisplays[0]->Window.MessageLoop();
		}
		break;
		case	SS_MODE_PASSWORD:	// Password is changing (only for old Win95/98ME)......
		{
			HINSTANCE mpr = LoadLibrary( "MPR.dll");

			typedef DWORD (FAR PASCAL *PWCHGPROC)( LPCTSTR, HWND, DWORD, LPVOID );

			if( mpr )
			{
				PWCHGPROC pwd = (PWCHGPROC)GetProcAddress( mpr, "PwdChangePasswordA" );
				if( pwd )
					pwd( TEXT("SCRSAVE"), parentHwnd, 0, NULL );
				FreeLibrary( mpr );
			}
		}	break;
		case	SS_MODE_SAVER:		// the full screen Screensaver is running........
		{
			if (!isSingleInstance())
				return retVal;

			if (CRegistry::MatrixShow[REGISTRY_CLONE])
			{
				for (unsigned int x=0;x<vecDisplays.size();x++)
				{
					vecDisplays[x]->Window.setScreensaverMode(iScreensaverMode);
					vecDisplays[x]->Window.createWindow();
				}
			} else {
				RECT rcAll;
				SetRect(&rcAll,0,0,0,0);
				for (unsigned int x=0;x<vecDisplays.size();x++)
				{
					RECT tmp=vecDisplays[x]->rcMonitor;
					tmp.bottom+=tmp.top;		// convert from x/y, w,h to x1/y1, x2/y2
					tmp.right+=tmp.left;
					if (tmp.left<rcAll.left)
						rcAll.left=tmp.left;
					if (tmp.top<rcAll.top)
						rcAll.top=tmp.top;
					if (tmp.right>rcAll.right)
						rcAll.right=tmp.right;
					if (tmp.bottom>rcAll.bottom)
						rcAll.bottom=tmp.bottom;
				}
				rcAll.bottom-=rcAll.top;
				rcAll.right-=rcAll.left;
				vecDisplays[0]->Window.setPosition(rcAll);
				vecDisplays[0]->Window.setScreensaverMode(iScreensaverMode);
				vecDisplays[0]->Window.createWindow();
			}
		}
		retVal=vecDisplays[0]->Window.MessageLoop();

		break;
		case	SS_MODE_CONFIG:		// the configDlg will be shown...
			retVal=DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG),parentHwnd,DialogProc);
			if (retVal==-1)
				retVal=GetLastError();
		break;
		default:
			return MessageBox(NULL,"No Screensaver-Mode Found","Screensaver",MB_OK);
	}

	return retVal;
}

// this is the static initialize phase is called via constructor
// Has to occur BEFORE init()
// manages to detect Multimonitorsystems, and ScreensaverMode..
void ScreensaverApp::initialize()
{
	iScreensaverMode=InterpreteCommandLine();

	BOOL	blnCloneMode=CRegistry::MatrixShow[REGISTRY_CLONE];

	EnumDisplayMonitors(GetDC(NULL),NULL,(MONITORENUMPROC) MonitorEnum, (long)&blnCloneMode);

	SetCursor(NULL);

}

void initDlg(HWND hDlg);
void readDlg(HWND hDlg);

BOOL ScreensaverApp::DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL retval=0;
	switch (uMsg)
    {
	case WM_INITDIALOG:
		{
			initDlg(hDlg);
		}break;
	case WM_COMMAND:
			HWND tmp;
      switch (LOWORD(wParam))
      {
				case ID_DEFAULT:
					CRegistry::InitDefaults();
					initDlg(hDlg);
					return TRUE;
				case IDC_CODE:
					CRegistry::MatrixShow[REGISTRY_CODE]=!CRegistry::MatrixShow[REGISTRY_CODE];
					tmp=GetDlgItem(hDlg, IDC_MTX_GLITCH);
					EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_CODE]);
					return false;
				case IDC_MESSAGE:
					CRegistry::MatrixShow[REGISTRY_MESSAGE]=!CRegistry::MatrixShow[REGISTRY_MESSAGE];
					if (CRegistry::MatrixShow[REGISTRY_MESSAGE])
						SendDlgItemMessage(hDlg, IDC_EDIT,EM_SETREADONLY,IsDlgButtonChecked(hDlg, IDC_MSG_CUSTOM)==BST_CHECKED? FALSE:TRUE,0);
					else
						SendDlgItemMessage(hDlg, IDC_EDIT,EM_SETREADONLY,TRUE,0);
					tmp=GetDlgItem(hDlg, IDC_MSG_CUSTOM);
					EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
					tmp=GetDlgItem(hDlg, IDC_MSG_ORIG);
					EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
					tmp=GetDlgItem(hDlg, IDC_MSG_USER);
					EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
					return false;
				case IDC_MSG_CUSTOM:
				case IDC_MSG_ORIG:
				case IDC_MSG_USER:
					SendDlgItemMessage(hDlg, IDC_EDIT,EM_SETREADONLY,(CRegistry::MatrixShow[REGISTRY_MESSAGE])&&(IsDlgButtonChecked(hDlg, IDC_MSG_CUSTOM)==BST_CHECKED? FALSE:TRUE),0);
					return false;
				case IDC_PHONE:
					CRegistry::MatrixShow[REGISTRY_PHONE]=!CRegistry::MatrixShow[REGISTRY_PHONE];
					SendDlgItemMessage(hDlg, IDC_TELNO,EM_SETREADONLY,CRegistry::MatrixShow[REGISTRY_PHONE]?FALSE:TRUE,0);
					tmp=GetDlgItem(hDlg, IDC_ACT_TIME);
					EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_PHONE]);
					return false;
				break;
					case IDOK:
						readDlg(hDlg);
						CRegistry::WriteRegistry();
			    case IDCANCEL:
		        EndDialog(hDlg, wParam);
		        retval=TRUE;
      }
    }
	return retval;
}


bool ScreensaverApp::MonitorEnum(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MonitorInfo* tmp=new MonitorInfo();
	tmp->hMonitor=hMonitor;
	tmp->dwData=dwData;
	tmp->hdcMonitor=hdcMonitor;
	tmp->rcMonitor= *lprcMonitor;
	// change Virtual Coords to x/y/Width/height..as we need them to position the windows..
	tmp->rcMonitor.bottom=tmp->rcMonitor.bottom - tmp->rcMonitor.top;
	tmp->rcMonitor.right=tmp->rcMonitor.right - tmp->rcMonitor.left;

	tmp->Window.setPosition(tmp->rcMonitor);

	// grabbing the screen of this Monitor and save it (may be for using it in the Screensaver..)
	int resX=GetDeviceCaps(hdcMonitor,HORZRES);
	int resY=GetDeviceCaps(hdcMonitor,VERTRES);
	int bplane=GetDeviceCaps(hdcMonitor,BITSPIXEL);
	HBITMAP bmp=CreateCompatibleBitmap(hdcMonitor,resX,resY);
	HDC secDC=CreateCompatibleDC(hdcMonitor);
	HBITMAP oldbmp=(HBITMAP)SelectObject(secDC,bmp);
	int i=BitBlt(secDC,0,0,resX,resY,hdcMonitor,lprcMonitor->left,lprcMonitor->top,SRCCOPY);

	// Now packing the screeninto a DIB ...
	tmp->bmapinfo=(BITMAPINFO*)new unsigned char[sizeof(BITMAPINFOHEADER)+3*256];
	memset(&(tmp->bmapinfo->bmiHeader),0,sizeof(BITMAPINFOHEADER));
	tmp->bmapinfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	tmp->bmapinfo->bmiHeader.biWidth=tmp->rcMonitor.right;
	tmp->bmapinfo->bmiHeader.biHeight=tmp->rcMonitor.bottom;
	tmp->bmapinfo->bmiHeader.biPlanes=1;
	tmp->bmapinfo->bmiHeader.biBitCount=32;
	tmp->bmapinfo->bmiHeader.biCompression=BI_BITFIELDS;

	SelectObject(secDC,oldbmp);

	tmp->mem=new unsigned char[tmp->rcMonitor.bottom*tmp->rcMonitor.right*4];
	i=GetDIBits(secDC,bmp,0,tmp->rcMonitor.bottom, tmp->mem,tmp->bmapinfo, DIB_RGB_COLORS );

	// This will be removed...
	tmp->Window.mem=tmp->mem;
	tmp->Window.binfo=tmp->bmapinfo;

	DeleteDC(secDC);
	DeleteObject(bmp);

	vecDisplays.push_back(tmp);
	return true;
}


//returns the Screensaver Mode running, passwort, Config or Preview
// and sets evtl. the ParentHwnd appropriate
int ScreensaverApp::InterpreteCommandLine()
{
	int ScrMode;
	char *comLine = GetCommandLine();
	if (*comLine=='\"')		// 1st: jump after the commands filename
	{	comLine++;
		while(*comLine != 0 && *comLine != '\"')
			comLine++;
	}else{
		while(*comLine!=0 && *comLine!=' ')
			comLine++;
	}
	if (*comLine!=0)
		comLine++;
	while (*comLine==' ')	// 2nd ignore spaces..
		comLine++;
	if (*comLine==0)		// 3rd This was all? then config screens as default
	{	ScrMode = SS_MODE_CONFIG;
		parentHwnd = NULL;
	}else{
		if(*comLine=='-' || *comLine=='/')	// 4th No there is a parameter
			comLine++;

		if(*comLine=='p' || *comLine=='P' || *comLine=='l' || *comLine=='L')	//5th is it p or L? then it is preview
		{
			comLine++;
			while(*comLine==' ' || *comLine==':')
				comLine++;
			parentHwnd=(HWND)atoi(comLine);			// the parent window
      		ScrMode = SS_MODE_PREVIEW;
		}else if (*comLine=='s' || *comLine=='S')	// 6th: S show the screensaver
		{
			ScrMode = SS_MODE_SAVER;
		}else if (*comLine=='c' || *comLine=='C')	// 7th C show the Config
		{
			comLine++;
			while(*comLine==' ' || *comLine==':')
				comLine++;
			if(*comLine == 0)
				parentHwnd = GetForegroundWindow();
			else
				parentHwnd = (HWND)atoi(comLine);			// here is the parent Window
			ScrMode = SS_MODE_CONFIG;
		}else if(*comLine=='a' || *comLine=='A')	// 8 th this is the password Window
		{
			comLine++;
			while(*comLine==' ' || *comLine==':')
				comLine++;
			parentHwnd = (HWND)atoi(comLine);
			ScrMode = SS_MODE_PASSWORD;
		} else
			return -1;
	}
	return ScrMode;
}


// **************************** CONFIGURATIONSDIALOG ************************************
void initDlg(HWND hDlg)
{
	SetDlgItemText(hDlg, IDC_EDIT,		CRegistry::Message);
	SetDlgItemText(hDlg, IDC_TELNO,		CRegistry::TelNo);
	CheckDlgButton(hDlg, IDC_TITLE,		CRegistry::MatrixShow[REGISTRY_TITLE]);
	CheckDlgButton(hDlg, IDC_PHONE,		CRegistry::MatrixShow[REGISTRY_PHONE]);
	CheckDlgButton(hDlg, IDC_MESSAGE,	CRegistry::MatrixShow[REGISTRY_MESSAGE]);
	CheckDlgButton(hDlg, IDC_CODE ,		CRegistry::MatrixShow[REGISTRY_CODE]);
	CheckDlgButton(hDlg, IDC_SFX ,		CRegistry::MatrixShow[REGISTRY_SFX]);

	SendDlgItemMessage(hDlg, IDC_TELNO,EM_SETREADONLY,!CRegistry::MatrixShow[REGISTRY_PHONE],0);

	// V2.2 advanced Controls
	CheckDlgButton(hDlg, IDC_CLONE ,	CRegistry::MatrixShow[REGISTRY_CLONE]);
	CheckDlgButton(hDlg, IDC_VIRTUAL ,	CRegistry::MatrixShow[REGISTRY_VIRTUAL]);
	CheckDlgButton(hDlg, IDC_MSG_CUSTOM,CRegistry::MatrixShow[REGISTRY_MSG_CUSTOM]);
	CheckDlgButton(hDlg, IDC_MSG_USER ,	CRegistry::MatrixShow[REGISTRY_MSG_USER]);
	CheckDlgButton(hDlg, IDC_MSG_ORIG ,	CRegistry::MatrixShow[REGISTRY_MSG_ORIG]);
	CheckDlgButton(hDlg, IDC_ACT_TIME ,	CRegistry::MatrixShow[REGISTRY_ACT_TIME]);
	CheckDlgButton(hDlg, IDC_MTX_GLITCH,CRegistry::MatrixShow[REGISTRY_MTX_GLITCH]);

	SendDlgItemMessage(hDlg, IDC_MSG_CUSTOM,EM_SETREADONLY,!CRegistry::MatrixShow[REGISTRY_MESSAGE],0);
	SendDlgItemMessage(hDlg, IDC_MSG_USER,EM_SETREADONLY,!CRegistry::MatrixShow[REGISTRY_MESSAGE],0);
	SendDlgItemMessage(hDlg, IDC_MSG_ORIG,EM_SETREADONLY,!CRegistry::MatrixShow[REGISTRY_MESSAGE],0);

	SendDlgItemMessage(hDlg, IDC_ACT_TIME,EM_SETREADONLY,!CRegistry::MatrixShow[REGISTRY_PHONE],0);

	if (CRegistry::MatrixShow[REGISTRY_MESSAGE])
		SendDlgItemMessage(hDlg, IDC_EDIT,EM_SETREADONLY,IsDlgButtonChecked(hDlg, IDC_MSG_CUSTOM)==BST_CHECKED? FALSE:TRUE,0);
	else
		SendDlgItemMessage(hDlg, IDC_EDIT,EM_SETREADONLY,TRUE,0);

	HWND tmp=GetDlgItem(hDlg, IDC_MSG_CUSTOM);
	EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
	tmp=GetDlgItem(hDlg, IDC_MSG_ORIG);
	EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
	tmp=GetDlgItem(hDlg, IDC_MSG_USER);
	EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_MESSAGE]);
	tmp=GetDlgItem(hDlg, IDC_ACT_TIME);
	EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_PHONE]);
	tmp=GetDlgItem(hDlg, IDC_MTX_GLITCH);
	EnableWindow(tmp,CRegistry::MatrixShow[REGISTRY_CODE]);
}

void readDlg(HWND hDlg)
{
	char* cMessage=new char[1024];
	delete CRegistry::TelNo;
	CRegistry::TelNo = new char[12];
	GetDlgItemText(hDlg, IDC_EDIT, cMessage, 1023);
	CRegistry::Message=cMessage;
	GetDlgItemText(hDlg, IDC_TELNO, CRegistry::TelNo, 11);
	//MessageBox(NULL, CRegistry.TelNo,"TextReaded:", MB_OK);
	CRegistry::MatrixShow[REGISTRY_SFX]		=IsDlgButtonChecked(hDlg, IDC_SFX  )==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_TITLE]	=IsDlgButtonChecked(hDlg, IDC_TITLE)==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_PHONE]	=IsDlgButtonChecked(hDlg, IDC_PHONE)==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_MESSAGE]	=IsDlgButtonChecked(hDlg, IDC_MESSAGE)==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_CODE]	=IsDlgButtonChecked(hDlg, IDC_CODE )==BST_CHECKED? true:false;

	CRegistry::MatrixShow[REGISTRY_CLONE]			=IsDlgButtonChecked(hDlg, IDC_CLONE)			==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_VIRTUAL]		=IsDlgButtonChecked(hDlg, IDC_VIRTUAL)		==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_MSG_CUSTOM]=IsDlgButtonChecked(hDlg, IDC_MSG_CUSTOM)	==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_MSG_USER]	=IsDlgButtonChecked(hDlg, IDC_MSG_USER)		==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_MSG_ORIG]	=IsDlgButtonChecked(hDlg, IDC_MSG_ORIG)		==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_ACT_TIME]	=IsDlgButtonChecked(hDlg, IDC_ACT_TIME)		==BST_CHECKED? true:false;
	CRegistry::MatrixShow[REGISTRY_MTX_GLITCH]=IsDlgButtonChecked(hDlg, IDC_MTX_GLITCH)	==BST_CHECKED? true:false;
}


bool ScreensaverApp::isSingleInstance()
{
	HWND hn=NULL;
	hn=FindWindow(NULL,"Matrix-Screensaver");	// TODO: get get strTitle from the Windowclass...
	return (hn==NULL);
}
