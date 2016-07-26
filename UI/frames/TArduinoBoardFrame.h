#ifndef TArduinoBoardFrameH
#define TArduinoBoardFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "mtkSTDStringEdit.h"
#include "TIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "mtkIniFile.h"
#include "mtkIniFileProperties.h"
#include "abArduinoDevice.h"
#include "mtkIniFileProperties.h"
//---------------------------------------------------------------------------

using mtk::IniFileProperties;
using mtk::IniFile;

class TArduinoBoardFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mCommPortE;
	TIntegerLabeledEdit *mBaudRateE;
	TButton *mArduinoBoard1Connect;
	mtkSTDStringEdit *mSendMSGE;
	TButton *Button1;
	TTimer *Timer1;
	void __fastcall mArduinoBoard1ConnectClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer1Timer(TObject *Sender);

	private:

        ArduinoDevice&					mAD;

	public:		// User declarations
    						__fastcall  TArduinoBoardFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
        IniFileProperties  			    mProperties;
};

extern PACKAGE TArduinoBoardFrame *ArduinoBoardFrame;
#endif
