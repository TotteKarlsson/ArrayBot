#ifndef MainFormH
#define MainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Buttons.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "mtkLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "TIntegerLabeledEdit.h"
#include "TFloatLabeledEdit.h"
#include <Vcl.AppEvnts.hpp>
#include "Poco/Timestamp.h"

#include "TSTDStringLabeledEdit.h"
#include "abXYZUnitFrame.h"
#include "abMotorFrame.h"
#include "TRegistryForm.h"
#include "abArrayBot.h"
#include "mtkIniFileProperties.h"
#include <mmsystem.h>
#include <Vcl.StdActns.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Grids.hpp>

using Poco::Timestamp;
using mtk::IniFileProperties;

class APTMotor;

//---------------------------------------------------------------------------
class TMain : public TRegistryForm
{
    __published:	// IDE-managed Components
        TActionList *ActionList1;
        TAction *checkForDevices;
        TAction *addDevicesToListBox;
        TTimer *ShutDownTimer;
        TAction *identifyCurrent;
        TAction *homeDevice;
        TAction *jogForward;
        TAction *jogBackwards;
        TAction *moveForward;
        TAction *moveBackward;
        TAction *stopAllA;
        TButton *Button7;
        TTimer *StatusTimer;
	TAction *initBotA;
        TAction *ShutDownA;
	TPanel *Btnpanel;
	TButton *Button5;
	TFileExit *FileExit1;
	TPanel *TopPanel;
	TPageControl *PageControl1;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *BitBtn2;
	TScrollBox *ScrollBox1;
	TScrollBox *ScrollBox2;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall checkForDevicesExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall ShutDownTimerTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall ShutDownAExecute(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);


    private:	// User declarations
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();
        IniFileProperties  			mProperties;

        IniFile						mIniFile;
        ProcessSequencer  			mMoveSequencer;
        XYZUnit						mXYZUnit;

		void __fastcall		        OnException();
		bool 						createMotorFrame(APTMotor* mtr);
		void __fastcall				refreshSequencesCB();


	public:		// User declarations
		__fastcall 					TMain(TComponent* Owner);
		__fastcall 					~TMain();

        BEGIN_MESSAGE_MAP
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif
