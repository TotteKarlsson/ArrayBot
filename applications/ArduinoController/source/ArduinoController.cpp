#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "Core/atExceptions.h"
#include "TArduinoControllerSplashForm.h"
#include "dslRestartApplicationUtils.h"
#include "TPGDataModule.h"
#include "TSensorsDataModule.h"
//---------------------------------------------------------------------------
USEFORM("frames\TWatchDogServerFrame.cpp", WatchDogServerFrame); /* TFrame: File Type */
USEFORM("P:\libs\atapi\source\vcl\frames\TPGConnectionFrame.cpp", PGConnectionFrame); /* TFrame: File Type */
USEFORM("TMainForm.cpp", MainForm);
USEFORM("forms\TAboutArduinoControllerForm.cpp", AboutArduinoControllerForm);
USEFORM("frames\TAboutArduinoServerFrame.cpp", AboutArduinoServerFrame); /* TFrame: File Type */
USEFORM("frames\TWatchDogSensorFrame.cpp", WatchDogSensorFrame); /* TFrame: File Type */
USEFORM("frames\TArduinoBoardFrame.cpp", ArduinoBoardFrame); /* TFrame: File Type */
USEFORM("frames\TLightsArduinoFrame.cpp", LightsArduinoFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;

extern string       gLogFileLocation            = "";
extern string		gAppExeName					= "ArduinoController";
extern string       gLogFileName                = gAppExeName + ".log";
extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ArduinoController\\0.5.0";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppExeName);
static HWND         gOtherAppWindow             = NULL;
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gRestartMutexName           = gAppExeName + "RestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";
extern string       gCommonAppDataLocation      = "";
extern bool         gIsDevelopmentRelease       = false;
extern bool         gAppIsStartingUp            = true;

void setupLogging();

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    //The app mutex is used to check for already running instances
    HANDLE appMutex;

	try
	{
        pgDM 	                = new TpgDM(NULL);
        sensorsDM 	            = new TSensorsDataModule(NULL);

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
		TStyleManager::TrySetStyle("Amakrits");
		Application->Title = "arduino_controller";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TPGConnectionFrame), &PGConnectionFrame);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch(const ATException& e)
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
#pragma comment(lib, "dslFoundation.lib")

#pragma comment(lib, "atFoundation.lib")

//Third Parties
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

//Packages
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLVisualComponents.bpi")
#pragma comment(lib, "atVisualComponents.bpi")

