#ifndef TMainFormH
#define TMainFormH
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <System.Actions.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <Vcl.Bind.Grid.hpp>
#include <Vcl.Bind.Navigator.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
//#include <Vcl.DBLookup.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "atBarCodeBuilder.h"
#include "Core/atDBApplicationMessages.h"
#include "Core/atDBDataStructures.h"
#include "core/atVideoCompressorThread.h"
#include "forms/dslTRegistryForm.h"
#include "dslTIniFileC.h"
#include "dslIniFileProperties.h"
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include "dslMessageContainer.h"
#include "dslProperty.h"
#include "dslApplicationProperties.h"
#include "TArrayBotBtn.h"
#include "dslTFloatLabeledEdit.h"
#include "TImagesFrame.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "TMoviesFrame.h"
#include "TPGConnectionFrame.h"
#include "dslRegistryProperties.h"
#include "dslTSTDStringEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include "TTableFrame.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

using dsl::Property;
using dsl::MessageContainer;
using dsl::IniFileProperties;
using dsl::TRegistryProperties;
using dsl::ApplicationProperties;
using dsl::shared_ptr;
using std::list;
using std::vector;
using dsl::StringList;
class TFFMPEGOutputFrame;
class TMovieItemFrame;

extern string gApplicationRegistryRoot;

class TMainForm : public TRegistryForm
{
    __published:	// IDE-managed Components
    TStatusBar *SB;
        TActionList *ActionList1;
	TPopupMenu *LogMemoPopup;
        TAction *ClearMemoA;
        TMenuItem *ClearMemoA1;
    TPanel *TopPanel;
    TIniFileC *mIniFileC;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Help1;
    TFileExit *FileExit1;
    TMenuItem *Exit1;
    TAction *OpenAboutFormA;
    TMenuItem *About1;
    TTimer *ShutDownTimer;
	TPageControl *PageControl1;
	TTabSheet *TabSheet5;
	TPanel *MenuPanel;
	TTabSheet *TabSheet6;
	TTableFrame *TTableFrame1;
	TTabSheet *RibbonsTS;
	TGroupBox *GroupBox2;
	TDBGrid *mRibbonsGrid;
	TDBNavigator *RibbonsNavigator;
	TGroupBox *GroupBox1;
	TDBGrid *mRibbonNotesGrid;
	TDBMemo *mRibbonNoteMemo;
	TDBNavigator *RibbonNoteNavigator;
	TDBNavigator *RibbonNotesNavigator;
	TTabSheet *TabSheet4;
	TPageControl *PageControl2;
	TTabSheet *TabSheet8;
	TDBGrid *SlicesGrid;
	TDBNavigator *SlicesNavigator;
	TGroupBox *GroupBox4;
	TListBox *mTablesLB;
	TDBGrid *mUsersDBGrid;
	TDBNavigator *UsersNavigator;
	TTabSheet *TabSheet3;
	TPanel *BottomPanel;
	TPanel *Panel1;
	TMemo *infoMemo;
	TToolBar *ToolBar1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton1;
	TComboBox *LogLevelCB;
	TPopupMenu *SpecimenPopup;
	TMenuItem *openDocument;
	TDBText *RibbonIDLbl;
	TTabSheet *TabSheet9;
	TDBGrid *CoverSlipsGrid;
	TDBNavigator *CSNavigator;
	TPanel *Panel7;
	TPanel *Panel8;
	TGroupBox *GroupBox8;
	TPanel *Panel9;
	TTabSheet *TabSheet10;
	TPanel *Panel12;
	TButton *mRegisterFreshBatchBtn;
	TGroupBox *BatchesGB;
	TDBGrid *FreshBatchesGrid;
	TDBNavigator *CSFreshBatchNavigator;
	TButton *mPrintBatchLblBtn;
	TPanel *CSgridPanel;
	TButton *mRegisterCarbonCoatBatchBtn;
	TIntLabel *mNrOfSelectedCS;
	TLabel *Label6;
	TButton *mPrintCSLabelsBtn;
	TPageControl *PageControl3;
	TTabSheet *TabSheet11;
	TDBMemo *DBMemo1;
	TGroupBox *GroupBox11;
	TLabel *Label10;
	TDBLookupComboBox *DBLookupComboBox1;
	TLabel *Label16;
	TDBEdit *DBEdit7;
	TButton *mAddCSNote;
	TGroupBox *GroupBox12;
	TGroupBox *GroupBox13;
	TGroupBox *GroupBox14;
	TSTDStringLabeledEdit *mTestLabel;
	TButton *mPrintTestLabelBtn;
	TPanel *Panel13;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel17;
	TDBText *CSID;
	TDBLookupComboBox *UsersCB;
	TSplitter *Splitter4;
	TGroupBox *GroupBox18;
	TPanel *Panel18;
	TDBGrid *DBGrid1;
	TPopupMenu *CoverSlipPopup;
	TMenuItem *SetStatus1;
	TMenuItem *DiscardedMenuItem;
	TMenuItem *FreshoutoftheBoxMenuItem;
	TMenuItem *N1;
	TDBMemo *mBarCodeCommandMemo;
	TDataSource *settingsDS;
	TDBNavigator *settingsNavigator;
	TDBText *DBText4;
	TSplitter *Splitter7;
	TGroupBox *SpecimenGB;
	TDBNavigator *SpecimenNavigator;
	TDBGrid *SpecimenGrid;
	TDataSource *SpecimenDS;
	TPanel *Panel6;
	TPanel *Panel19;
	TBitBtn *UnlocktablesBtn;
	TRadioGroup *SpecieRG;
	TApplicationEvents *ApplicationEvents1;
	TPageControl *MediaPageControl;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox16;
	TDBLookupListBox *BlockIDSLLB;
	TBrowseForFolder *BrowseForFolder1;
	TTabSheet *TabSheet14;
	TImagesFrame *TImagesFrame1;
	TMoviesFrame *TMoviesFrame1;
	TGroupBox *GroupBox20;
	TButton *BrowseForMediaFolderBtn;
	TSTDStringLabeledEdit *MediaFolderE;
	TButton *RegisterPostSilanizationBatch;
	TButton *mRegisterCleanRoundBtn;
	TPGConnectionFrame *TPGConnectionFrame1;
	TLabel *Label4;
	TPanel *Panel10;
	TDBNavigator *DBNavigator1;
	TLabel *Label5;
	TTabSheet *TabSheet12;
	TDBGrid *DBGrid2;
	TGroupBox *GroupBox3;
	TDBNavigator *DBNavigator2;
	TGroupBox *GroupBox6;
	TPanel *Panel11;
	TDBMemo *DBMemo2;
	TDBNavigator *KnifeNoteNavigator;
	TDBNavigator *KnifeNotesNavigator;
	TDBGrid *DBGrid3;
	TPanel *Panel22;
	TGroupBox *GroupBox7;
	TPanel *Panel14;
	TLabel *Label8;
	TDBEdit *DBEdit2;
	TLabel *Label9;
	TDBLookupComboBox *DBLookupComboBox2;
	TLabel *Label11;
	TDBEdit *DBEdit3;
	TLabel *Label12;
	TDBEdit *DBEdit4;
	TLabel *Label13;
	TDBLookupComboBox *DBLookupComboBox3;
	TLabel *Label14;
	TDBLookupComboBox *DBLookupComboBox4;
	TLabel *Label15;
	TDBLookupComboBox *DBLookupComboBox5;
	TLabel *Label17;
	TDBLookupComboBox *DBLookupComboBox6;
	TLabel *Label18;
	TDBLookupComboBox *DBLookupComboBox7;
	TMoviesFrame *MoviesFrame1;
	TLabel *Label7;
	TDBLookupComboBox *BlockIDCB;
	TSplitter *Splitter2;
	TGroupBox *mBlocksGB;
	TGroupBox *BlockNotesGB;
	TPanel *Panel3;
	TDBMemo *mBlockNoteMemo;
	TDBNavigator *BlockNoteNavigator;
	TPanel *Panel4;
	TDBNavigator *BlockNotesNavigator;
	TDBGrid *mBlockNotesGrid;
	TPanel *Panel2;
	TPanel *Panel5;
	TDBGrid *BlocksGrid;
	TDBNavigator *BlocksNavigator;
	TGroupBox *GroupBox10;
	TMemo *mLblMakerMemo;
	TButton *Button1;
	TSTDStringLabeledEdit *CoverslipIDE;
	TArrayBotButton *ArrayBotButton1;
	TGroupBox *GroupBox5;
	TTabSheet *TabSheet2;
	TMenuItem *Options1;
	TMenuItem *ThemesMenu;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ClearMemoAExecute(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ThemesMenuClick(TObject *Sender);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall NavigatorClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall NavigatorBeforeAction(TObject *Sender, TNavigateBtn Button);
	void __fastcall mATDBServerBtnConnectClick(TObject *Sender);
	void __fastcall mUpdateNoteBtnClick(TObject *Sender);
	void __fastcall UsersCBCloseUp(TObject *Sender);
	void __fastcall SlicesGridDrawDataCell(TObject *Sender, const TRect &Rect, TField *Field, TGridDrawState State);
	void __fastcall SlicesGridDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall mTablesLBClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall mProcessForBlocksGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mProcessForBlocksGridCellClick(TColumn *Column);
	void __fastcall OpenAboutFormAExecute(TObject *Sender);
	void __fastcall PageControl2Change(TObject *Sender);
	void __fastcall mAddDocBtnClick(TObject *Sender);
	void __fastcall SlicesDBGridDblClick(TObject *Sender);
	void __fastcall SlicesGridMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SlicesGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall BlocksGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BlocksGridCellClick(TColumn *Column);
	void __fastcall SlicesGridMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SlicesGridTitleClick(TColumn *Column);
	void __fastcall mPrintTestLabelBtnClick(TObject *Sender);
	void __fastcall mRegisterFreshBatchBtnClick(TObject *Sender);
	void __fastcall mPrintBatchLblBtnClick(TObject *Sender);
	void __fastcall FreshBatchesGridCellClick(TColumn *Column);
	void __fastcall FreshBatchesGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mRegisterCleanRoundBtnClick(TObject *Sender);
	void __fastcall mRegisterCarbonCoatBatchBtnClick(TObject *Sender);
	void __fastcall FormBtnClick(TObject *Sender);
	void __fastcall CoverSlipsGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CoverSlipsGridCellClick(TColumn *Column);
	void __fastcall DiscardedMenuItemClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DBGridDblClick(TObject *Sender);
	void __fastcall UnlocktablesBtnClick(TObject *Sender);
	void __fastcall SpecieRGClick(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall BlockIDSLLBKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BlockIDSLLBKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);
	void __fastcall MediaPageControlChange(TObject *Sender);
	void __fastcall BlockIDSLLBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall mRibbonsGridCellClick(TColumn *Column);
	void __fastcall BlockIDCBCloseUp(TObject *Sender);
	void __fastcall CoverslipIDEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ArrayBotButton1Click(TObject *Sender);

    private:
        bool                                            gCanClose;
        ApplicationProperties                           mAppProperties;
		Poco::Mutex										mServerDBMutex;

		String __fastcall								createBlockLabel();
        TThreadMethod                                   logMsgMethod;
        void __fastcall                                 logMsg();
		int 											getCurrentUserID();

		LogFileReader                                   mLogFileReader;
        vector<TDBGrid*>								mDBGrids;

		void                                            setupWindowTitle();
		void                                            updateWindowTitle();
		string                                          mTempFileFolder;

                                                        //INI Parameters...
        shared_ptr<IniFileProperties>                   mGeneralProperties;
        dsl::Property<int>	                            mBottomPanelHeight;
		dsl::Property<int>	                            mMainTabIndex;
		dsl::Property<int>	                            BatchesGBHeight;
		dsl::Property<int>	                            mDustAssayResultImageHeight;
		dsl::Property<int>	                            mDustAssayBackGroundImageWidth;
		dsl::Property<dsl::LogLevel>	                mLogLevel;
		dsl::Property<string>	         		        mTableUnlockPassword;

        shared_ptr<IniFileProperties>                   mCoverslipPrintingProperties;
        shared_ptr<TRegistryProperties>                 mSplashProperties;
        dsl::Property<bool>                             mShowSplashOnStartup;

		dsl::Property<int>	                            mDBUserID;

        bool                                            setupAndReadIniParameters();
        void                                            setupIniFile();

		void __fastcall                                 AppInBox(mlxStructMessage &Msg);

		void    										populateUsers();
		void       __fastcall							afterDBServerConnect(System::TObject* Sender);
		void       __fastcall							afterDBServerDisconnect(System::TObject* Sender);
		void 		__fastcall 							selectBlocks();
		void 		__fastcall							selectCoverSlips(TDBGrid* masterGrid, TDBGrid* detailGrid);

		void 		__fastcall 							createBlockLabels();
		bool 											loadImage(const string& fName, TImage* img);

        //Custom event
		void 		__fastcall 							onDustAssayDataChanged(TObject *Sender);
      	BarCodeBuilder									mBCBuilder;

		void __fastcall 								openSpecimenForm();
		void __fastcall 								openSlicesForm();
		void __fastcall 								openBlocksForm();

		void            								populateMedia();
    public:		// User declarations
                    __fastcall                          TMainForm(TComponent* Owner);
                    __fastcall                          ~TMainForm();

        BEGIN_MESSAGE_MAP
                  MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif
