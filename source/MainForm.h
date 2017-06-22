#ifndef MainFormH
#define MainFormH
#include "abApplicationMessages.h"
#include "arraycam/atArrayCamClient.h"
#include "arraybot/atArrayBot.h"
#include "abUIDataStructures.h"
#include "InitArrayBotThread.h"
#include "mtkIniFileProperties.h"
#include "mtkLogFileReader.h"
#include "TRegistryForm.h"
#include "TSTDStringLabeledEdit.h"
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "TAboutArrayBot_2Frame.h"
#include "TFloatLabeledEdit.h"
#include "TIntegerLabeledEdit.h"
#include "TIntLabel.h"
#include "TPropertyCheckBox.h"
#include "TArrayBotBtn.h"
#include "arraybot/apt/atMotorWiggler.h"
#include "cspin.h"
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>
#include "TSoundsFrame.h"
#include "sound/atApplicationSound.h"
#include "TApplicationSoundsFrame.h"

using Poco::Timestamp;
using mtk::IniFileProperties;
class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;
class TNewRibbonForm;

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
	TAction *reInitBotA;
        TAction *ShutDownA;
	TPanel *mRightPanel;
	TFileExit *FileExit1;
	TPanel *TopPanel;
	TPageControl *PageControl1;
	TTabSheet *mFrontPage;
	TGroupBox *JSGB;
	TSpeedButton *mJSSpeedFastBtn;
	TSpeedButton *mJSSpeedMediumBtn;
	TSpeedButton *mJSSpeedSlowBtn;
	TTabSheet *TabSheet1;
	TScrollBox *ScrollBox1;
	TTabSheet *TabSheet2;
	TGroupBox *JoyStickGB2;
	TFloatLabeledEdit *mZJogAccelerationJoystick;
	TFloatLabeledEdit *mXYJogAccelerationJoystick;
	TFloatLabeledEdit *mMaxZJogVelocityJoystick;
	TFloatLabeledEdit *mMaxXYJogVelocityJoystick;
	TComboBox *JoyStickSettingsCB;
	TTabSheet *TabSheet5;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogWindowBtn;
	TButton *AddJsSettingBtn;
	TFloatLabeledEdit *mAngleControlVelE;
	TFloatLabeledEdit *mAngleControllerAccE;
	TTimer *UIUpdateTimer;
	TGroupBox *mRibbonCreationGB;
	TFloatLabeledEdit *mMoveAccelerationE;
	TFloatLabeledEdit *mMoveVelocityVerticalE;
	TPanel *BottomBtnPanel;
	TTimer *mLiftTimer;
	TAction *abortLiftA;
	TAction *liftA;
	TComboBox *mLiftCB;
	TComboBox *LogLevelCB;
	TTabSheet *mMoveSequencesPage;
	TTimer *WaitForDeviceInitTimer;
	TPanel *mSequencesPanel;
	TTabSheet *RibbonLifterTabSheet;
	TPanel *Panel1;
	TBitBtn *mCheckDevicesBtn;
	TBitBtn *ReInitBotBtn;
	TPanel *mMiddlePanel;
	TSpeedButton *mJSCSBtn;
	TRadioGroup *mJoyStickRG;
	TLabel *mJSStatusL;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArrayCamServerPortE;
	TTabSheet *TabSheet3;
	TAboutArrayBotFrame_2 *TAboutArrayBotFrame_21;
	TArrayBotButton *Button5;
	TArrayBotButton *Button7;
	TArrayBotButton *LiftBtn;
	TGroupBox *mLiftGB;
	TGroupBox *GroupBox3;
	TFloatLabeledEdit *mWigglerAmplitudeE;
	TFloatLabeledEdit *mWigglerAccelerationE;
	TArrayBotButton *mWiggleBtn;
	TFloatLabeledEdit *mWigglerVelocityE;
	TCSpinButton *mWiggleSpinButton;
	TGroupBox *GroupBox2;
	TFloatLabeledEdit *mWigglerAmplitudeStepE;
	TArrayBotButton *mPullRibbonBtn;
	TComboBox *mPullCB;
	TLabel *Label1;
	TArrayBotButton *mRelaxBtn;
	TFloatLabeledEdit *mPullRelaxAccE;
	TFloatLabeledEdit *mPullRelaxVelocityE;
	TGroupBox *GroupBox4;
	TGroupBox *ACGB;
	TLabel *mVideoRecordingStatusLbl;
	TImage *mArrayCamStatusLED;
	TLabel *Label2;
	TImage *mArrayCamConnectionStatusLED;
	TButton *mASStartBtn;
	TPageControl *PageControl2;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet6;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TSoundsFrame *TSoundsFrame1;
	TRadioGroup *mUnitControlRG;
	TRadioGroup *mXYCtrlRG;
	TApplicationSoundsFrame *TApplicationSoundsFrame1;
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
    void __fastcall reInitBotAExecute(TObject *Sender);
    void __fastcall ShutDownAExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall JSControlClick(TObject *Sender);
	void __fastcall JSSpeedBtnClick(TObject *Sender);
	void __fastcall AddJsSettingBtnClick(TObject *Sender);
	void __fastcall JoyStickSettingsCBChange(TObject *Sender);
	void __fastcall mXYCtrlRGClick(TObject *Sender);
	void __fastcall mLiftTimerTimer(TObject *Sender);
	void __fastcall abortLiftAExecute(TObject *Sender);
	void __fastcall liftAExecute(TObject *Sender);
	void __fastcall mLiftCBChange(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall WaitForDeviceInitTimerTimer(TObject *Sender);
	void __fastcall mJoyStickRGClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mUnitControlRGClick(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall mRightPanelDblClick(TObject *Sender);
	void __fastcall mWiggleBtnClick(TObject *Sender);
	void __fastcall mWiggleSpinButtonDownClick(TObject *Sender);
	void __fastcall mWiggleSpinButtonUpClick(TObject *Sender);
void __fastcall mASStartBtnClick(TObject *Sender);
	void __fastcall mPullRibbonBtnClick(TObject *Sender);
	void __fastcall mSequencesPanelResize(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

    private:
		enum PageControlTabs 					{pcMain = 0,  pcMoveSequences = 1,
        										pcMotors = 2, pcSettings = 3,
                                                pcLogs = 4, pcAbout = 5};

        void									enableDisableUI(bool enable);
        LogFileReader                           mLogFileReader;
        void __fastcall                         logMsg();

        void __fastcall 						WndProc(TMessage& Message);

		void 						            setupWindowTitle();
        InitBotThread					        mInitBotThread;
        void __fastcall					        onFinishedInitBot();
        void __fastcall					        setupUIFrames();

        IniFile						            mIniFile;
        IniFileProperties  			            mProperties;
		mtk::Property<mtk::LogLevel>            mLogLevel;


                										//Sound properties
		void									setupProperties();
        IniFileProperties  			            mSoundProperties;
        Property<ApplicationSound>				mEnableSlowSpeedSound;
        Property<ApplicationSound>				mEnableMediumSpeedSound;
        Property<ApplicationSound>				mEnableFastSpeedSound;
        Property<ApplicationSound>				mMainPageControlChangeSound;

        vector<TFrame*>					        mFrames;

        										//!The ArrayCam client connects to
                                                //an ArrayCam server. The client processes
                                                //incoming messages over a socket, in
                                                //onArrayCamMessageReceived
		ArrayCamClient				        	mArrayCamClient;

        							            //!Arraybot is allocated on the heap.
                                                //!So that we can catch init exceptions in the
                                                //!constructor of the main form
        ArrayBot					            mAB;

          										//!The Process sequencer allow individual
                                                //!processes to be executed in sequence
  	    ProcessSequencer  						mProcessSequencer;

        										//Callback
		void 									onArrayCamMessageReceived(const string& msg);

      											//Callbacks
        void									onArrayCamClientConnected();
        void									onArrayCamClientDisconnected();
        void									enableDisableArrayCamClientControls(bool enable);



		PairedMove* 				            getCurrentPairedMove();

		TXYZUnitFrame*					        mXYZUnitFrame1;
		TXYZUnitFrame*					        mXYZUnitFrame2;

		TABProcessSequencerFrame*		        mABProcessSequencerFrame;
        TSequencerButtonsFrame*			        mSequencerButtons;
		void __fastcall		                    OnException();

        TRibbonLifterFrame* 			        mRibbonLifterFrame;

        										//!The Motor wiggler wiggles the ribbon
        MotorWiggler							mTheWiggler;


        								        //JS button #5 cycles XY control
        void						            onJSButton5Click();

        								        //JS button #6 cycles joystick speeds
        void						            onJSButton6Click();

        							            //!Button #14 stops everything
        void						            onJSButton14Click();

        void __fastcall 				        FrameClosed(TObject *Sender);


	public:		// User declarations
		__fastcall 					            TMain(TComponent* Owner);
		__fastcall 					            ~TMain();

		void __fastcall                         AppInBox(mlxStructMessage &Msg);
        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)

		TNewRibbonForm* 						mNewRibbonForm;
};

extern PACKAGE TMain *Main;
#endif
