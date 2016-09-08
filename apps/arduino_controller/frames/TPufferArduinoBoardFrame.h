#ifndef TPufferArduinoBoardFrameH
#define TPufferArduinoBoardFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "TIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
#include "abPufferArduino.h"
//---------------------------------------------------------------------------

class PACKAGE TPufferArduinoBoardFrame : public TArduinoBoardFrame
{
__published:
	TIntegerLabeledEdit *mPufferDurationE;
	TIntegerLabeledEdit *mPufferValveSpeedE;
	void __fastcall updateParameter(TObject *Sender, WORD &Key, TShiftState Shift);

	private:

	public:
							__fastcall 	TPufferArduinoBoardFrame(PufferArduino& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TPufferArduinoBoardFrame();
    	void 							init();
};

extern PACKAGE TPufferArduinoBoardFrame *PufferArduinoBoardFrame;

#endif
