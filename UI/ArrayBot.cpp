#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
USEFORM("..\source\VCL\abMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("..\source\VCL\abXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\source\VCL\abEditPositionsForm.cpp", Form2);
//---------------------------------------------------------------------------
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "ArrayBot.log";
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
		Application->CreateForm(__classid(TForm2), &Form2);
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
	Log(lInfo) << "Logger was setup";
}

//---------------------------------------------------------------------------
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "VCLCommon.lib")


