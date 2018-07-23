#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "TMainForm.h"
#include "TRegisterNewRibbonForm.h"
#include "TLoggerForm.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "ArrayCamUtilities.h"
#include "TMoviesFrame.h"
#include "core/ATExceptions.h"
//---------------------------------------------------------------------------
USEFORM("TMainForm.cpp", MainForm);
USEFORM("forms\TRegisterNewRibbonForm.cpp", RegisterNewRibbonForm);
USEFORM("forms\TLoggerForm.cpp", LoggerForm);
//---------------------------------------------------------------------------
ArrayCamUtilities acu;
using namespace at;
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
    	//Setup application mutex, logging etc..
	    acu.init();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		pgDM 	                = new TpgDM(NULL);
        csPGDM                  = new TcsPGDM(NULL);
        PGImagesAndMoviesDM     = new TPGImagesAndMoviesDM(NULL);

		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
    catch (const ATException& ae)
    {
    	MessageDlg(ae.Message().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
    }
	catch (...)
	{
    	MessageDlg("Uncaught exception occured!", mtError, TMsgDlgButtons() << mbOK, 0);
	}
	return 0;
}

