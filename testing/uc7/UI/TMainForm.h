#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
#include "Core/atDBApplicationMessages.h"
#include "Core/atDBDataStructures.h"
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
#include "TArrayBotBtn.h"
#include "database/atATDBServerSession.h"
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include "TTableFrame.h"
#include "pBarcode2D.hpp"
#include "pCore2D.hpp"
#include "pDataMatrix.hpp"
#include "pDBBarcode2D.hpp"
#include "pQRCode.hpp"
#include "TIntLabel.h"

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
    TFileExit *FileExit1;
    TMenuItem *Exit1;
    TAction *OpenAboutFormA;
    TMenuItem *About1;
    TTimer *ShutDownTimer;
	TMemo *infoMemo;
	TPanel *BottomPanel;
	TPanel *Panel1;
	TComboBox *LogLevelCB;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);

    void __fastcall ClearMemoAExecute(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ThemesMenuClick(TObject *Sender);
    void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LogLevelCBChange(TObject *Sender);



    private:
        bool                                            gCanClose;
        TApplicationProperties                          mAppProperties;

        TThreadMethod                                   logMsgMethod;
        void __fastcall                                 logMsg();
		LogFileReader                                   mLogFileReader;
		bool                                            mIsStyleMenuPopulated;
		void                                            setupWindowTitle();
		void                                            updateWindowTitle();


														//Threads can drop messages into the
														//Message container. The main thread pops them
														//using the messageProcessor
		MessageContainer                                mMessages;



                                                        //INI Parameters...
        IniFileProperties	      	                    mGeneralProperties;
        mtk::Property<int>	                            mBottomPanelHeight;
		mtk::Property<mtk::LogLevel>	                mLogLevel;
        TRegistryProperties   	  	                    mSplashProperties;
        mtk::Property<bool>                             mShowSplashOnStartup;

        void        __fastcall                          PopulateStyleMenu();

        bool                                            setupAndReadIniParameters();
        void                                            setupIniFile();

		void __fastcall                                 AppInBox(mlxStructMessage &Msg);

    public:		// User declarations
                    __fastcall                          TMainForm(TComponent* Owner);
                    __fastcall                          ~TMainForm();

        BEGIN_MESSAGE_MAP
                  MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);
        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif
