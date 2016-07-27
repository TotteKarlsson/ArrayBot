#ifndef TPufferArduinoBoardFrameH
#define TPufferArduinoBoardFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "TIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

class TPufferArduinoBoardFrame : public TArduinoBoardFrame
{
__published:
	TIntegerLabeledEdit *mPufferDurationE;
	TIntegerLabeledEdit *mPufferValveSpeedE;
	void __fastcall updateParameter(TObject *Sender, WORD &Key, TShiftState Shift);

	private:

	public:
							__fastcall TPufferArduinoBoardFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall ~TPufferArduinoBoardFrame();

                            void TPufferArduinoBoardFrame::init();
};

extern PACKAGE TPufferArduinoBoardFrame *PufferArduinoBoardFrame;

#endif
