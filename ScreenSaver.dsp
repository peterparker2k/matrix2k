# Microsoft Developer Studio Project File - Name="ScreenSaver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ScreenSaver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScreenSaver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScreenSaver.mak" CFG="ScreenSaver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScreenSaver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ScreenSaver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScreenSaver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 OpenGL32.lib GLu32.lib GLaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib winmm.lib /nologo /subsystem:windows /profile /machine:I386 /out:"Release/ScreenSaver.scr"

!ELSEIF  "$(CFG)" == "ScreenSaver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ScreenSaver___Win32_Debug"
# PROP BASE Intermediate_Dir "ScreenSaver___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OpenGL32.lib GLu32.lib GLaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib winmm.lib /nologo /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "ScreenSaver - Win32 Release"
# Name "ScreenSaver - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BaseWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\Bob.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\MatrixGlitch.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\MatrixWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreensaverApp.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreensaverWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\Show.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix\StringLine.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BaseWindow.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\Bob.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\MatrixGlitch.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\MatrixWindow.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\resource.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\Screen.h
# End Source File
# Begin Source File

SOURCE=.\ScreensaverApp.h
# End Source File
# Begin Source File

SOURCE=.\ScreensaverWindow.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\Show.h
# End Source File
# Begin Source File

SOURCE=.\Matrix\StringLine.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\B_T.bmp
# End Source File
# Begin Source File

SOURCE=.\Cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\Icon1.ico
# End Source File
# Begin Source File

SOURCE=.\ScreenSaver.rc
# End Source File
# Begin Source File

SOURCE=.\Sprtdata.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DialLoop.wav
# End Source File
# Begin Source File

SOURCE=.\FindNumber.wav
# End Source File
# Begin Source File

SOURCE=.\knockknock.wav
# End Source File
# Begin Source File

SOURCE=.\SearchNumbers.wav
# End Source File
# Begin Source File

SOURCE=.\Title_mini.wav
# End Source File
# End Target
# End Project
