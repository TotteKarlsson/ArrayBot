#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "core/atExceptions.h"
#include "TSplashForm.h"
#include "dslRestartApplicationUtils.h"
#include "UIUtilities.h"
using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Main);
//---------------------------------------------------------------------------
string              gLogFileLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
string              gLogFileName                = "ArrayBot.log";
string 		        gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ArrayBot\\0.5.0";
string 		        gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
HWND                gOtherAppWindow             = NULL;
string              gApplicationStyle           = "Iceberg Classico";
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

			MessageDlg("Arraybot is already running.\nPlease close or kill application before starting new instance.", mtWarning, TMsgDlgButtons() << mbOK, 0);
            return(1); // Exit program
        }

        try
        {
        	gApplicationStyle = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
			TStyleManager::TrySetStyle(gApplicationStyle.c_str());
			TStyleManager::SetStyle(gApplicationStyle.c_str());
        }
        catch(...)
        {
        }

        setupLogging(gLogFileLocation, gLogFileName);

		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        if(!gHideSplash)
        {
            Application->ShowMainForm = false;
	        gSplashForm = new TSplashForm(gLogFileName, Application);
            gSplashForm->Show();
            gSplashForm->Update();
        }

		Application->Title = "ArrayBot - Software for Microtomes";
		Application->CreateForm(__classid(TMain), &Main);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch(const at::ATException& e)
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

