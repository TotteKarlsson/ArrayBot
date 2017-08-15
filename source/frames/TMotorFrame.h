#ifndef TMotorFrameH
#define TMotorFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TIntLabel.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "mtkFloatLabel.h"
#include "TPropertyCheckBox.h"
//---------------------------------------------------------------------------

class APTMotor;

class PACKAGE TMotorFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *MotorGB;
        TGroupBox *StatusGB;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Lbl;
        TLabel *Lbl2;
        TLabel *mIsActiveLabel;
        TLabel *mIsForwardingLabel;
        TLabel *mIsHomedLabel;
        TLabel *mIsHomingLabel;
        TLabel *mIsReversingLabel;
        TFloatLabeledEdit *mMotorPositionE;
	TTimer *MotorStatusTimer;
        TButton *Button1;
        TActionList *ActionList1;
        TAction *identify;
        TGroupBox *JoggingGB;
        TButton *mFwdBtn;
        TButton *mRewBtn;
        TFloatLabeledEdit *mJogAcc;
        TFloatLabeledEdit *mJogVelocity;
        TButton *Button4;
        TAction *home;
        TLabel *Label4;
        TLabel *Label5;
        mtkFloatLabel *mJogVelLbl;
        mtkFloatLabel *mJogAccLbl;
        TLabel *Label6;
        TLabel *mIsEnabledLbl;
        TButton *StopBtn;
        TGroupBox *GroupBox1;
        TFloatLabeledEdit *mPositionRangeMaxE;
	TFloatLabeledEdit *mMinPositionLimitE;
	TFloatLabeledEdit *mMaxPositionLimitE;
	TFloatLabeledEdit *mPotentiometerSettingE;
	TButton *EnableDisableBtn;
	TPropertyCheckBox *mEnableDisableLimits;
	TRadioGroup *JogModeRG;
	TFloatLabeledEdit *mJogStepE;
        void __fastcall MotorStatusTimerTimer(TObject *Sender);
        void __fastcall identifyExecute(TObject *Sender);
        void __fastcall homeExecute(TObject *Sender);
        void __fastcall BtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
              int X, int Y);
        void __fastcall BtnUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
              int X, int Y);
        void __fastcall DevEdit(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall mMotorPositionEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall mMotorPositionEKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall EnableDisableBtnClick(TObject *Sender);
        void __fastcall StopBtnClick(TObject *Sender);
	void __fastcall mEnableDisableLimitsClick(TObject *Sender);
	void __fastcall JogModeRGClick(TObject *Sender);

    private:
        APTMotor*				mMotor;
        static int				mFrameNr;

    public:
        			__fastcall	TMotorFrame(const string& name, TComponent* Owner);
        void					assignMotor(APTMotor* m);

};

extern PACKAGE TMotorFrame *MotorFrame;
#endif
