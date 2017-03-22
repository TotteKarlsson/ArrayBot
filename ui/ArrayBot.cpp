#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "atExceptions.h"
#include "TSplashForm.h"
#include "mtkRestartApplicationUtils.h"
#include "UIUtilities.h"
using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
//---------------------------------------------------------------------------
extern string       gLogFileLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
extern string       gLogFileName                = "ArrayBot.log";
extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ArrayBot\\0.5.0";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
static HWND         gOtherAppWindow             = NULL;
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gRestartMutexName           = "arrayBotRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";
extern string       gCommonAppDataLocation      = ""; //Filled out later
extern bool         gIsDevelopmentRelease       = false;
extern bool         gAppIsStartingUp            = true;
extern bool         gHideSplash                 = false;
extern TSplashForm* gSplashForm                 = NULL;
//extern SQLite       gDB                         ;

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

        gSplashForm = new TSplashForm(gLogFileName, Application);
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

		Application->Title = "ArrayBot - Software for Robots";
		TStyleManager::TrySetStyle("Obsidian");
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

