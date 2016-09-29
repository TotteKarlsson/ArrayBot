@echo off 

set OUTPUTDIR=P:\AppsDebug\Amalytico
set AMALYTICO_ROOT=P:\Amalytico
set BDSCOMMONDIR=P:\installs\xe3_ide
set DEBUG_INSTALL=p:\installs\debug
set USER_LOCAL_APPDATA=C:\Users\Totte\AppData\Local

echo %AMALYTICO_ROOT%
echo %OUTPUTDIR%
echo %BDSCOMMONDIR%
echo %RELEASE_INSTALL%

copy %AMALYTICO_ROOT%\DataBases\amalytico.db %USER_LOCAL_APPDATA%\Amalytico\
xcopy %AMALYTICO_ROOT%\PythonSource\fetch*.py %USER_LOCAL_APPDATA%\Amalytico\ /yi
xcopy *.txt %OUTPUTDIR% /y
copy %BDSCOMMONDIR%\BPL\*.bpl %OUTPUTDIR% /y
xcopy %RELEASE_INSTALL%\bin\mtk*.dll %OUTPUTDIR% /y
xcopy %AMALYTICO_ROOT%\Redist\* %OUTPUTDIR% /yie

