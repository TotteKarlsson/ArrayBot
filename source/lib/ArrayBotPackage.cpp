#include <System.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
USEFORM("..\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
USEFORM("..\forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("..\forms\TSplashForm.cpp", SplashForm);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------


#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")

//---------------------------------------------------------------------------
#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "atArraybotCore.lib")
#pragma comment(lib, "atVCLCommon.lib")
#pragma comment(lib, "atVCLComponents.bpi")
#pragma comment(lib, "atVCLVisualComponents.bpi")
#pragma comment(lib, "atVCLAPTVisualComponents.bpi")

//---------------------------------------------------------------------------
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")

