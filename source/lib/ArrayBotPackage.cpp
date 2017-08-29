#include <System.hpp>
#pragma hdrstop
//USEFORM("..\frames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
//USEFORM("..\frames\TArrayCamRequestFrame.cpp", ArrayCamRequestFrame); /* TFrame: File Type */
//USEFORM("..\frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
//USEFORM("..\frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
//USEFORM("..\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
//USEFORM("..\forms\TProcessSequenceControlForm.cpp", ProcessSequenceControlForm);
//USEFORM("..\forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
//USEFORM("..\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
//USEFORM("..\forms\TSplashForm.cpp", SplashForm);
//USEFORM("..\frames\TStopAndResumeFrame.cpp", StopAndResumeFrame); /* TFrame: File Type */
//USEFORM("..\frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
//USEFORM("..\frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
//USEFORM("..\frames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
//USEFORM("..\frames\TMoveCoverSlipAtAngleProcessFrame.cpp", MoveCoverSlipAtAngleProcessFrame); /* TFrame: File Type */
////USEFORM("..\frames\TMotorPositionFrame.cpp", MotorPositionFrame); /* TFrame: File Type */
//USEFORM("..\frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
//USEFORM("..\frames\TParallelProcessesFrame.cpp", ParallelProcessesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "TMotorFrame.h"
#include "TMotorPositionFrame.h"
//---------------------------------------------------------------------------
USEFORM("..\frames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\frames\TArrayCamRequestFrame.cpp", ArrayCamRequestFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("..\frames\TAboutArrayBot_2Frame.cpp", AboutArrayBotFrame_2); /* TFrame: File Type */
USEFORM("..\forms\TProcessSequenceControlForm.cpp", ProcessSequenceControlForm);
USEFORM("..\forms\abAddJoyStickSettingForm.cpp", AddJoyStickSettingForm);
USEFORM("..\frames\TAboutArrayBotFrame.cpp", AboutArrayBotFrame); /* TFrame: File Type */
USEFORM("..\forms\TSplashForm.cpp", SplashForm);
USEFORM("..\frames\TStopAndResumeFrame.cpp", StopAndResumeFrame); /* TFrame: File Type */
USEFORM("..\frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("..\frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("..\frames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
USEFORM("..\frames\TMoveCoverSlipAtAngleProcessFrame.cpp", MoveCoverSlipAtAngleProcessFrame); /* TFrame: File Type */
USEFORM("..\frames\TMotorPositionFrame.cpp", MotorPositionFrame); /* TFrame: File Type */
USEFORM("..\frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("..\frames\TParallelProcessesFrame.cpp", ParallelProcessesFrame); /* TFrame: File Type */
USEFORM("..\forms\TEditSequenceForm.cpp", EditSequenceForm);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------


static inline void ValidCtrCheck(TMotorFrame *)
{
  new TMotorFrame("", NULL);
}

namespace Tmotorframe
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TMotorFrame)};
        RegisterComponents("AIComponents", classes, 0);
    }
}

static inline void ValidCtrCheck(TMotorPositionFrame *)
{
  new TMotorPositionFrame(NULL, NULL);
}

namespace Tmotorpositionframe
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TMotorPositionFrame)};
        RegisterComponents("AIComponents", classes, 0);
    }
}

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

//---------------------------------------------------------------------------
#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "atArduino.lib")
#pragma comment(lib, "atArrayBotCore.lib")
#pragma comment(lib, "atVCLCore.bpi")
//---------------------------------------------------------------------------

