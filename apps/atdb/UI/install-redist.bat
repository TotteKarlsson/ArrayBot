@echo off 

set AMAZONIX_ROOT=C:\DSReleases\code\Amalytico
set OUTPUTDIR=C:\DSReleases\finals\Amalytico\current
set BDSCOMMONDIR=C:\DSReleases\install\xe3_ide
set RELEASE_INSTALL=C:\DSReleases\install\Release

echo %AMAZONIX_ROOT%
echo %OUTPUTDIR%
echo %BDSCOMMONDIR%
echo %RELEASE_INSTALL%

copy %AMAZONIX_ROOT%\DataBases\amazon.db %OUTPUTDIR%
xcopy %AMAZONIX_ROOT%\DataBases\*.ini %OUTPUTDIR% /y
xcopy %AMAZONIX_ROOT%\PythonSource\fetch*.py %OUTPUTDIR%\python_source\ /yi
xcopy *.txt %OUTPUTDIR% /y
copy %BDSCOMMONDIR%\BPL\*.bpl %OUTPUTDIR% /y
xcopy %RELEASE_INSTALL%\bin\mtk*.dll %OUTPUTDIR% /y
xcopy %AMAZONIX_ROOT%\Redist\* %OUTPUTDIR% /yie
xcopy %AMAZONIX_ROOT%\Help\*.chm %OUTPUTDIR% /yie

