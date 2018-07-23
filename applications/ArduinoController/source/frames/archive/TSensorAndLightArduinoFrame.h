#ifndef TSensorAndLightArduinoFrameH
#define TSensorAndLightArduinoFrameH
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

class PACKAGE TSensorAndLightArduinoFrame : public TArduinoBoardFrame
{
	__published:	// IDE-managed Components
	void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mSendBtnClick(TObject *Sender);

		private:	// User declarations
		public:		// User declarations

							__fastcall 	TSensorAndLightArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TSensorAndLightArduinoFrame();

		void 							init();

};

//---------------------------------------------------------------------------
extern PACKAGE TSensorAndLightArduinoFrame *SensorAndLightArduinoFrame;
//---------------------------------------------------------------------------
#endif
