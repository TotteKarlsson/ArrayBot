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
#include "amlApplicationMessages.h"
#include "amlDataStructures.h"
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
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Vcl.Mask.hpp>
#include "TatDM.h"
#include "pBarcode1D.hpp"
#include "pUPC.hpp"
#include "pUPCA.hpp"
#include "pCode39.hpp"
#include "pDBBarcode1D.hpp"

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
    TAction *OpenAboutFormA;
    TMenuItem *About1;
    TToolButton *ToolButton1;
    TTimer *ShutDownTimer;
	TPageControl *PageControl1;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox2;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TBarcode1D_Code39 *Barcode1D_Code391;
	TDBBarcode1D *DBBarcode1D1;
	TImage *mBarCodeImage;
	TActionList *ActionList2;
	TDBGrid *DBGrid1;
	TTabSheet *TabSheet1;
	TDBNavigator *mRibbonsNavigator;
	TGroupBox *GroupBox6;
	TButton *PrintBarCodeBtn;
	TDBText *DBText2;
	TBindSourceDB *BindSourceDB2;
	TDBGrid *DBGrid2;
	TTabSheet *TabSheet3;
	TDBGrid *DBGrid3;
	TDBNavigator *DBNavigator1;
	TDBNavigator *DBNavigator2;
	TPanel *Panel1;
	TPanel *Panel2;
	TDBGrid *DBGrid4;
	TPanel *Panel3;
	TDBNavigator *mBlocksNavigator;
	TButton *mNewBlockBtn;
	TComboBox *ComboBox1;
	TSQLQuery *mUsersQ;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);

    void __fastcall ClearMemoAExecute(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ThemesMenuClick(TObject *Sender);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mUsersCBClick(TObject *Sender);
	void __fastcall mUsersNavigatorClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall mUsersNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button);
	void __fastcall mUserNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mInsertNewNoteBtnClick(TObject *Sender);
	void __fastcall mDeleteNoteBtnClick(TObject *Sender);
	void __fastcall mBlocksNavigatorClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall RibbonsNavigatorClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall mBlocksNavigatorBeforeAction(TObject *Sender, TNavigateBtn Button);
	void __fastcall PrintBarCodeClick(TObject *Sender);
	void __fastcall RegisterNewBlock(TObject *Sender);

	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox1Enter(TObject *Sender);


    private:	// User declarations
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

    public:		// User declarations
                    __fastcall                          TMainForm(TComponent* Owner);
                    __fastcall                          ~TMainForm();

        BEGIN_MESSAGE_MAP
                  MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
