//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\frames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
USEFORM("..\frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("..\frames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
USEFORM("..\frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("..\forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("..\frames\TArrayCamRequestFrame.cpp", ArrayCamRequestFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("..\forms\TSplashForm.cpp", SplashForm);
USEFORM("..\forms\TProcessSequenceControlForm.cpp", ProcessSequenceControlForm);
USEFORM("..\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
USEFORM("..\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
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
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneComponents.bpi")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")


#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "atArduino.lib")
#pragma comment(lib, "atArrayBotCore.lib")
#pragma comment(lib, "atVCLCore.bpi")


