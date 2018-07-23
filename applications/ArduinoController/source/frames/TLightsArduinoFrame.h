#ifndef TLightsArduinoFrameH
#define TLightsArduinoFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

class PACKAGE TLightsArduinoFrame : public TArduinoBoardFrame
{
	__published:	// IDE-managed Components
		void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall mSendBtnClick(TObject *Sender);

		private:

		public:

							__fastcall 	TLightsArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TLightsArduinoFrame();

		void 							init();

};

extern PACKAGE TLightsArduinoFrame *LightsArduinoFrame;
#endif
