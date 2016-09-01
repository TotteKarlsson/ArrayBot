#include <System.hpp>
#pragma hdrstop
USEFORM("frames\TTimeDelayFrame.cpp", TimeDelayFrame); /* TFrame: File Type */
USEFORM("frames\TXYZPositionsFrame.cpp", XYZPositionsFrame); /* TFrame: File Type */
USEFORM("frames\TSequencerButtonsFrame.cpp", SequencerButtonsFrame); /* TFrame: File Type */
USEFORM("frames\TRibbonLifterFrame.cpp", RibbonLifterFrame); /* TFrame: File Type */
USEFORM("frames\TSequenceInfoFrame.cpp", SequenceInfoFrame); /* TFrame: File Type */
USEFORM("frames\TXYZUnitFrame.cpp", XYZUnitFrame); /* TFrame: File Type */
USEFORM("frames\TPositionalTriggerFrame.cpp", PositionalTriggerFrame); /* TFrame: File Type */
USEFORM("forms\TamFileEditor.cpp", amFileEditor);
USEFORM("forms\TShowFileContentForm.cpp", ShowFileContentForm);
USEFORM("frames\TMotorMoveProcessFrame.cpp", MotorMoveProcessFrame); /* TFrame: File Type */
USEFORM("frames\TParallellProcessesFrame.cpp", ParallellProcessesFrame);
USEFORM("frames\TMotorFrame.cpp", MotorFrame); /* TFrame: File Type */
USEFORM("forms\TStringInputDialog.cpp", StringInputDialog);
USEFORM("forms\TTextInputDialog.cpp", TextInputDialog);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}


#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "abResources.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

#pragma comment(lib, "DuneComponents.bpi")



