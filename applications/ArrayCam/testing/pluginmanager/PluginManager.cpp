#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslWin32Utils.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("P:\libs\dsl\VCL\Frames\dslTPluginInfoFrame.cpp", PluginInfoFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
using namespace dsl;

void setupLogging();
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		setupLogging();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Turquoise Gray");
		Application->CreateForm(__classid(TMainForm), &MainForm);
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

//---------------------------------------------------------------------------
#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "dslPlugins.lib")
#pragma comment(lib, "dslPythonPlugins.lib")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

void setupLogging()
{
	//Get Application folder
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "PluginManager");

	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}

	string fullLogFileName(joinPath(fldr, "Log.txt"));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
	dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= false;
	Log(lInfo) << "Logger was setup";
}

