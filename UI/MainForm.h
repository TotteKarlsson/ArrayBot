#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
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
#include "mtkFloatLabeledEdit.h"
#include <Vcl.AppEvnts.hpp>
#include "Poco/Timestamp.h"
#include "abJoyStick.h"
#include "abXYZUnit.h"
#include "TSTDStringLabeledEdit.h"
#include "abXYZUnitFrame.h"
using Poco::Timestamp;

class APTMotor;

//---------------------------------------------------------------------------
class TMain : public TForm
{
    __published:	// IDE-managed Components
	TGroupBox *DevicesGB;
        TMemo *infoMemo;
	TListBox *devicesLB;
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TActionList *ActionList1;
        TAction *checkForDevices;
        TBitBtn *BitBtn2;
        TAction *connectAllDevices;
	TTimer *ShutDownTimer;
	TGroupBox *DeviceGB;
	TButton *Button1;
	TAction *identifyCurrent;
	TButton *Button2;
	TAction *homeDevice;
	TAction *jogForward;
	TAction *jogBackwards;
	TButton *Button3;
	TButton *Button4;
	mtkFloatLabeledEdit *motorPositionE;
	TAction *moveForward;
	TAction *moveBackward;
	TAction *stopMotor;
	TButton *Button7;
	TTimer *StatusTimer;
	TApplicationEvents *ApplicationEvents1;
	TLabel *mIsActiveLabel;
	TLabel *mIsHomingLabel;
	TLabel *mIsHomedLabel;
	TPanel *BottomPanel;
	TToolBar *ToolBar2;
	TBitBtn *BitBtn3;
	TPanel *TopPanel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Lbl2;
	TLabel *mVelocityLbl;
	TLabel *Lbl;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *mIsReversingLabel;
	TLabel *mIsForwardingLabel;
	TLabel *Label5;
	mtkFloatLabeledEdit *mJogVelocity;
	mtkFloatLabeledEdit *mJogAcc;
	TCheckBox *mJogModeCB;
	TGroupBox *JoggingGB;
	TGroupBox *GroupBox4;
	TButton *mJogStopBtn;
	TPanel *Panel3;
	TGroupBox *JoyStickGB;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label11;
	TLabel *Label12;
	TSplitter *Splitter1;
	TIntegerLabeledEdit *mNrOfGearsLbl;
	TCheckBox *mJogStopModeCB;
	mtkFloatLabeledEdit *mMaxXYJogVelocityJoystick;
	mtkFloatLabeledEdit *mXYJogAccelerationJoystick;
	mtkFloatLabeledEdit *mMaxZJogVelocityJoystick;
	mtkFloatLabeledEdit *mZJogAccelerationJoystick;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TRadioGroup *jsStateRG;
	TXYZUnitFrame *TXYZUnitFrame1;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall checkForDevicesExecute(TObject *Sender);
        void __fastcall connectAllDevicesExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall devicesLBClick(TObject *Sender);
	void __fastcall identifyCurrentExecute(TObject *Sender);
	void __fastcall homeDeviceExecute(TObject *Sender);
	void __fastcall jogForwardExecute(TObject *Sender);
	void __fastcall jogBackwardsExecute(TObject *Sender);

	void __fastcall stopMotorExecute(TObject *Sender);

	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall mJogModeCBClick(TObject *Sender);
	void __fastcall DeviceBtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

	void __fastcall jsAxisRGClick(TObject *Sender);
	void __fastcall DeviceValueEdit(TObject *Sender, WORD &Key, TShiftState Shift);


    private:	// User declarations
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();

        IniFile						mIniFile;
		JoyStick					mJoyStick;

        XYZUnit						mXYZUnit1;
        XYZUnit						mXYZUnit2;

		void __fastcall		        OnException();
		APTDevice* 					getCurrentDevice();
		APTMotor* 					getCurrentMotor();

        void __fastcall 			JMButtonUpUpdate(TMessage &msg);
        void __fastcall 			JMButtonDownUpdate(TMessage &msg);
        void __fastcall 			JMXYMove(TMessage &msg);
        void __fastcall 			JMZMove(TMessage &msg);
  		void						updateJoyStickAxes();

	public:		// User declarations
		__fastcall 					TMain(TComponent* Owner);
		__fastcall 					~TMain();

        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MM_JOY1MOVE,TMessage,JMXYMove)
          MESSAGE_HANDLER(MM_JOY1ZMOVE,TMessage,JMZMove)
          MESSAGE_HANDLER(MM_JOY1BUTTONDOWN,TMessage,JMButtonDownUpdate)
          MESSAGE_HANDLER(MM_JOY1BUTTONUP,	TMessage,JMButtonUpUpdate)
        END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
