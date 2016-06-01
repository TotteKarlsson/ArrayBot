//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include "mtkStringUtils.h"
#include "mtkFileUtils.h"
#include "mtkLogger.h"

using std::string;
using namespace mtk;

//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Main);
//---------------------------------------------------------------------------
void setupLogging();
extern string  gLogFileName                = "JoyStickt.log";
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		setupLogging();
		Application->CreateForm(__classid(TMain), &Main);
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
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "poco_foundation-static.lib")

void setupLogging()
{
	//Get Application folder

	string fullLogFileName(joinPath(".", gLogFileName));
	clearFile(fullLogFileName);
	gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel 	= true;
	LogOutput::mShowLogTime 	= true;
	LogOutput::mUseLogTabs 		= true;
//	mtk::gLogger.setLogLevel(lInfo);
	mtk::gLogger.setLogLevel(lDebug3);
	Log(lInfo) << "Logger was setup";
}

