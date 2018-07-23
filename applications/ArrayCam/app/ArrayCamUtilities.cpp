#pragma hdrstop
#include <Shlobj.h>
#include "ArrayCamUtilities.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atExceptions.h"
#include "dslWin32Utils.h"
#include "dslVCLUtils.h"

using namespace dsl;
using namespace at;
int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam);

extern ArrayCamUtilities acu;

//---------------------------------------------------------------------------
ApplicationUtilities::ApplicationUtilities(const string& appName, const string& regRoot, const string& appVersion)
:
AppMutex(NULL),
AppName(appName),
AppVersion(appVersion),
AppRegistryRoot(joinPath(regRoot, appVersion)),
LogFileName(AppName + ".log"),
AppDataFolder(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
LogFileLocation(AppDataFolder),
RestartMutexName(AppName + "RestartMutex"),
OtherAppWindow(NULL),
AppIsStartingUp(true),
AppIsClosing(false),
Style("Glow")
{
}

ApplicationUtilities::~ApplicationUtilities()
{
    closeLogFile();
}

void ApplicationUtilities::init()
{
    string appMutexName = string(AppName + "Mutex").c_str();
    AppMutex = ::CreateMutexA(NULL, FALSE, appMutexName.c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
    	throw(ATException("Application \"" + AppName + "\" is already running!"));
    }

    setupLogging();

     try
     {
        Style = readStringFromRegistry(AppRegistryRoot, "", "Theme",  Style);
    	TStyleManager::TrySetStyle(Style.c_str());
   	   	TStyleManager::SetStyle(Style.c_str());
     }
     catch(...)
     {
     }

}

bool ApplicationUtilities::setupLogging()
{
	if(!folderExists(LogFileLocation))
	{
		createFolder(LogFileLocation);
	}

	string fullLogFileName(joinPath(LogFileLocation, LogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
    return true;
}

bool ApplicationUtilities::closeLogFile()
{
    dsl::gLogger.closeLogFile();
    return true;
}

///////////////////////////////////////////////////////////////////////////////

ArrayCamUtilities::ArrayCamUtilities()
:
ApplicationUtilities("ArrayCam", "\\Software\\Allen Institute\\ArrayCam", "0.5.0")
{
}

ArrayCamUtilities::~ArrayCamUtilities()
{
    Log(lInfo) << "In Arraycam utilities destructor..";
}

///////////////////////////////////////////////////////////////////////////////
int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	int length = ::GetWindowTextLength(hwnd);
	if(!length)
    {
	    return TRUE;
    }

	vector<TCHAR> buffer(length + 1);
	GetWindowText(hwnd, &buffer[0], length + 1);

    string s(stdstr(buffer));
	if(startsWith(acu.AppName, s))
	{
		// do something with hwnd here
		acu.OtherAppWindow = hwnd;
        SetFocus(hwnd);

        //Stop enumerating..
		return false;
	}

	return true;
}



