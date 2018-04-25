#include <System.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\frames\TStopAndResumeFrame.cpp", StopAndResumeFrame); /* TFrame: File Type */
USEFORM("..\frames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
USEFORM("..\frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("..\frames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
USEFORM("..\frames\TArrayBotRequestFrame.cpp", ArrayBotRequestFrame); /* TFrame: File Type */
USEFORM("..\frames\TArrayCamRequestFrame.cpp", ArrayCamRequestFrame); /* TFrame: File Type */
USEFORM("..\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
USEFORM("..\forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("..\forms\TEditSequenceForm.cpp", EditSequenceForm);
USEFORM("..\forms\TProcessSequenceControlForm.cpp", ProcessSequenceControlForm);
USEFORM("..\forms\TSplashForm.cpp", SplashForm);
USEFORM("..\frames\TParallelProcessesFrame.cpp", ParallelProcessesFrame); /* TFrame: File Type */
USEFORM("..\frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("..\frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("..\frames\TMoveCoverSlipAtAngleProcessFrame.cpp", MoveCoverSlipAtAngleProcessFrame); /* TFrame: File Type */
USEFORM("..\frames\THomeMotorProcessFrame.cpp", HomeMotorProcessFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
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


#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma comment(lib, "atFoundation.lib")
#pragma comment(lib, "atArraybotCore.lib")
#pragma comment(lib, "atVCLCommon.lib")
#pragma comment(lib, "atComponents.bpi")
#pragma comment(lib, "atVisualComponents.bpi")
#pragma comment(lib, "atAPTFrames.bpi")
//---------------------------------------------------------------------------

