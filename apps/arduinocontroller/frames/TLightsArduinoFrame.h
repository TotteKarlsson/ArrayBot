#ifndef TLightsArduinoFrameH
#define TLightsArduinoFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "TIntegerLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TLightsArduinoFrame : public TArduinoBoardFrame
{
	__published:	// IDE-managed Components
		void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall mSendBtnClick(TObject *Sender);

		private:	// User declarations
		public:		// User declarations

							__fastcall 	TLightsArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TLightsArduinoFrame();

		void 							init();

};

extern PACKAGE TLightsArduinoFrame *LightsArduinoFrame;
#endif
