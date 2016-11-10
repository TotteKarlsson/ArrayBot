#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "atExceptions.h"
#include "TArduinoControllerSplashForm.h"
#include "mtkRestartApplicationUtils.h"

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
USEFORM("frames\TLightsArduinoFrame.cpp", LightsArduinoFrame); /* TFrame: File Type */
USEFORM("frames\TPufferArduinoBoardFrame.cpp", PufferArduinoBoardFrame); /* TFrame: File Type */
USEFORM("forms\TAboutArduinoControllerForm.cpp", AboutArduinoControllerForm);
USEFORM("forms\TArduinoControllerSplashForm.cpp", ArduinoControllerSplashForm);
USEFORM("frames\TArduinoBoardFrame.cpp", ArduinoBoardFrame); /* TFrame: File Type */
USEFORM("frames\TAboutArduinoServerFrame.cpp", AboutArduinoServerFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
using namespace mtk;
using namespace std;

extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "ArduinoController.log";
extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ArduinoController\\0.5.0";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
static HWND         gOtherAppWindow             = NULL;
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gRestartMutexName           = "arduinoControllerRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";

extern string       gCommonAppDataLocation      = "";
extern bool         gIsDevelopmentRelease       = false;
extern bool         gAppIsStartingUp            = true;
extern bool         gHideSplash                 = true;
extern TArduinoControllerSplashForm* gSplashForm                 = NULL;

void setupLogging();

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    //The app mutex is used to check for already running instances
    HANDLE appMutex;

	try
	{
		// Initialize restart code
		// Check if this instance is restarted and
		// wait while previos instance finish
		if (mtk::checkForCommandLineFlag("--Restart"))
		{
            //TODO: Fix this.. not working properly..
            //            MessageDlg("Wait...", mtWarning, TMsgDlgButtons() << mbOK, 0);
			mtk::WaitForPreviousProcessToFinish(gRestartMutexName);
            Sleep(1000);
		}

        //Look at this later... does not work yet
        const char appMutexName [] = "arduinoControllerAppMutex";
        appMutex = ::CreateMutexA(NULL, FALSE, appMutexName);
        if( ERROR_ALREADY_EXISTS == GetLastError() )
        {
             Log(lInfo) << "ArduinoController is already running!";
            // Program already running somewhere
            ::EnumWindows(FindOtherWindow, NULL);

            if(gOtherAppWindow != NULL)
            {
                //Send a custom message to restore window here..
                Log(lInfo) << "ArduinoController is already running!";
            }

            return(1); // Exit program
        }

        setupLogging();

		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        gSplashForm = new TArduinoControllerSplashForm(Application);
        if(!gHideSplash)
        {
            Application->ShowMainForm = false;
            gSplashForm->Show();
            gSplashForm->Update();
        }
        else
        {
            gSplashForm->Close();
        }

		TStyleManager::TrySetStyle("Iceberg Classico");
		Application->Title = "arduino_controller";
		Application->CreateForm(__classid(TMain), &Main);
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

//---------------------------------------------------------------------------
#if defined DSL_STATIC
	#pragma comment(lib, "mtkCommon-static.lib")
	#pragma comment(lib, "mtkMath-static.lib")
	#pragma comment(lib, "mtkIPC-static.lib")
#else
	#pragma comment(lib, "mtkCommon.lib")
	#pragma comment(lib, "mtkMath.lib")
	#pragma comment(lib, "mtkIPC.lib")
#endif

#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.lib")
