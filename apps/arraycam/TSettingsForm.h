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
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mArduinoServerPortE;
	TButton *mASStartBtn;
	TTimer *UIUpdateTimer;
	void __fastcall mASStartBtnClick(TObject *Sender);
	void __fastcall UIUpdateTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations


	TMainForm&			mMainForm;

	__fastcall TSettingsForm(TMainForm& mf);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
