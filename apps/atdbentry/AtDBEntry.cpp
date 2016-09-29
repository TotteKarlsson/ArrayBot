#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abExceptions.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("..\..\source\vcl\datamodules\TATDBDataModule.cpp", atDM); /* TDataModule: File Type */
USEFORM("MainForm.cpp", Main);
//---------------------------------------------------------------------------
using namespace mtk;
using namespace std;

extern string		gApplicationName			= "ATDBData Entry";
extern string       gLogFileLocation            = "";
extern string       gLogFileName                = "ATDBDataEntry.log";
extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\ATDBDataEntry\\0.5.0";
extern string 		gAppDataFolder 				= joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot");
static HWND         gOtherAppWindow             = NULL;
extern string       gDefaultAppTheme            = "Iceberg Classico";
extern string       gRestartMutexName           = "ATDBDataEntryRestartMutex";
extern string       gFullDateTimeFormat         = "%Y-%m-%dT%H:%M:%S";
extern string       gDateFormat                 = "%Y-%m-%d";
extern string       gTimeFormat                 = "%H:%M:%S";

extern string       gCommonAppDataLocation      = "";
extern bool         gIsDevelopmentRelease       = false;
extern bool         gAppIsStartingUp            = true;

void setupLogging();
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        setupLogging();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Iceberg Classico");
		Application->CreateForm(__classid(TMain), &Main);
		Application->CreateForm(__classid(TatDM), &atDM);
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
#if defined DSL_STATIC
	#pragma comment(lib, "mtkCommon-static.lib")
	#pragma comment(lib, "mtkMath-static.lib")
	#pragma comment(lib, "mtkIPC-static.lib")
#else
	#pragma comment(lib, "mtkCommon.lib")
	#pragma comment(lib, "mtkMath.lib")
	#pragma comment(lib, "mtkIPC.lib")
#endif

#pragma comment(lib, "abCore.lib")

#pragma comment(lib, "libmysqlB.lib")

#pragma comment(lib, "poco_mysql_connector-static.lib")
#pragma comment(lib, "poco_data-static.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.lib")
