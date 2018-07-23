#ifndef TRegisterNewRibbonFormH
#define TRegisterNewRibbonFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBCtrls.hpp>
#include "TMainForm.h"
#include <Vcl.Mask.hpp>
#include "TArrayBotBtn.h"
#include <string>

using std::string;
//---------------------------------------------------------------------------
class PACKAGE TRegisterNewRibbonForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TPanel *Panel1;
	TArrayBotButton *mCancelBtn;
	TLabel *mCSBarcode;
	TLabel *Label1;
	TLabel *Label2;
	TGroupBox *GroupBox5;
	TDBText *RibbonID;
	TDBText *DBText2;
	TLabel *Label3;
	TArrayBotButton *mDecrementCuttingOrderBtn;
	TArrayBotButton *mIncrementSectionBtn;
	TLabel *Label4;
	TArrayBotButton *mDecrementSectionBtn;
	TArrayBotButton *mIncrementCuttingOrderBtn;
	TLabel *Label5;
	TDBText *DBText3;
	TLabel *Label6;
	TDBText *DBText4;
	TLabel *Label7;
	TDBText *DBText5;
	TDBText *mNrOfSectionsDBLbl;
	TDBText *mCuttingOrderDBLbl;
	TArrayBotButton *mRegisterBtn;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox6;
	TGroupBox *GroupBox7;
	TDBText *DBText6;
	TLabel *Label8;
	TPanel *Panel3;
	TMemo *mRibbonNoteMemo;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall mOkCancelBtnClick(TObject *Sender);
	void __fastcall miscBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

    private:
		string						mBarCode;
        string						mRibbonID;
        TMainForm&					mMainForm;
		int 						extractCoverSlipID(const string& bc);
        bool            			createNoteForCurrentRibbon(const string& ribbonID);
        bool						updateCoverSlipStatus();


    public:
                        __fastcall	TRegisterNewRibbonForm(TMainForm& mf);
		void						setCoverSlipBarcode(const string& barcode);
		string 						getRibbonID();
};

extern PACKAGE TRegisterNewRibbonForm *RegisterNewRibbonForm;
#endif
