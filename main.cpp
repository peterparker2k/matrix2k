
#include <windows.h>
#include <math.h>
#include "ScreensaverApp.h"
#include "resource.h"
//#define	 COMPILE_MULTIMON_STUBS	// so we define multimonitorstubs for win95..
#include "multimonitor.h"

int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{

	ScreensaverApp myApp;
	myApp.init();

	myApp.run();

	myApp.exit();

	return 0;
}



			 