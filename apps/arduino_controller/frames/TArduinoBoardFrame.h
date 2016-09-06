#ifndef TArduinoBoardFrameH
#define TArduinoBoardFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "mtkIniFile.h"
#include "mtkIniFileProperties.h"
#include "abArduinoDevice.h"
#include "mtkIniFileProperties.h"
#include "TSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

using mtk::IniFileProperties;
using mtk::IniFile;

class PACKAGE TArduinoBoardFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mCommPortE;
	TIntegerLabeledEdit *mBaudRateE;
	TButton *mConnectBtn;
	TTimer *Timer1;
	TSTDStringLabeledEdit *mSendMSGE;
	void __fastcall ConnectBtnClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall mSendMSGEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer1Timer(TObject *Sender);

	protected:

        ArduinoDevice&					mArduinoDevice;

        								//The init function will initialize the device
                                        //using parameters from ini file
        virtual void	 				init();

	public:		// User declarations
    						__fastcall  TArduinoBoardFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
    	virtual				__fastcall  ~TArduinoBoardFrame();
        IniFileProperties  			    mProperties;
};

extern PACKAGE TArduinoBoardFrame *ArduinoBoardFrame;
#endif
