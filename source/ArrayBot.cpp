#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "core/atExceptions.h"
#include "TSplashForm.h"
#include "mtkRestartApplicationUtils.h"
#include "UIUtilities.h"
using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
//---------------------------------------------------------------------------
string              gLogFileLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
string              gLogFileName                = "ArrayBot.log";
string 		        gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ArrayBot\\0.5.0";
string 		        gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
HWND                gOtherAppWindow             = NULL;
string              gDefaultAppTheme            = "Iceberg Classico";
string              gRestartMutexName           = "arrayBotRestartMutex";
string              gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
string              gDateFormat                 = "%Y-%m-%d";
string              gTimeFormat                 = "%H:%M:%S";
bool                gIsDevelopmentRelease       = false;
bool                gAppIsStartingUp            = true;
bool                gHideSplash                 = false;
TSplashForm*        gSplashForm                 = NULL;

int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam);

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
        const char appMutexName [] = "arrayBotAppMutex";
        appMutex = ::CreateMutexA(NULL, FALSE, appMutexName);
        if( ERROR_ALREADY_EXISTS == GetLastError() )
        {
             Log(lInfo) << "Arraybot is already running!";
            // Program already running somewhere
            ::EnumWindows(FindOtherWindow, NULL);

            if(gOtherAppWindow != NULL)
            {
                //Send a custom message to restore window here..
                Log(lInfo) << "Arraybot is already running!";
            }

            return(1); // Exit program
        }

        setupLogging(gLogFileLocation, gLogFileName);

		Application->Initialize();
		Application->MainFormOnTaskBar = true;


        if(!gHideSplash)
        {
	        gSplashForm = new TSplashForm(gLogFileName, Application);
            Application->ShowMainForm = false;
            gSplashForm->Show();
            gSplashForm->Update();
        }
        else
        {
            gSplashForm = NULL;
        }

		Application->Title = "ArrayBot - Software for Microtomes";
		TStyleManager::TrySetStyle("Amakrits");
		Application->CreateForm(__classid(TMain), &Main);
		Application->ShowMainForm = false;
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

