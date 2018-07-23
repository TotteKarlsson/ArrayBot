#ifndef TMainFormH
#define TMainFormH
#include <Data.Bind.Components.hpp>
#include <Data.Bind.EngExt.hpp>
#include <System.Actions.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
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
#include "abApplicationMessages.h"
#include "abUIDataStructures.h"
#include "arduino/atArduinoServer.h"
#include "arduino/atLightsArduino.h"
#include "core/WatchDogServer.h"
#include "dslIniFile.h"
#include "dslIniFileProperties.h"
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include "dslTFloatLabel.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "dslTRegistryForm.h"
#include "dslTSTDStringLabeledEdit.h"
#include "Poco/Timestamp.h"
#include "TArrayBotBtn.h"
#include "TPGConnectionFrame.h"
#include "TWatchDogServerFrame.h"
using Poco::Timestamp;
using dsl::IniFileProperties;
using dsl::IniFile;
using dsl::Property;

class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;

//---------------------------------------------------------------------------
class TMainForm : public TRegistryForm
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
	TPanel *TopPanel;
	TArrayBotButton *Button1;
	TArrayBotButton *Button5;
	TArrayBotButton *LEDBtn;
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArduinoServerPortE;
	TButton *mArduinoServerStartBtn;
	TPanel *Panel2;
	TGroupBox *GroupBox4;
	TToolBar *ToolBar2;
	TBitBtn *mHideBottomPanelBtn;
	TPanel *Panel1;
	TButton *mShowBottomPanelBtn;
	TTabSheet *TabSheet3;
	TIntLabel *NrOfServerClients;
	TLabel *Label1;
	TArrayBotButton *RequestInfoBtn;
	TIntegerLabeledEdit *LEDDriveE;
	TTrackBar *DriveTB;
	TBindingsList *BindingsList1;
	TPGConnectionFrame *TPGConnectionFrame1;
	TButton *Button2;
	TTimer *GetEnvironmentNumbersTimer;
	TWatchDogServerFrame *TWatchDogServerFrame1;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mAboutBtnClick(TObject *Sender);
	void __fastcall MiscBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mArduinoServerStartBtnClick(TObject *Sender);
	void __fastcall LigthsBtnsClick(TObject *Sender);
	void __fastcall mShowBottomPanelBtnClick(TObject *Sender);
	void __fastcall DriveTBChange(TObject *Sender);
	void __fastcall LEDDriveEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
        LogFileReader                       mLogFileReader;
        void __fastcall                     logMsg();

        IniFile						        mIniFile;
        IniFileProperties  			        mProperties;
		Property<dsl::LogLevel>        		mLogLevel;
		Property<int>        				mBottomPanelHeight;
		Property<bool>        				mBottomPanelVisible;

		void 						        setupWindowTitle();
        void __fastcall					    setupUIFrames();

		void __fastcall		                OnException();

        vector<TFrame*>					    mFrames;
	  	void								onUpdatesFromArduinoServer(const string& msg);
		void __fastcall						afterDBServerConnect(System::TObject* Sender);
		void __fastcall						afterDBServerDisconnect(System::TObject* Sender);

        WatchDogServer						mWatchDogServer;

	public:
		__fastcall 					        TMainForm(TComponent* Owner);
		__fastcall 					        ~TMainForm();

		void __fastcall                 	AppInBox(mlxStructMessage &Msg);
        ArduinoServer					    mArduinoServer;

           									//References to arduino objects
        LightsArduino&					    mLightsArduino;

        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,    mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif
