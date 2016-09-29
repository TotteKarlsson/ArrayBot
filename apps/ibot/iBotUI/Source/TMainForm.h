#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
#include "ibApplicationMessages.h"
#include "ibDataStructures.h"
#include "mtkIniFileC.h"
#include "mtkIniFileProperties.h"
#include "mtkLogFileReader.h"
#include "mtkLogLevel.h"
#include "mtkMessageContainer.h"
#include "mtkProperty.h"
#include "mtkSQLite.h"
#include "TApplicationProperties.h"
#include "TRegistryForm.h"
#include "TRegistryProperties.h"
#include "TSTDStringLabeledEdit.h"
#include <System.Actions.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <Vcl.Bind.Grid.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
#include "TIntegerLabeledEdit.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Navigator.hpp>
#include "TatDM.h"
#include "iBotDataModule.h"
#include "TSlotFrame.h"

using mtk::Property;
using mtk::SQLite;
using mtk::MessageContainer;
using mtk::IniFileProperties;
using mtk::TRegistryProperties;

extern string gApplicationRegistryRoot;

class TMainForm : public TRegistryForm
{
    __published:	// IDE-managed Components
    TStatusBar *SB;
    TPanel *BottomPanel;
        TMemo *infoMemo;
        TActionList *ActionList1;
        TPopupMenu *PopupMenu1;
        TAction *ClearMemoA;
        TMenuItem *ClearMemoA1;
        TTimer *StartupTimer;
    TSplitter *Splitter1;
    TPanel *TopPanel;
    mtkIniFileC *mIniFileC;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Help1;
    TMenuItem *ools1;
    TFileExit *FileExit1;
    TMenuItem *Exit1;
    TMenuItem *ThemesMenu;
    TToolBar *ToolBar2;
    TPanel *Panel4;
    TToolButton *ToolButton4;
    TComboBox *LogLevelCB;
    TMenuItem *AmalyticoHelpDocuments1;
    TAction *OpenAboutFormA;
    TMenuItem *About1;
    TToolButton *ToolButton1;
    TTimer *ShutDownTimer;
	TGroupBox *GroupBox1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TScrollBox *ScrollBox1;
	TDBGrid *DBGrid2;
	TDBNavigator *DBNavigator2;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TDBLookupComboBox *mBlocksCB;
	TGroupBox *GroupBox4;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TGroupBox *GroupBox7;
	TLabel *Label1;
	TGroupBox *Stains;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TComboBox *ComboBox5;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TSlotFrame *SlotFrame1;
	TSlotFrame *SlotFrame2;
	TSlotFrame *SlotFrame3;
	TSlotFrame *SlotFrame4;
	TButton *Button1;
	TAction *NotImplementedYetA;
	TButton *Button2;
	TComboBox *ComboBox1;
	TLabel *Label5;
	TDBGrid *DBGrid3;
	TDBLookupComboBox *mImageStainSessionCB;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ClearMemoAExecute(TObject *Sender);
    void __fastcall StartupTimerTimer(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ThemesMenuClick(TObject *Sender);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LogLevelCBChange(TObject *Sender);
    void __fastcall MainPCChange(TObject *Sender);
	void __fastcall DBLookupComboBox5CloseUp(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall NotImplementedYetAExecute(TObject *Sender);

    private:
        bool                                            gCanClose;
        TApplicationProperties                          mAppProperties;

        TThreadMethod                                   logMsgMethod;
        void __fastcall                                 logMsg();

		LogFileReader                                   mLogFileReader;

		bool                                            mIsStyleMenuPopulated;
		void                                            setupWindowTitle();
		void                                            updateWindowTitle();
		string                                          mTempFileFolder;


														//Threads can drop messages into the
														//Message container. The main thread pops them
														//using the messageProcessor
		MessageContainer                                mMessages;

                                                        //Parameters...
        IniFileProperties	      	                    mGeneralProperties;
        mtk::Property<int>	                            mBottomPanelHeight;
		mtk::Property<int>	                            mMainTabIndex;

		mtk::Property<mtk::LogLevel>	                mLogLevel;
        TRegistryProperties   	  	                    mSplashProperties;
        mtk::Property<bool>                             mShowSplashOnStartup;
        void        __fastcall                          PopulateStyleMenu();

        bool                                            setupAndReadIniParameters();
        void                                            setupIniFile();

        string                                          mDBConnectionName;
        bool                                            ConnectToDataBase(const string& ConnectionName);

		void __fastcall                                 AppInBox(mlxStructMessage &Msg);
        void											clearSlots();
        void											addItemToSlots(const string& id, TObject* o);

    public:
                    __fastcall                          TMainForm(TComponent* Owner);
                    __fastcall                          ~TMainForm();

        BEGIN_MESSAGE_MAP
                  MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif
