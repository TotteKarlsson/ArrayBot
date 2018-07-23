@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by UCM0B1.HPJ. >"hlp\ucm0b1.hm"
echo. >>"hlp\ucm0b1.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ucm0b1.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ucm0b1.hm"
echo. >>"hlp\ucm0b1.hm"
echo // Prompts (IDP_*) >>"hlp\ucm0b1.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ucm0b1.hm"
echo. >>"hlp\ucm0b1.hm"
echo // Resources (IDR_*) >>"hlp\ucm0b1.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ucm0b1.hm"
echo. >>"hlp\ucm0b1.hm"
echo // Dialogs (IDD_*) >>"hlp\ucm0b1.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ucm0b1.hm"
echo. >>"hlp\ucm0b1.hm"
echo // Frame Controls (IDW_*) >>"hlp\ucm0b1.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ucm0b1.hm"
REM -- Make help for Project UCM0B1


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ucm0b1.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ucm0b1.hlp" goto :Error
if not exist "hlp\ucm0b1.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ucm0b1.hlp" Debug
if exist Debug\nul copy "hlp\ucm0b1.cnt" Debug
if exist Release\nul copy "hlp\ucm0b1.hlp" Release
if exist Release\nul copy "hlp\ucm0b1.cnt" Release
echo.
goto :done

:Error
echo hlp\ucm0b1.hpj(1) : error: Problem encountered creating help file

:done
echo.
