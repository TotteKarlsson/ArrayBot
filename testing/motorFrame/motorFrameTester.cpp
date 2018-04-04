//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;
USEFORM("MainForm.cpp", Main);
USEFORM("..\..\source\frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("P:\libs\dsl\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "MotorTester.log";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
extern string 		gApplicationRegistryRoot  	= "\\Software\\AllenInstitute\\MotorTester\\0.5.0";
void setupLogging();
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        setupLogging();
        Log(lInfo) << "The Logfile was opened..";
		Application->CreateForm(__classid(TMain), &Main);
		Application->CreateForm(__classid(TLogMemoFrame), &LogMemoFrame);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
void setupLogging()
{
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}
	gLogFileLocation = fldr;
	string fullLogFileName(joinPath(gLogFileLocation, gLogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
	dsl::gLogger.setLogLevel(lDebug5);
	Log(lInfo) << "Logger was setup";
}
//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")

#pragma comment(lib, "poco_foundation-static.lib")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLVisualComponents.bpi")


