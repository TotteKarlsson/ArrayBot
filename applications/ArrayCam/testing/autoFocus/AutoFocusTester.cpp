//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "ArrayCamUtilities.h"
#include "core/ATExceptions.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("forms\TSettingsForm.cpp", SettingsForm);
USEFORM("forms\TReticlePopupForm.cpp", ReticlePopupForm);
USEFORM("forms\TLoggerForm.cpp", LoggerForm);
//---------------------------------------------------------------------------
ArrayCamUtilities acu;

using namespace at;
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
    	//Setup application mutex, logging etc..
	    acu.init();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch (const ATException& ae)
    {
    	MessageDlg(ae.Message().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
    }
	catch (...)
	{
    	MessageDlg("Uncaught exception occured!", mtError, TMsgDlgButtons() << mbOK, 0);
	}
	return 0;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.lib")
#pragma comment(lib, "dslVCLVisualComponents.bpi")
//
//
#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atVCLAPTVisualComponents.bpi")
#pragma comment(lib, "atVCLNavitar.bpi")
//
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "uc480_B.lib")
#pragma comment(lib, "uc480_tools_B.lib")

////#pragma comment(lib, "ArrayCamPackage.bpi")
//
//
//#pragma comment(lib, "DBXDevartPostgreSQLDriver250.bpi")


