#ifndef TMainFormH
#define TMainFormH
#include "abApplicationMessages.h"
#include "arraycam/atArrayCamClient.h"
#include "arraybot/atArrayBot.h"
#include "abUIDataStructures.h"
#include "InitArrayBotThread.h"
#include "dslIniFileProperties.h"
#include "dslLogFileReader.h"
#include "dslTRegistryForm.h"
#include "dslTSTDStringLabeledEdit.h"
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
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "TArrayBotBtn.h"
#include "TAboutArrayBot_2Frame.h"
#include "TMotorPositionFrame.h"
#include "dslLoglevel.h"
#include "uc7/atUC7Component.h"
#include "TUC7StagePositionFrame.h"
#include <Vcl.DBCtrls.hpp>
#include "TApplicationSoundsFrame.h"
#include "TFFMPEGFrame.h"
#include "THDMIStreamerFrame.h"
#include "TPGConnectionFrame.h"
#include "TSoundsFrame.h"
#include "barcodereader/atDS457.h"
#include "dslTFloatLabel.h"
#include "TMoviesFrame.h"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "atVCLUtils.h"
//#include "camera/uc480Class.h"
#include "uc7/atUC7ApplicationMessages.h"
//---------------------------------------------------------------------------

using Poco::Timestamp;
using dsl::IniFileProperties;
class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;
class THandWheelPositionForm;
class TRegisterNewRibbonForm;

//---------------------------------------------------------------------------
class TMainForm : public TRegistryForm
{
	friend TRegisterNewRibbonForm;
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
	TFileExit *FileExit1;
	TPageControl *MainPC;
	TTabSheet *MainTS;
	TTabSheet *MotorsTS;
	TScrollBox *ScrollBox1;
	TTabSheet *LoggingTS;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogWindowBtn;
	TTimer *UIUpdateTimer;

	TComboBox *LogLevelCB;
	TTabSheet *SequencesTS;
	TTimer *WaitForDeviceInitTimer;
	TPanel *Panel1;
	TBitBtn *mCheckDevicesBtn;
	TBitBtn *ReInitBotBtn;
	TPanel *MiddlePanel;
	TTabSheet *AboutTS;
	TAboutArrayBotFrame_2 *TAboutArrayBotFrame_21;
	TArrayBotButton *StopButton;
	TBitBtn *BitBtn1;
	TAction *HomeAllDevicesA;
	TArrayBotButton *DiveButton;
	TArrayBotButton *LiftBtn;
	TArrayBotButton *FillMoreBtn;
	TArrayBotButton *FillLessBtn;
	TPanel *Panel2;
	TMemo *Memo1;
	TPanel *LeftPanel;
	TGroupBox *UC7GB;
	TGroupBox *GroupBox4;
	TIntegerLabeledEdit *mStageMoveDelayE;
	TGroupBox *KnifeGB;
	TUC7StagePositionFrame *ResumeDeltaDistanceFrame;
	TGroupBox *KnifeStageGB;
	TUC7StagePositionFrame *MaxStagePosFrame;
	TArrayBotButton *PopulateMaxNorthPosBtn;
	TUC7StagePositionFrame *CurrentStagePosFrame;
	TTabSheet *UC7Page;
	TPanel *Panel9;
	TGroupBox *CuttingGB;
	TArrayBotButton *mSetZeroCutBtn;
	TIntegerLabeledEdit *mFeedRateE;
	TIntegerLabeledEdit *mZeroCutsE;
	TIntegerLabeledEdit *mPresetFeedRateE;
	TArrayBotButton *SetPresetFeedBtn;
	TGroupBox *UC7OperationGB;
	TGroupBox *GroupBox8;
	TFloatLabeledEdit *PresetReturnSpeedE;
	TFloatLabeledEdit *SlowReturnSpeedE;
	TFloatLabeledEdit *UltraSlowReturnSpeedE;
	TPanel *GroupBox7;
	TRadioGroup *StopOptionsRG;
	TGroupBox *CutterGB;
	TArrayBotButton *StartStopBtn;
	TGroupBox *GroupBox9;
	TTabSheet *SettingsTS;
	TPageControl *MiscPageControl;
	TTabSheet *TabSheet8;
	TSoundsFrame *TSoundsFrame1;
	TApplicationSoundsFrame *TApplicationSoundsFrame1;
	TTabSheet *TabSheet12;
	TPGConnectionFrame *TPGConnectionFrame1;
	TTabSheet *UC7Tab;
	TControlBar *ControlBar1;
	TGroupBox *CounterGB;
	TIntLabel *SectionCounterLabel;
	TIntLabel *RibbonOrderCountLabel;
	TLabel *Label6;
	TIntegerLabeledEdit *mCountToE;
	TArrayBotButton *mResetCounterBtn;
	TArrayBotButton *mResetRibbonOrderBtn;
	TPanel *mTopPanel;
	TComboBox *mUC7ComportCB;
	TButton *mConnectUC7Btn;
	TArrayBotButton *mSynchUIBtn;
	TTimer *mStartupTimer;
	TShape *UC7Shape;
	TLabel *BeforeCuttingLbl;
	TLabel *CuttingLbl;
	TLabel *AfterCuttingLbl;
	TLabel *RetractingLbl;
	TPageControl *PageControl1;
	TTabSheet *About;
	TTabSheet *Help;
	TArrayBotButton *ArrayBotButton1;
	TMotorPositionFrame *MotorPositionFrame1;
	TGroupBox *RibbonRegistrationGB;
	TLabel *BarcodeLbl;
	TLabel *Label7;
	TDBText *DBText1;
	TArrayBotButton *ClearBarcodeBtn;
	TArrayBotButton *RegisterRibbonBtn;
	TArrayBotButton *DecodeSessionBtn;
	TTabSheet *TabSheet1;
	TGroupBox *BarCodeGB;
	TPanel *Panel3;
	TComboBox *mZebraCOMPortCB;
	TButton *mConnectZebraBtn;
	TComboBox *mZebraBaudRateCB;
	TGroupBox *mImagerSettingsGB;
	TRadioGroup *mScannerAimRG;
	TRadioGroup *mScannerEnabledRG;
	TArrayBotButton *BeepBtn;
	TTabSheet *RibbonsTS;
	TGroupBox *GroupBox14;
	TDBGrid *RibbonsGrid;
	TDBNavigator *RibbonsNavigator;
	TPanel *Panel4;
	TDBText *RibbonID;
	TPanel *Panel11;
	TGroupBox *BlockSelectionGB;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label5;
	TDBLookupComboBox *BlockIDCB;
	TDBLookupComboBox *KnifeIDCB;
	TDBLookupComboBox *mUsersCB;
	TGroupBox *GroupBox3;
	TPanel *Panel6;
	TDBGrid *mRibbonNotesGrid;
	TDBNavigator *mRibbonNotesNavigator;
	TPanel *Panel7;
	TDBMemo *mRibbonNoteMemo;
	TDBNavigator *mRibbonNoteNavigator;
	TSpeedButton *PresetReturnSpeedBtn;
	TSpeedButton *SlowReturnSpeedBtn;
	TSpeedButton *UltraSlowReturnSpeedBtn;
	TTabSheet *Miscellaneous;
	TRadioGroup *ThemesRG;
	TGroupBox *GroupBox1;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall checkForDevicesExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall stopAllAExecute(TObject *Sender);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
    void __fastcall reInitBotAExecute(TObject *Sender);
    void __fastcall ShutDownAExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall WaitForDeviceInitTimerTimer(TObject *Sender);
	void __fastcall MainPCChange(TObject *Sender);
	void __fastcall HomeAllDevicesAExecute(TObject *Sender);
	void __fastcall mClearLogWindowBtnClick(TObject *Sender);
	void __fastcall DiveButtonClick(TObject *Sender);
	void __fastcall LiftBtnClick(TObject *Sender);
	void __fastcall JogMotorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall JogMotorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mConnectUC7BtnClick(TObject *Sender);
	void __fastcall mResetCounterBtnClick(TObject *Sender);
	void __fastcall uc7EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CreateUC7Message(TObject *Sender);
	void __fastcall RegisterRibbonBtnClick(TObject *Sender);
	void __fastcall ConnectZebraBtnClick(TObject *Sender);
	void __fastcall DecodeBarcodeClick(TObject *Sender);
	void __fastcall scannerSettingsClick(TObject *Sender);
	void __fastcall mStartupTimerTimer(TObject *Sender);
	void __fastcall CountLabelClick(TObject *Sender);
	void __fastcall ClearBarcodeBtnClick(TObject *Sender);
	void __fastcall mUsersCBCloseUp(TObject *Sender);
	void __fastcall DB_CBCloseUp(TObject *Sender);
	void __fastcall ThemesRGClick(TObject *Sender);

    private:
        void									enableDisableUI(bool enable);
        LogFileReader                           mLogFileReader;
        void __fastcall                         logMsg();

        void __fastcall 						WndProc(TMessage& Message);

		void 						            setupWindowTitle();
        InitBotThread					        mInitBotThread;
        void __fastcall					        onFinishedInitBot();
        void __fastcall					        setupUIFrames();

        IniFile						            mIniFile;
        IniFileProperties  			            mGeneralProperties;
		dsl::Property<dsl::LogLevel>            mLogLevel;

		void									setupProperties();

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
		TXYZUnitFrame*					        mXYZUnitFrame1;

		TABProcessSequencerFrame*		        mABProcessSequencerFrame;
        TSequencerButtonsFrame*			        mSequencerButtons1;
		void __fastcall		                    OnException();
        void									updateDivePosition(double newPos);

        UC7                                     mUC7;
		int										getUC7COMPortNumber();

		bool									handleUC7Message(const UC7Message& msg);
		void __fastcall							onConnectedToUC7();
		void __fastcall							onDisConnectedToUC7();


		void __fastcall							enableDisableUC7UI(bool enableDisable);
		void									onUC7Count();
		void									onUC7CountedTo();
		void __fastcall							AppInBox(ATWindowStructMessage& Msg);


		Property<string>						mLocalDBName;

		Property<int>							mUC7COMPort;
		Property<int>							mCountTo;
		Property<int>							mStopCutterMode;

												//Sound properties
		IniFileProperties						mSoundProperties;
		Property<ApplicationSound>				mBeforeKnifeBackOffSound;
		Property<ApplicationSound>				mKnifeBeforeCuttingSound;
		Property<ApplicationSound>				mKnifeCuttingSound;
		Property<ApplicationSound>				mKnifeAfterCuttingSound;
		Property<ApplicationSound>				mArmRetractingSound;

		Property<int>							mKnifeStageMaxPos;
		Property<int>							mKnifeStageJogStep;
		Property<int>							mKnifeStageResumeDelta;

												//Database stuff
		Property<int>							mDBUserID;
		Property<int>							mBlockID;
		Property<int>							mKnifeID;

		void									populateUsersCB();
		void									populateUsers();
		void	__fastcall						afterDBServerConnect(System::TObject* Sender);
		void	__fastcall						afterDBServerDisconnect(System::TObject* Sender);

        										//!The barcode reader
		DS457									mZebra;

												//INI Parameters...
		Property<int>							mZebraCOMPort;
		Property<int>							mZebraBaudRate;
		int										getZebraCOMPortNumber();
		void __fastcall							onConnectedToZebra();
		void __fastcall							onDisConnectedToZebra();

												//Decoder events
		void __fastcall							onWMDecode(TMessage& Msg);
		void __fastcall							onSSIEvent(TMessage& Msg);
		void __fastcall							onSSIError(TMessage& Msg);
		void __fastcall							onSSITimeout(TMessage& Msg);
		void __fastcall							onSSICapabilities(TMessage& Msg);

		THandWheelPositionForm*					mHandWheelPositionForm;

	public:
		__fastcall 					            TMainForm(TComponent* Owner);
		__fastcall 					            ~TMainForm();

		int										getCurrentUserID();
		int										getCurrentCoverSlipID();
		int										getCurrentBlockID();
		string									getCurrentRibbonID();
		int										getCurrentKnifeID();
		string									getCurrentUserName();

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(UWM_UC7_MESSAGE,		ATWindowStructMessage,			AppInBox);
		MESSAGE_HANDLER(WM_DECODE,				TMessage,						onWMDecode);
		MESSAGE_HANDLER(WM_CAPABILITIES,		TMessage,						onSSICapabilities)
		MESSAGE_HANDLER(WM_ERROR,				TMessage,						onSSIError)
		MESSAGE_HANDLER(WM_TIMEOUT,				TMessage,						onSSITimeout)
		MESSAGE_HANDLER(WM_EVENT,				TMessage,						onSSIEvent)
	END_MESSAGE_MAP(TForm)

};

extern PACKAGE TMainForm *MainForm;
#endif
