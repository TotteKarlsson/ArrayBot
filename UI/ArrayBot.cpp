#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abExceptions.h"
#include "TSplashForm.h"
#include "mtkRestartApplicationUtils.h"

using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
USEFORM("frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("frames\TTimeDelayFrame.cpp", CombinedMoveFrame); /* TFrame: File Type */
USEFORM("frames\TRibbonLifterFrame.cpp", RibbonLifterFrame); /* TFrame: File Type */
USEFORM("frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("MainForm.cpp", Main);
USEFORM("frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("forms\TShowFileContentForm.cpp", ShowFileContentForm);
USEFORM("forms\abAddLiftForm.cpp", AddLiftSettingForm);
USEFORM("forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("forms\TSplashForm.cpp", SplashForm);
USEFORM("frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
USEFORM("frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2);
USEFORM("frames\TABProcessSequencerFrame.cpp", ABProcessSequencerFrame);
USEFORM("frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
extern string       gLogFileLocation            = "";
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

void setupLogging();

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam);

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

        setupLogging();

		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        gSplashForm = new TSplashForm(Application);
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
		TStyleManager::TrySetStyle("Sapphire Kamri");
		Application->CreateForm(__classid(TMain), &Main);
		Application->CreateForm(__classid(TShowFileContentForm), &ShowFileContentForm);
		Application->CreateForm(__classid(TAddLiftSettingForm), &AddLiftSettingForm);
		Application->CreateForm(__classid(TAddJoyStickSettingForm), &AddJoyStickSettingForm);
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
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "mtkIPC.lib")
#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.lib")
