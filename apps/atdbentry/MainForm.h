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
#include "mtkFloatLabel.h"
#include "TIntLabel.h"
#include "TPropertyCheckBox.h"
#include "TArrayBotBtn.h"
#include <vector>
#include "abATDBServerSession.h"
using Poco::Timestamp;
using mtk::IniFileProperties;
using mtk::IniFile;
using std::vector;
using std::string;

class TABProcessSequencerFrame;
class TRibbonLifterFrame;
class TXYZUnitFrame;
class TSequencerButtonsFrame;

//---------------------------------------------------------------------------
class TMain : public TRegistryForm
{
    __published:	// IDE-managed Components
        TActionList *ActionList1;
        TTimer *ShutDownTimer;
        TApplicationEvents *ApplicationEvents1;
        TAction *ShutDownA;
	TFileExit *FileExit1;
	TPanel *BottomPanel;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogMemoBtn;
	TComboBox *LogLevelCB;
	TSplitter *Splitter1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPanel *TopPanel;
	TArrayBotButton *Button1;
	TArrayBotButton *Button5;
	TPanel *Panel2;
	TPanel *CenterPanel;
	TButton *mCheckForServerDataBtn;
	TTabSheet *TabSheet2;
	TButton *Button3;
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
	void __fastcall mCheckForServerDataBtnClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);

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

        ATDBServerSession					mServerSession;


	public:
		__fastcall 					        TMain(TComponent* Owner);
		__fastcall 					        ~TMain();

		void __fastcall                 	AppInBox(mlxStructMessage &Msg);


        BEGIN_MESSAGE_MAP
            MESSAGE_HANDLER(UWM_MESSAGE,    mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif
