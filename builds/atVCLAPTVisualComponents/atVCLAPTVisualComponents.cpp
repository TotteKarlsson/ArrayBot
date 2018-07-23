#include <System.hpp>
#pragma hdrstop
#include "TMotorFrame.h"
#include "TMotorPositionFrame.h"
USEFORM("..\..\source\vcl\aptFrames\TSequenceInfoFrame.cpp", SequenceInfoFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TProcessSequenceControlForm.cpp", ProcessSequenceControlForm);
USEFORM("..\..\source\vcl\aptFrames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TParallelProcessesFrame.cpp", ParallelProcessesFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TStopAndResumeFrame.cpp", StopAndResumeFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TArrayCamRequestFrame.cpp", ArrayCamRequestFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TArrayBotRequestFrame.cpp", ArrayBotRequestFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\THomeMotorProcessFrame.cpp", HomeMotorProcessFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TMoveCoverSlipAtAngleProcessFrame.cpp", MoveCoverSlipAtAngleProcessFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TMotorPositionFrame.cpp", MotorPositionFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\aptFrames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
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

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
//#pragma comment(lib, "atArrayBotCore.lib")
//#pragma comment(lib, "atArduino.lib")
//#pragma comment(lib, "atVCLComponents.lib")
#pragma comment(lib, "poco_foundation")

//#pragma comment(lib, "atVCLCommon.lib")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")

#pragma comment(lib, "atVCLComponents.bpi")
#pragma comment(lib, "atVCLVisualComponents.bpi")

