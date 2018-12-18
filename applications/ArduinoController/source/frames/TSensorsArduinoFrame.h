#ifndef TSensorsArduinoFrameH
#define TSensorsArduinoFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArduinoBoardFrame.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TSensorsArduinoFrame : public TArduinoBoardFrame
{
	__published:	// IDE-managed Components
	void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mSendBtnClick(TObject *Sender);

		private:	// User declarations
		public:		// User declarations

							__fastcall 	TSensorsArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
							__fastcall 	~TSensorsArduinoFrame();

		void 							init();

};

//---------------------------------------------------------------------------
extern PACKAGE TSensorsArduinoFrame *SensorsArduinoFrame;
//---------------------------------------------------------------------------
#endif