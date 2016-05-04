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

#include "abDeviceManager.h"
#include "mtkLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "TIntegerLabeledEdit.h"
#include "mtkFloatLabeledEdit.h"
#include <Vcl.AppEvnts.hpp>
#include <mmsystem.h>
#include "Poco/Timestamp.h"
#include "abMotorMessageProcessor.h"
#include "abMotorMessageContainer.h"
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
	TButton *fwdDriveBtn;
	TButton *revDriveBtn;
	TAction *moveForward;
	TAction *moveBackward;
	TAction *stopMotor;
	TButton *Button7;
	TTimer *StatusTimer;
	TApplicationEvents *ApplicationEvents1;
	TLabel *mIsActiveLabel;
	TLabel *mIsHomingLabel;
	TLabel *mIsHomedLabel;
	TPanel *Panel1;
	TToolBar *ToolBar2;
	TBitBtn *BitBtn3;
	TPanel *Panel2;
	mtkFloatLabeledEdit *mMaxVelocity;
	mtkFloatLabeledEdit *mAcceleration;
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
	TButton *DecreaseVelBtn;
	TButton *IncreaseVelBtn;
	TCheckBox *ContinousMoveCB;
	mtkFloatLabeledEdit *mVelDeltaE;
	TButton *switchdirectionBtn;
	TLabel *JoystickZPosition;
	TLabel *JoystickAvgZPos;
	mtkFloatLabeledEdit *mJogVelocity;
	mtkFloatLabeledEdit *mJogAcc;
	TCheckBox *mJogModeCB;
	TGroupBox *JoggingGB;
	TGroupBox *GroupBox4;
	TGroupBox *MovingGB;
	TButton *Button6;
	TButton *Button8;
	TPanel *Panel3;
	TGroupBox *JoyStickGB;
	TGroupBox *GroupBox1;
	TRadioGroup *RadioGroup1;
	mtkFloatLabeledEdit *maxJoyVel;
	TIntegerLabeledEdit *JoySteps;
	TButton *Button5;
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
	void __fastcall moveForwardExecute(TObject *Sender);
	void __fastcall moveBackwardExecute(TObject *Sender);
	void __fastcall stopMotorExecute(TObject *Sender);
	void __fastcall driveBtnUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall mDeviceValueEdit(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall IncreaseVelBtnClick(TObject *Sender);
	void __fastcall DecreaseVelBtnClick(TObject *Sender);
	void __fastcall switchdirectionBtnClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall mJogModeCBClick(TObject *Sender);
	void __fastcall DeviceBtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button5Click(TObject *Sender);

    private:	// User declarations
        DeviceManager		        mDeviceManager;
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();
		APTDevice* 			        getCurrentDevice();
		void __fastcall		        OnException();
		APTMotor*	                getCurrentMotor();
       	Timestamp 			        mLastMotorCommand;
        double						mLastVel;

        MotorMessageProcessor		mMotorMessageProcessor;
        MotorMessageContainer  		mMotorMessageContainer;

        int 						mJoystickID;
        int 						mJoyStickDriverCount;
        bool 						mJoyStickConnected;
	    JOYCAPS 					mJoyCaps;
        double 						mRunningZAverage;
        double 						mValCommand;
        double 						mAlpha;
        void __fastcall 			JMXMove(TMessage &msg);

	public:		// User declarations
		__fastcall 					TMain(TComponent* Owner);

        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MM_JOY1MOVE,TMessage,JMXMove)
        END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
