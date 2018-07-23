//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslIniKey.h"
#include "dslRestartApplicationUtils.h"
#include "dslLogger.h"
#include "Core/atDBUtilities.h"
#include "dslException.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "forms/TScanForm.h"
//---------------------------------------------------------------------------
USEFORM("Frames\TRibbonNotesFrame.cpp", RibbonNotesFrame); /* TFrame: File Type */
USEFORM("Frames\TTableFrame.cpp", TableFrame); /* TFrame: File Type */
USEFORM("Forms\TSlicesForm.cpp", SlicesForm);
USEFORM("Forms\TSpecimenForm.cpp", SpecimenForm);
USEFORM("Forms\TTableUpdateForm.cpp", TableUpdateForm);
USEFORM("TMainForm.cpp", MainForm);
USEFORM("P:\libs\atapi\source\vcl\frames\TMoviesFrame.cpp", MoviesFrame); /* TFrame: File Type */
USEFORM("Forms\TAboutATDBForm.cpp", AboutATDBForm);
USEFORM("Forms\TRegisterFreshCSBatchForm.cpp", RegisterFreshCSBatchForm);
USEFORM("Forms\TScanForm.cpp", ScanForm);
USEFORM("Forms\TShowFileContentForm.cpp", ShowFileContentForm);
USEFORM("Forms\TPrintLabelForm.cpp", PrintLabelForm);
USEFORM("Forms\TATDBSplashForm.cpp", SplashForm);
USEFORM("Forms\TBlockForm.cpp", BlockForm);
USEFORM("Forms\TCoverSlipForm.cpp", CoverSlipForm);
USEFORM("P:\libs\atapi\source\vcl\frames\TImagesFrame.cpp", ImagesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
using std::string;
extern HWND         gOtherAppWindow             = NULL;
extern string		gAppName					= "ATDB-PG";
extern string       gApplicationRegistryRoot    = "\\Software\\Smith Lab\\atDBPG\\0.5.0";
extern string       gAppMutexName           	= "ATDBPGAppMutex";
extern bool 		gAppIsStartingUp 			= true;
extern string       gRestartMutexName           = "ATDBPGRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";
extern string       gCommonAppDataLocation      = ""; //Filled out later
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "atDBPG.log";
extern string       gApplicationStyle           = "Iceberg Classico";
extern bool         gIsDevelopmentRelease       = false;
BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam) ;
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        HANDLE appMutex = ::CreateMutexA(NULL, FALSE, gAppMutexName.c_str());
        int err = GetLastError();
        if( ERROR_ALREADY_EXISTS == err)
        {
            ::EnumWindows(FindOtherWindow, NULL);
            if(gOtherAppWindow != NULL)
            {
                MessageDlg("ATDB is already running!", mtWarning, TMsgDlgButtons() << mbOK, 0);
                ::SwitchToThisWindow(gOtherAppWindow, false);
            }
            return(0);
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
        setupLogging();
        Log(lInfo) << "The Logfile was opened..";
        gCommonAppDataLocation = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB-PG");
        if(!folderExists(gCommonAppDataLocation))
        {
            Log(lError) << "The local app data folder("<<gCommonAppDataLocation<<") don't exists! Catastrophe..";
        }
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "atDBpg";

        string iconFile("atDB.ico");
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
        Application->ProcessMessages();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->ShowMainForm = true;
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch(const DSLException &e)
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
//---------------------------------------------------------------------------
