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
#include "abMotorFrame.h"
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
	TBitBtn *InitCloseBtn;
        TActionList *ActionList1;
        TAction *checkForDevices;
        TBitBtn *BitBtn2;
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
	TApplicationEvents *ApplicationEvents1;
	TPanel *BottomPanel;
	TToolBar *ToolBar2;
	TBitBtn *BitBtn3;
	TPanel *TopPanel;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label11;
	TLabel *Label12;
	TSplitter *Splitter1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TXYZUnitFrame *TXYZUnitFrame1;
	TTabSheet *TabSheet4;
	TAction *InitializeUnitsA;
	TAction *ShutDownA;
	TMotorFrame *TMotorFrame1;
	TGroupBox *CoverSlipGB;
	TComboBox *PositionsCB;
	TButton *GotoPosBtn;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	mtkFloatLabeledEdit *mXPosE;
	mtkFloatLabeledEdit *mYPosE;
	mtkFloatLabeledEdit *mZPosE;
	TButton *Button5;
	TSTDStringLabeledEdit *mPositionLabelE;
	TGroupBox *GroupBox3;
	TPanel *Panel2;
	TGroupBox *GroupBox5;
	TGroupBox *GroupBox6;
	mtkFloatLabeledEdit *mVerticalMoveDistanceE;
	mtkFloatLabeledEdit *mMoveAngleE;
	mtkFloatLabeledEdit *mMoveVelHorizE;
	mtkFloatLabeledEdit *mMoveAccelerationE;
	mtkFloatLabeledEdit *mMoveVelocityVerticalE;
	TButton *MoveBtn;
	TComboBox *ComboBox1;
	TButton *Button6;
	mtkFloatLabeledEdit *tkFloatLabeledEdit1;
	mtkFloatLabeledEdit *tkFloatLabeledEdit2;
	mtkFloatLabeledEdit *tkFloatLabeledEdit3;
	TSTDStringLabeledEdit *STDStringLabeledEdit1;
	TButton *Button8;
	TXYZUnitFrame *TXYZUnitFrame2;
	TScrollBox *ScrollBox1;
	TGroupBox *JoyStickGB;
	TIntegerLabeledEdit *mNrOfGearsLbl;
	mtkFloatLabeledEdit *mMaxXYJogVelocityJoystick;
	mtkFloatLabeledEdit *mXYJogAccelerationJoystick;
	mtkFloatLabeledEdit *mMaxZJogVelocityJoystick;
	mtkFloatLabeledEdit *mZJogAccelerationJoystick;
	TRadioGroup *jsStateRG;
	TRadioGroup *JoyControlRG;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall checkForDevicesExecute(TObject *Sender);
        void __fastcall addDevicesToListBoxExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall devicesLBClick(TObject *Sender);
	void __fastcall stopAllAExecute(TObject *Sender);
	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall jsAxisRGClick(TObject *Sender);
	void __fastcall InitializeUnitsAExecute(TObject *Sender);
	void __fastcall ShutDownAExecute(TObject *Sender);
	void __fastcall GotoBtnClick(TObject *Sender);
	void __fastcall PositionsCBChange(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall moveEdit(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MoveBtnClick(TObject *Sender);
	void __fastcall JoyControlRGClick(TObject *Sender);


    private:	// User declarations
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();

        IniFile						mIniFile;
		JoyStick					mJoyStick;
        XYZUnit						mCoverSlip;
        XYZUnit						mWhisker;

		void __fastcall		        OnException();

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
