#ifndef abAddJoyStickSettingFormH
#define abAddJoyStickSettingFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "arraybot/joystick/atJoyStickSetting.h";
//---------------------------------------------------------------------------

class PACKAGE TAddJoyStickSettingForm : public TForm
{
__published:	// IDE-managed Components
	TSTDStringLabeledEdit *mSettingsNameE;
	TFloatLabeledEdit *mMaxXYVelocityE;
	TFloatLabeledEdit *mXYAcc;
	TFloatLabeledEdit *mMaxZVelocityE;
	TFloatLabeledEdit *mZAccE;
	TButton *CancelBtn;
	TButton *Button2;
private:	// User declarations
public:		// User declarations
	__fastcall TAddJoyStickSettingForm(TComponent* Owner);
    JoyStickSetting		getSetting();
};

extern PACKAGE TAddJoyStickSettingForm *AddJoyStickSettingForm;

#endif
