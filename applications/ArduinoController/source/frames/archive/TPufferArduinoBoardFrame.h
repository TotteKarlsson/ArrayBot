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
#include "arduino/atPufferArduino.h"
//---------------------------------------------------------------------------

class PACKAGE TPufferArduinoBoardFrame : public TArduinoBoardFrame
{
__published:
	TIntegerLabeledEdit *mPufferDurationE;
	void __fastcall updateParameter(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mSendBtnClick(TObject *Sender);




	private:
		PufferArduino&					mPufferArduino;

	public:
							__fastcall 	TPufferArduinoBoardFrame(ArduinoServer& server, PufferArduino& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TPufferArduinoBoardFrame();
    	void 							init();
};

extern PACKAGE TPufferArduinoBoardFrame *PufferArduinoBoardFrame;

#endif
