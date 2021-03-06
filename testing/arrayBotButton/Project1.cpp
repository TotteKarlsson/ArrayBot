#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <string>
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslWin32Utils.h"
#include "dslLogger.h"

USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
using std::string;
using namespace dsl;


extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "button.log";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
void setupLogging();

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		setupLogging();
		TStyleManager::TrySetStyle("Iceberg Classico");
		Application->CreateForm(__classid(TForm1), &Form1);
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

void setupLogging()
{
	//Get Application folder
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}

	gLogFileLocation = fldr;

	string fullLogFileName(joinPath(gLogFileLocation, gLogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
}

//---------------------------------------------------------------------------
#if defined DSL_STATIC
	#pragma comment(lib, "dslCommon-static.lib")
	#pragma comment(lib, "dslMath-static.lib")
	#pragma comment(lib, "dslIPC-static.lib")
#else
	#pragma comment(lib, "dslCommon.lib")
	#pragma comment(lib, "dslMath.lib")
	#pragma comment(lib, "dslIPC.lib")
#endif

#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "atResources.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "uc480_B.lib")
#pragma comment(lib, "uc480_tools_B.lib")

#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.bpi")
