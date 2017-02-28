#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Frames\TSQLiteDBFrame.cpp", SQLiteDBFrame); /* TFrame: File Type */
USEFORM("TMainForm.cpp", MainForm);
USEFORM("P:\atDB\UI\TatDM.cpp", atDM); /* TDataModule: File Type */
USEFORM("Frames\TSlotFrame.cpp", SlotFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkIniKey.h"
#include "mtkRestartApplicationUtils.h"
#include "mtkLogger.h"
#include "ibUtilities.h"
//#include "TSplashForm.h"
#include "mtkMoleculixException.h"
#include "mtkSQLite.h"
#pragma package(smart_init)

using namespace mtk;
using std::string;

static HWND         gOtherAppWindow             = NULL;
extern string       gApplicationRegistryRoot    = "\\Software\\Dune Scientific\\iBot\\0.6.0";
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gRestartMutexName           = "AmalyticoRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";
extern string       gCommonAppDataLocation      = ""; //Filled out later
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "iBot.log";
extern bool         gIsDevelopmentRelease       = false;
extern bool         gAppIsStartingUp            = true;
extern bool         gHideSplash                 = true;
//extern TSplashForm* gSplashForm                 = NULL;
extern SQLite       gDB                         ;

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;

SQLite       gDB;
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
		}

        //Look at this later... does not work yet
        const char appMutexName [] = "iBotAppMutex";
        appMutex = ::CreateMutexA(NULL, FALSE, appMutexName);
        if( ERROR_ALREADY_EXISTS == GetLastError() )
        {
            // Program already running somewhere
            ::EnumWindows(FindOtherWindow, NULL);

            if(gOtherAppWindow != NULL)
            {
                //Send a custom message to restore window here..
            }

            return(1); // Exit program
        }

        setupLogging();
        Log(lInfo) << "The Logfile was opened..";

        //Setup globals
        gCommonAppDataLocation = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "iBot");
        if(!folderExists(gCommonAppDataLocation))
        {
            Log(lError) << "The local app data folder("<<gCommonAppDataLocation<<") don't exists! Catastrophe..";
        }

        Application->Initialize();
        Application->MainFormOnTaskBar = true;

        //Load Styles from files
        loadStyles();
        setupApplicationTheme();

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

//        TStyleManager::TrySetStyle(gDefaultAppTheme.c_str());
		TStyleManager::TrySetStyle("Amakrits");
		Application->Title = "iBot";
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
			throw Exception("There was something bad happening! We have to close iBot.");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
