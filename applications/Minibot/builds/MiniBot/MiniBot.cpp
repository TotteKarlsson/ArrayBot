#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslRestartApplicationUtils.h"
#include "core/atExceptions.h"
#include "TSplashForm.h"
#include "UIUtilities.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "TMainForm.h"

using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("..\..\source\frames\TABProcessSequencerFrame.cpp", ABProcessSequencerFrame); /* TFrame: File Type */
USEFORM("..\..\source\TMainForm.cpp", Form1);
USEFORM("..\..\source\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
USEFORM("..\..\source\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
USEFORM("..\..\source\forms\TRegisterNewRibbonForm.cpp", RegisterNewRibbonForm);
//---------------------------------------------------------------------------
string 				gAppName					= "MiniBot";
string              gLogFileLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppName);
string              gLogFileName                = "MiniBot.log";
string 		        gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\MiniBot\\0.5.0";
string 		        gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppName);
HWND                gOtherAppWindow             = NULL;
string              gAppMutexName     		    = "MiniBotMutex";
string              gApplicationStyle           = "Iceberg Classico";
string              gRestartMutexName           = "MiniBotRestartMutex";
string              gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
string              gDateFormat                 = "%Y-%m-%d";
string              gTimeFormat                 = "%H:%M:%S";
bool                gIsDevelopmentRelease       = false;
bool                gAppIsStartingUp            = true;
bool                gHideSplash                 = true;
TSplashForm*        gSplashForm                 = NULL;

int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam);

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    //The app mutex is used to check for already running instances
    HANDLE appMutex;

	try
	{
        //Look at this later... does not work yet
        const char* appMutexName  = gAppMutexName.c_str();
        appMutex = ::CreateMutexA(NULL, FALSE, appMutexName);
        if( ERROR_ALREADY_EXISTS == GetLastError() )
        {
             Log(lInfo) << gAppName << " is already running!";
            // Program already running somewhere
            ::EnumWindows(FindOtherWindow, NULL);

            if(gOtherAppWindow != NULL)
            {
                //Send a custom message to restore window here..
                Log(lInfo) << gAppName << " is already running!";
            }

            return(1); // Exit program
        }

        setupLogging(gLogFileLocation, gLogFileName);

        try
        {
        	gApplicationStyle = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
			TStyleManager::TrySetStyle(gApplicationStyle.c_str());
			TStyleManager::SetStyle(gApplicationStyle.c_str());
        }
        catch(...)
        {
        }

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        string iconFile("MiniBot_Icon.ico");
        if(fileExists(iconFile))
        {
			Application->Icon->LoadFromFile(iconFile.c_str());
        }
        else
        {
            Log(lWarning) << "Application icon ("<<iconFile<<")  was not found";
        }

		pgDM 	                = new TpgDM(NULL);
        csPGDM                  = new TcsPGDM(NULL);
        PGImagesAndMoviesDM     = new TPGImagesAndMoviesDM(NULL);

        if(!gHideSplash)
        {
	        gSplashForm = new TSplashForm(gLogFileName, Application);
            Application->ShowMainForm = false;
            gSplashForm->TAboutArrayBotFrame1->AppNameLabel->Caption = vclstr(gAppName);
            gSplashForm->Show();
            gSplashForm->Update();
        }
        else
        {
            gSplashForm = NULL;
        }

		Application->Title = "MiniBot - Software for Microtomes";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->ShowMainForm = false;
		Application->Run();
        delete gSplashForm;
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

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "dslMath.lib")
#pragma comment(lib, "dslIPC.lib")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atBarcodereader.lib")
#pragma comment(lib, "atArrayBotCore.lib")

#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "atVCLCommon.lib")

#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "atVCLVisualComponents.bpi")
#pragma comment(lib, "atVCLAPTVisualComponents.bpi")
