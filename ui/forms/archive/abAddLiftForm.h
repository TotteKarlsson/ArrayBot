#ifndef abAddLiftFormH
#define abAddLiftFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "abPairedMove.h";
//---------------------------------------------------------------------------

class TAddLiftSettingForm : public TForm
{
__published:	// IDE-managed Components
	TSTDStringLabeledEdit *mSettingsNameE;
	TFloatLabeledEdit *mVelocityE;
	TFloatLabeledEdit *mAcc;
	TFloatLabeledEdit *mDistanceE;
	TButton *CancelBtn;
	TButton *Button2;
private:	// User declarations

public:		// User declarations
	__fastcall TAddLiftSettingForm(TComponent* Owner);
    PairedMove						getSetting();
};

extern PACKAGE TAddLiftSettingForm *AddLiftSettingForm;

#endif
