#include <System.hpp>
#pragma hdrstop
USEFORM("forms\TSettingsForm.cpp", SettingsForm);
USEFORM("forms\TReticlePopupForm.cpp", ReticlePopupForm);
USEFORM("forms\TActionsForm.cpp", ActionsForm);
USEFORM("forms\TAboutForm.cpp", AboutForm);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atVCLComponents.bpi")
#pragma comment(lib, "atVCLVisualComponents.bpi")

#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")
//
#pragma comment(lib, "uc480_B.lib")
//#pragma comment(lib, "uc480_tools_B.lib")
#pragma comment(lib, "DBXDevartPostgreSQLDriver250.bpi")


