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

using Poco::Timestamp;
using mtk::IniFileProperties;

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
        TApplicationEvents *ApplicationEvents1;
	TAction *initBotA;
        TAction *ShutDownA;
	TPanel *Btnpanel;
	TFileExit *FileExit1;
	TPanel *TopPanel;
	TPageControl *PageControl1;
	TTabSheet *TabSheet4;
	TGroupBox *AnglesGB;
	TFloatLabeledEdit *mCSAngleE;
	TGroupBox *JSGB;
	TSpeedButton *mJSSpeedFastBtn;
	TSpeedButton *mJSSpeedMediumBtn;
	TSpeedButton *mJSSpeedSlowBtn;
	TTabSheet *TabSheet1;
	TScrollBox *ScrollBox1;
	TXYZUnitFrame *TXYZUnitFrame1;
	TXYZUnitFrame *TXYZUnitFrame2;
	TMotorFrame *TMotorFrame1;
	TTabSheet *TabSheet2;
	TGroupBox *JoyStickGB2;
	TFloatLabeledEdit *mZJogAccelerationJoystick;
	TFloatLabeledEdit *mXYJogAccelerationJoystick;
	TFloatLabeledEdit *mMaxZJogVelocityJoystick;
	TFloatLabeledEdit *mMaxXYJogVelocityJoystick;
	TComboBox *JoyStickSettingsCB;
	TButton *Button2;
	TButton *Button3;
	TBitBtn *BitBtn1;
	TBitBtn *InitCloseBtn;
	TTabSheet *TabSheet5;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *BitBtn2;
	TButton *AddJsSettingBtn;
	TFloatLabeledEdit *mCameraAngleEdit;
	TMotorFrame *TMotorFrame2;
	TFloatLabeledEdit *mAngleControlVelE;
	TFloatLabeledEdit *mAngleControllerAccE;
	TButton *Button1;
	TTimer *UIUpdateTimer;
	TRadioGroup *mXYCtrlRG;
	TGroupBox *LiftGB;
	TFloatLabeledEdit *mMoveAccelerationE;
	TFloatLabeledEdit *mMoveVelocityVerticalE;
	TFloatLabeledEdit *mVerticalMoveDistanceE;
	TSpeedButton *mJSCSBtn;
	TSpeedButton *Button7;
	TSpeedButton *Button5;
	TPanel *BottomBtnPanel;
	TTimer *mLiftTimer;
	TAction *abortLiftA;
	TAction *liftA;
	TSpeedButton *LiftBtn;
	TComboBox *mLiftCB;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall checkForDevicesExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall stopAllAExecute(TObject *Sender);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
    void __fastcall BitBtn3Click(TObject *Sender);
    void __fastcall JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall initBotAExecute(TObject *Sender);
    void __fastcall ShutDownAExecute(TObject *Sender);
    void __fastcall moveEdit(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall Button3Click(TObject *Sender);
	void __fastcall stowBtnClick(TObject *Sender);
	void __fastcall mCSAngleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall JSControlClick(TObject *Sender);
	void __fastcall JSSpeedBtnClick(TObject *Sender);
	void __fastcall AddJsSettingBtnClick(TObject *Sender);
	void __fastcall JoyStickSettingsCBChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mXYCtrlRGClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall mLiftTimerTimer(TObject *Sender);
	void __fastcall abortLiftAExecute(TObject *Sender);
	void __fastcall liftAExecute(TObject *Sender);
	void __fastcall mLiftCBChange(TObject *Sender);

    private:
        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();
        IniFileProperties  			mProperties;

        IniFile						mIniFile;
        							//!Arraybot is allocated on the stack.
                                    //!So that we can cat ch exceptions in the
                                    //!constructor
        ArrayBot*					mAB;
		PairedMove* 				getCurrentPairedMove();


		void __fastcall		        OnException();
        void						onJSButton5Click();
        void						onJSButton6Click();

        							//!Button 14 initiate/cancel a lift operation
        void						onJSButton14Click();

	public:		// User declarations
		__fastcall 					TMain(TComponent* Owner);
		__fastcall 					~TMain();

        BEGIN_MESSAGE_MAP
//          MESSAGE_HANDLER(MM_JOY1MOVE, TMessage, JMXYMove)
//          MESSAGE_HANDLER(MM_JOY1ZMOVE, TMessage, JMZMove)
//          MESSAGE_HANDLER(MM_JOY1BUTTONDOWN,TMessage,JMButtonDownUpdate)
//          MESSAGE_HANDLER(MM_JOY1BUTTONUP,	TMessage,JMButtonUpUpdate)
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif
