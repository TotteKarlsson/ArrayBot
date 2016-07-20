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
#include "abArrayBot.h"
#include "mtkIniFileProperties.h"
#include <mmsystem.h>
#include <Vcl.StdActns.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Mask.hpp>
#include "mtkLogLevel.h"
#include "abUIDataStructures.h"
#include "abApplicationMessages.h"
#include "InitArrayBotThread.h"
using Poco::Timestamp;
using mtk::IniFileProperties;

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
	TPanel *mButtonPanel;
	TFileExit *FileExit1;
	TPanel *TopPanel;
	TPageControl *PageControl1;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet5;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *BitBtn2;
	TTimer *UIUpdateTimer;
	TSpeedButton *Button5;
	TPanel *BottomBtnPanel;
	TAction *abortLiftA;
	TAction *liftA;
	TComboBox *LogLevelCB;
	TSpeedButton *mAboutBtn;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);

	void __fastcall FormShow(TObject *Sender);

	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mAboutBtnClick(TObject *Sender);


    private:
        LogFileReader                   mLogFileReader;
        void __fastcall                 logMsg();

		void 						    setupWindowTitle();

        void __fastcall					setupUIFrames();

        IniFile						    mIniFile;
        IniFileProperties  			    mProperties;
		mtk::Property<mtk::LogLevel>    mLogLevel;

		void __fastcall		            OnException();

	public:		// User declarations
		__fastcall 					    TMain(TComponent* Owner);
		__fastcall 					    ~TMain();

		void __fastcall                 AppInBox(mlxStructMessage &Msg);
        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif
