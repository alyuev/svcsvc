@echo off
rem Сборка svcsvc.dll (Release, MBCS, MFC80 DLL) в VS2005 без регистрации в системе.
rem Результат: ReleaseMinDependency\svcsvc.dll
setlocal
cd /d "%~dp0"
call "%VS80COMNTOOLS%vsvars32.bat" >nul || (echo VS2005 not found & exit /b 1)
set OUT=ReleaseMinDependency
if not exist %OUT% mkdir %OUT%
cl /nologo /c /O1 /Ob1 /GF /Gy /EHsc /MD /W3 /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D _AFXDLL /D _MBCS /Fo%OUT%\ /Fd%OUT%\ StdAfx.cpp FilterDlg.cpp SelectDlg.cpp Service.cpp svcsvc.cpp || exit /b 1
rc /d NDEBUG /d _AFXDLL /l 0x419 /fo%OUT%\svcsvc.res svcsvc.rc || exit /b 1
link /nologo /DLL /OPT:REF /OPT:ICF /FileAlign:512 /SUBSYSTEM:WINDOWS /MACHINE:X86 /DEF:svcsvc.def /MANIFEST /MANIFESTFILE:%OUT%\svcsvc.dll.manifest /OUT:%OUT%\svcsvc.dll /IMPLIB:%OUT%\svcsvc.lib /PDB:%OUT%\svcsvc.pdb /DEBUG %OUT%\*.obj %OUT%\svcsvc.res version.lib || exit /b 1
mt /nologo -manifest %OUT%\svcsvc.dll.manifest -outputresource:%OUT%\svcsvc.dll;#2 || exit /b 1
echo OK: %OUT%\svcsvc.dll
