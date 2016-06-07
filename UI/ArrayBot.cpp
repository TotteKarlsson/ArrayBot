#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abExceptions.h"
using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
USEFORM("..\source\VCL\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("..\source\VCL\abXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\source\VCL\abMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "ArrayBot.log";
extern string 		gApplicationRegistryRoot  = "\\Software\\Dune Scientific\\ArrayBot\\0.5.0";
extern string 		gAppDataFolder = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
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

		TStyleManager::TrySetStyle("Aqua Light Slate");
		Application->CreateForm(__classid(TMain), &Main);
		Application->CreateForm(__classid(TAddJoyStickSettingForm), &AddJoyStickSettingForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch(const ABException& e)
    {
		Application->ShowException(&Exception(e.what()));
    }
	catch (...)
	{
		try
		{
			throw Exception("Unhandled exception");
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
	//Get Application folder
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}

	gLogFileLocation = fldr;

	string fullLogFileName(joinPath(gLogFileLocation, gLogFileName));
	clearFile(fullLogFileName);
	mtk::gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
//	mtk::gLogger.setLogLevel(lInfo);
	mtk::gLogger.setLogLevel(lDebug5);
	Log(lInfo) << "Logger was setup";
}

//---------------------------------------------------------------------------
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.lib")


