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
#include "TFloatLabeledEdit.h"
#include <Vcl.AppEvnts.hpp>

#include "Poco/Timestamp.h"
#include "abJoyStick.h"
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
	TFloatLabeledEdit *motorPositionE;
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
	TPanel *BottomPanel;
	TToolBar *ToolBar2;
	TBitBtn *BitBtn3;
	TPanel *TopPanel;
	TFloatLabeledEdit *mMaxVelocity;
	TFloatLabeledEdit *mAcceleration;
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
	TFloatLabeledEdit *mVelDeltaE;
	TButton *switchdirectionBtn;
	TLabel *JoystickZPosition;
	TFloatLabeledEdit *mJogVelocity;
	TFloatLabeledEdit *mJogAcc;
	TCheckBox *mJogModeCB;
	TGroupBox *JoggingGB;
	TGroupBox *GroupBox4;
	TGroupBox *MovingGB;
	TButton *Button6;
	TButton *mJogStopBtn;
	TPanel *Panel3;
	TGroupBox *JoyStickGB;
	TButton *Button5;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *JoystickXPosition;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *JoystickYPosition;
	TLabel *JoystickButton1;
	TLabel *JoystickButton2;
	TLabel *JoystickButton3;
	TLabel *JoystickButton4;
	TSplitter *Splitter1;
	TRadioGroup *jsStateRG;
	TIntegerLabeledEdit *mNrOfGearsLbl;
	TCheckBox *mJogStopModeCB;
	TRadioGroup *jsAxisRG;
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
	void __fastcall mJogModeCBClick(TObject *Sender);
	void __fastcall DeviceBtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall jsAxisRGClick(TObject *Sender);

    private:	// User declarations
        DeviceManager		        mDeviceManager;
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();
		APTDevice* 			        getCurrentDevice();
		APTMotor*	                getCurrentMotor();

		void __fastcall		        OnException();

       	Timestamp 			        mLastMotorCommand;
        double						mLastVel;

		ArrayBotJoyStick					mJoyStick;
        double 						mValCommand;

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
