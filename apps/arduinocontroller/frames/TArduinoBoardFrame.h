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
#include "arduino/atArduinoDevice.h"
#include "arduino/atArduinoServer.h"
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
	TTimer *mCheckConnectionTimer;
	TSTDStringLabeledEdit *mSendMSGE;
	TButton *mSendBtn;
	void __fastcall ConnectBtnClick(TObject *Sender);
	void __fastcall mCheckConnectionTimerTimer(TObject *Sender);

	protected:
    	ArduinoServer&					mServer;
        ArduinoDevice&					mArduinoDevice;

        								//The init function will initialize the device
                                        //using parameters from ini file
        virtual void	 				init();

	public:		// User declarations
    						__fastcall  TArduinoBoardFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner);
    	virtual				__fastcall  ~TArduinoBoardFrame();
        IniFileProperties  			    mProperties;
};

extern PACKAGE TArduinoBoardFrame *ArduinoBoardFrame;
#endif
