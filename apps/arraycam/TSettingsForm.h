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
	TButton *Button2;
	void __fastcall mASStartBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
	void __fastcall mVerticalMirrorCBClick(TObject *Sender);
	void __fastcall mHorizontalMirrorCBClick(TObject *Sender);
	void __fastcall AutoParaCBClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations


	TMainForm&			mMainForm;

	__fastcall TSettingsForm(TMainForm& mf);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
