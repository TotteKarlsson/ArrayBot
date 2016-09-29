#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("TatDM.cpp", atDM); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkIniKey.h"
#include "mtkRestartApplicationUtils.h"
#include "mtkLogger.h"
#include "amlUtilities.h"
//#include "TATDBSplashForm.h"
#include "mtkMoleculixException.h"
#include "mtkSQLite.h"
#pragma package(smart_init)

using namespace mtk;
using std::string;

extern HWND         gOtherAppWindow             = NULL;
extern string       gApplicationRegistryRoot    = "\\Software\\Smith Lab\\atDB\\0.5.0";
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gAppMutexName           	= "ATDBAppMutex";
extern bool 		gAppIsStartingUp 			= true;
extern string       gRestartMutexName           = "ATDBRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";
extern string       gCommonAppDataLocation      = ""; //Filled out later
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "atDB.log";
extern bool         gIsDevelopmentRelease       = false;

extern bool         gHideSplash                 = true;
//extern TSplashForm* gSplashForm                 = NULL;
extern SQLite       gDB                         ;

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;

SQLite       gDB;
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    //The app mutex is used to check for already running instances
    try
    {
		// Initialize restart code
		// Check if this instance is restarted and
		// wait while previos instance finish
		if (mtk::checkForCommandLineFlag("--Restart"))
		{
			mtk::WaitForPreviousProcessToFinish(gRestartMutexName);
		}
        else
        {
            //Look at this later... does not work yet
            HANDLE appMutex = ::CreateMutexA(NULL, FALSE, gAppMutexName.c_str());
            int err = GetLastError();
            if( ERROR_ALREADY_EXISTS == err)
            {
                // Program already running somewhere
                ::EnumWindows(FindOtherWindow, NULL);

                if(gOtherAppWindow != NULL)
                {
                    //Send a custom message to restore window here..
                    ::SwitchToThisWindow(gOtherAppWindow, false);
                }

                return(0); // Exit program
            }
        }

        setupLogging();
        Log(lInfo) << "The Logfile was opened..";

        //Setup globals
        gCommonAppDataLocation = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB");
        if(!folderExists(gCommonAppDataLocation))
        {
            Log(lError) << "The local app data folder("<<gCommonAppDataLocation<<") don't exists! Catastrophe..";
        }

        Application->Initialize();
        Application->MainFormOnTaskBar = true;

        //Load Styles from files
//        loadStyles();
//        setupApplicationTheme();

//        gSplashForm = new TSplashForm(Application);
//        if(!gHideSplash)
//        {
//            Application->ShowMainForm = false;
//            gSplashForm->Show();
//            gSplashForm->Update();
//        }
//        else
//        {
//            gSplashForm->Close();
//        }

        TStyleManager::TrySetStyle("Iceberg Classico");
		TStyleManager::TrySetStyle(gDefaultAppTheme.c_str());
		Application->Title = "atDB";
        Application->ProcessMessages();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TatDM), &atDM);
		Application->Run();

        // Finish restarting process if needed
        DoRestartProcessFinish();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch(const MoleculixException &e)
	{
		throw Exception(e.what());
	}

	catch (...)
	{
		try
		{
			throw Exception("There was something bad happening! We have to close atDB.");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
