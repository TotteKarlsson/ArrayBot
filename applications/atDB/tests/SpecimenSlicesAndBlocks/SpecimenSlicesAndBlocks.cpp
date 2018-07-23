//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("P:\libs\atapi\source\vcl\datamodules\TATDBDataModule.cpp", atdbDM); /* TDataModule: File Type */
USEFORM("..\..\source\Forms\TSlicesForm.cpp", SlicesForm);
USEFORM("..\..\source\Forms\TSpecimenForm.cpp", SpecimenForm);
USEFORM("..\..\source\Forms\TBlockForm.cpp", BlockForm);
//---------------------------------------------------------------------------
extern bool gAppIsStartingUp = true;

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Amethyst Kamri");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TatdbDM), &atdbDM);
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