#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("P:\libs\atapi\source\vcl\datamodules\TPGDataModule.cpp", pgDM); /* TDataModule: File Type */
USEFORM("P:\libs\atapi\source\vcl\frames\TPGConnectionFrame.cpp", PGConnectionFrame); /* TFrame: File Type */
USEFORM("TMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TpgDM), &pgDM);
		Application->CreateForm(__classid(TPGConnectionFrame), &PGConnectionFrame);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "atDatabase.lib")
