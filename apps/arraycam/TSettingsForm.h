#ifndef TSettingsFormH
#define TSettingsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TMainForm.h"
#include "TPropertyCheckBox.h"
#include <Vcl.ComCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArduinoServerPortE;
	TButton *mASStartBtn;
	TTimer *UIUpdateTimer;
	TGroupBox *GroupBox2;
	TPropertyCheckBox *mVerticalMirrorCB;
	TPropertyCheckBox *mHorizontalMirrorCB;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TButton *Button1;
	TPropertyCheckBox *mAutoExposureCB;
	TPropertyCheckBox *mAutoGainCB;
	TGroupBox *GroupBox5;
	TPropertyCheckBox *mPairLEDsCB;
	TSTDStringLabeledEdit *mPhotoOutputBaseFolder;
	TSTDStringLabeledEdit *mMoviesFolderE;
	TButton *mBrowseForImagesFolderBtn;
	TButton *mBrowseForMoviesFolderBtn;
	TTrackBar *mGammaSB;
	TLabel *mGamma;
	void __fastcall mASStartBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mVerticalMirrorCBClick(TObject *Sender);
	void __fastcall mHorizontalMirrorCBClick(TObject *Sender);
	void __fastcall AutoParaCBClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall mPairLEDsCBClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BrowseForFolder(TObject *Sender);
	void __fastcall mGammaSBChange(TObject *Sender);


private:	// User declarations
public:		// User declarations


	TMainForm&			mMainForm;

	__fastcall TSettingsForm(TMainForm& mf);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
