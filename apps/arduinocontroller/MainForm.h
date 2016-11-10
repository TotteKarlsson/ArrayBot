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
#include "TRegistryForm.h"
#include "mtkIniFileProperties.h"
#include <mmsystem.h>
#include <Vcl.StdActns.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Mask.hpp>
#include "mtkLogLevel.h"
#include "abUIDataStructures.h"
#include "abApplicationMessages.h"
#include "mtkIniFile.h"
#include "arduino/atArduinoServer.h"
#include "mtkFloatLabel.h"
#include "TIntLabel.h"
#include "TPropertyCheckBox.h"
#include "TArrayBotBtn.h"
#include "arduino/atPufferArduino.h"
#include "arduino/atLightsArduino.h"
#include "arduino/atSensorsArduino.h"
using Poco::Timestamp;
using mtk::IniFileProperties;
using mtk::IniFile;

class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;

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
	TFileExit *FileExit1;
	TTimer *UIUpdateTimer;
	TAction *abortLiftA;
	TAction *liftA;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogMemoBtn;
	TComboBox *LogLevelCB;
	TSplitter *Splitter1;
	TScrollBox *mArduinoSB;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox2;
	TIntLabel *mSectionCountLbl;
	TGroupBox *GroupBox3;
	TIntegerLabeledEdit *mDesiredRibbonLengthE;
	TPropertyCheckBox *mAutoPuffCB;
	TPanel *TopPanel;
	TGroupBox *GroupBox6;
	TArrayBotButton *Button1;
	TArrayBotButton *Button5;
	TArrayBotButton *mPuffNowBtn;
	TArrayBotButton *mEnablePuffBtn;
	TArrayBotButton *mResetCounterBtn;
	TArrayBotButton *mFrontBackLEDBtn;
	TArrayBotButton *mCoaxLightBtn;
	TPropertyCheckBox *mAutoZeroCutCB;
	TGroupBox *GroupBox7;
	TArrayBotButton *mSetZeroCutBtn;
	TArrayBotButton *mSetPresetCutBtn;
	TComboBox *mLeicaCutThicknessLB;
	TLabel *Label1;
	TArrayBotButton *mStartNewRibbonButton;
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArduinoServerPortE;
	TButton *mArduinoServerStartBtn;
	TPanel *Panel2;
	TPanel *CenterPanel;
	TGroupBox *GroupBox4;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mAboutBtnClick(TObject *Sender);
	void __fastcall mClearLogMemoBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mArduinoServerStartBtnClick(TObject *Sender);
	void __fastcall mResetCounterBtnClick(TObject *Sender);
	void __fastcall mPuffRelatedBtnClick(TObject *Sender);
	void __fastcall LigthsBtnsClick(TObject *Sender);
	void __fastcall mAutoPuffCBClick(TObject *Sender);
	void __fastcall mDesiredRibbonLengthEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall mSetZeroCutBtnClick(TObject *Sender);
	void __fastcall mSetPresetCutBtnClick(TObject *Sender);
	void __fastcall mAutoZeroCutCBClick(TObject *Sender);
	void __fastcall mStartNewRibbonButtonClick(TObject *Sender);


    private:
        LogFileReader                       mLogFileReader;
        void __fastcall                     logMsg();

		void 						        setupWindowTitle();
        void __fastcall					    setupUIFrames();

        IniFile						        mIniFile;
        IniFileProperties  			        mProperties;
		mtk::Property<mtk::LogLevel>        mLogLevel;

		void __fastcall		                OnException();

        vector<TFrame*>					    mFrames;
	  	void								onUpdatesFromArduinoServer(const string& msg);

	public:
		__fastcall 					        TMain(TComponent* Owner);
		__fastcall 					        ~TMain();

		void __fastcall                 	AppInBox(mlxStructMessage &Msg);

        ArduinoServer					    mArduinoServer;

           									//References to arduino objects
        PufferArduino&					    mPufferArduino;
        LightsArduino&					    mLightsArduino;
        SensorsArduino&					    mSensorsArduino;

        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,    mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif
