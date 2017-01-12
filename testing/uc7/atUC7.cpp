#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("UI\Forms\TRegisterFreshCSBatchForm.cpp", RegisterFreshCSBatchForm);
USEFORM("UI\Forms\TPrintLabelForm.cpp", PrintLabelForm);
USEFORM("UI\TMainForm.cpp", MainForm);
USEFORM("source\vcl\TImagesDataModule.cpp", imageDM); /* TDataModule: File Type */
USEFORM("source\vcl\TNewBlockForm.cpp", NewBlockForm);
USEFORM("source\vcl\TCoverSlipDataModule.cpp", csDM); /* TDataModule: File Type */
USEFORM("UI\Forms\TAboutATDBForm.cpp", AboutATDBForm);
USEFORM("source\vcl\TNewSpecimenForm.cpp", NewSpecimenForm);
USEFORM("source\vcl\TTableFrame.cpp", TableFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkIniKey.h"
#include "mtkRestartApplicationUtils.h"
#include "mtkLogger.h"
#include "Core/atDBUtilities.h"
#include "mtkMoleculixException.h"
#include "mtkSQLite.h"
#include "datamodules/TATDBDataModule.h"
#pragma package(smart_init)

using namespace mtk;
using std::string;

extern HWND         gOtherAppWindow             = NULL;
extern string       gApplicationRegistryRoot    = "\\Software\\Smith Lab\\uc7";
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

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;

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

		TStyleManager::TrySetStyle(gDefaultAppTheme.c_str());
		Application->Title = "atDB";
        Application->ProcessMessages();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TatdbDM), &atdbDM);
		Application->CreateForm(__classid(TcsDM), &csDM);
		Application->CreateForm(__classid(TimageDM), &imageDM);
		Application->CreateForm(__classid(TPrintLabelForm), &PrintLabelForm);
		Application->CreateForm(__classid(TNewSpecimenForm), &NewSpecimenForm);
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
