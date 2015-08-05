// ScreensaverWindow.cpp: implementation of the ScreensaverWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "ScreensaverWindow.h"
#include "ScreensaverApp.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ScreensaverWindow::ScreensaverWindow()
{
	iTimerRate=50;
	idTimer=0;
	isFirstFrame=true;
	mousePos.x=-1;
	mousePos.y=-1;
	blnUsePassword=true;	//only for WIn95...
	GetRegSettings();
}

ScreensaverWindow::~ScreensaverWindow()
{

}

void ScreensaverWindow::paint(HDC hdc)
{
}
void ScreensaverWindow::paintFirstFrame(HDC hdc)
{
		int i=SetDIBitsToDevice(hdc,
				0, 
				0, 
				rctPosition.right,
				rctPosition.bottom,
				0,0,
				0,
				rctPosition.bottom,
				mem,binfo,DIB_RGB_COLORS);
}
void ScreensaverWindow::paintPreview(HDC hdc)
{
}
void ScreensaverWindow::paintPreviewFirstFrame(HDC hdc)
{
	paintFirstFrame(hdc);
}

LRESULT ScreensaverWindow::windowProc(HWND hwnd,  UINT uMsg,   WPARAM wParam,  LPARAM lParam )
{
  switch (uMsg)
  {
	  case WM_CREATE:
	  {
	      idTimer=SetTimer(hwnd,0,iTimerRate,NULL);
	  } break;
	  case WM_TIMER:
	  { 
			HDC dc= GetDC(hwnd);
			if (isFirstFrame){
				switch (iScreensaverMode)
				{
					case SS_MODE_PREVIEW:
						paintPreviewFirstFrame(dc);
					break;
					case SS_MODE_SAVER:
						paintFirstFrame(dc);
						break;
				}
				isFirstFrame=false;
			}else{
				switch (iScreensaverMode)
				{
					case SS_MODE_PREVIEW:
						paintPreview(dc);
					break;
					case SS_MODE_SAVER:
						paint(dc);
					break;
				}
			}
			ReleaseDC(hwnd, dc);
	  } break;

	  case WM_MOUSEMOVE:
		{
			if (iScreensaverMode!=SS_MODE_SAVER)
				break;
			if (mousePos.x==-1 && mousePos.y==-1)
			{
				mousePos.x = LOWORD(lParam);  // horizontal position of cursor 
				mousePos.y = HIWORD(lParam);  // vertical position of cursor 
				break;
			}else{
				int PosX = LOWORD(lParam);  
				int PosY = HIWORD(lParam);  
				if (abs(mousePos.x-PosX)<1 && abs(mousePos.y-PosY)<1)
					break;
			}
		}
 	  case WM_MBUTTONDOWN:
	  case WM_RBUTTONDOWN:
	  case WM_LBUTTONDOWN:
	  case WM_KEYDOWN:
	  case WM_SYSKEYDOWN:
	  case WM_CHAR:
	  case WM_CLOSE:
		{
			static bool blnPasswordChecking=false;
			if (iScreensaverMode==SS_MODE_PREVIEW) 
				break;
			if ((blnUsePassword == 0) && (iScreensaverMode==SS_MODE_SAVER))
				DestroyWindow( hwnd );
			// prevents this function from being called recursively
			if( blnPasswordChecking == false )
			{
				blnPasswordChecking = true;
				KillTimer(hWnd,idTimer); // stop timer during password check
				SendMessage( hWnd, WM_SETCURSOR, 0, 0 );
				BOOL blnPasswordVerified = VerifyPassword( hwnd );
				if( blnPasswordVerified )
					DestroyWindow( hwnd ); // password was correct (or NT)
				else
				{
					// restart screen saver
					SetTimer(hwnd,idTimer, iTimerRate,NULL);
					blnPasswordChecking = false;
					SendMessage( hWnd, WM_SETCURSOR, 0, 0 );
					return FALSE;
				}
			}
			else
				return FALSE; // return if password dialog is up already
		}	break;
	  case WM_DESTROY:
			PostQuitMessage(0);
			if (idTimer!=0) 
				KillTimer(hwnd,idTimer); 
			idTimer=0;

	}
	LRESULT retVal=DefWindowProc(hwnd, uMsg, wParam, lParam);
	return retVal;
}

void ScreensaverWindow::setScreensaverMode(int i)
{
	iScreensaverMode=i;
}


// added 3.23.00 by Ivo Roper
// and modified 3.24.00
void ScreensaverWindow::GetRegSettings()
{
	// this code found and described at:
	//		http://chesworth.com/pv/os/windows/creating_screen_savers.htm

    LONG res;
	HKEY skey;
	DWORD valtype, valsize, val;

    res = RegOpenKeyEx( HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, 
						KEY_ALL_ACCESS, &skey );
    if( res != ERROR_SUCCESS )
		return;
    valsize = sizeof( val );
	res = RegQueryValueEx( skey, "ScreenSaveUsePassword", 0, &valtype, 
						   (LPBYTE)&val, &valsize );
	if( res == ERROR_SUCCESS )
		blnUsePassword = val;	// if successful we know if a password is required
	RegCloseKey( skey );
}

BOOL ScreensaverWindow::VerifyPassword(HWND hwnd)
{
	// this code found and described at:
	//		http://chesworth.com/pv/os/windows/creating_screen_savers.htm

	// Under NT, we return TRUE immediately. This lets the saver quit,
	// and the system manages passwords. Under '95, we call VerifyScreenSavePwd.
	// This checks the appropriate registry key and, if necessary,
	// pops up a verify dialog
	OSVERSIONINFO osv; 
	osv.dwOSVersionInfoSize=sizeof(osv); 
	GetVersionEx(&osv);

	HINSTANCE hpwdcpl=::LoadLibrary("PASSWORD.CPL");
	if (hpwdcpl==NULL) 
	{
//		DEBUG("Unable to load PASSWORD.CPL. Aborting\n");
		return TRUE;
	}

	typedef BOOL (WINAPI *VERIFYSCREENSAVEPWD)(HWND hwnd);
	VERIFYSCREENSAVEPWD VerifyScreenSavePwd;
	VerifyScreenSavePwd=
		(VERIFYSCREENSAVEPWD)GetProcAddress(hpwdcpl,"VerifyScreenSavePwd");
	if (VerifyScreenSavePwd==NULL)
	{
//		Debug("Unable to get VerifyPwProc address. Aborting\n");
		FreeLibrary(hpwdcpl);
		return TRUE;
	}
//	Debug("About to call VerifyPwProc");
/*	if( DrawObj->dd == NULL )
		return TRUE;
	// Force direct draw to cooperate with the Password dialog (Win9x) -Ivo
	DrawObj->dd->SetCooperativeLevel( hwnd, DDSCL_NORMAL );
*/
	SetWindowPos( hwnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE );
    ShowCursor( TRUE );
	// call PASSWORD.CPL library function -Ivo
	BOOL bres=VerifyScreenSavePwd(hwnd);
	
	ShowCursor( FALSE ) ;
	FreeLibrary(hpwdcpl);

	return bres;
}


///////////////////////////////////////////////////////////////////////////////////////////////
