@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by UCM1B0.HPJ. >"hlp\ucm1b0.hm"
echo. >>"hlp\ucm1b0.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ucm1b0.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ucm1b0.hm"
echo. >>"hlp\ucm1b0.hm"
echo // Prompts (IDP_*) >>"hlp\ucm1b0.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ucm1b0.hm"
echo. >>"hlp\ucm1b0.hm"
echo // Resources (IDR_*) >>"hlp\ucm1b0.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ucm1b0.hm"
echo. >>"hlp\ucm1b0.hm"
echo // Dialogs (IDD_*) >>"hlp\ucm1b0.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ucm1b0.hm"
echo. >>"hlp\ucm1b0.hm"
echo // Frame Controls (IDW_*) >>"hlp\ucm1b0.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ucm1b0.hm"
REM -- Make help for Project UCM1B0


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ucm1b0.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ucm1b0.hlp" goto :Error
if not exist "hlp\ucm1b0.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ucm1b0.hlp" Debug
if exist Debug\nul copy "hlp\ucm1b0.cnt" Debug
if exist Release\nul copy "hlp\ucm1b0.hlp" Release
if exist Release\nul copy "hlp\ucm1b0.cnt" Release
echo.
goto :done

:Error
echo hlp\ucm1b0.hpj(1) : error: Problem encountered creating help file

:done
echo.
