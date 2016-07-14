//---------------------------------------------------------------------------

#ifndef TPositionalTriggerFrameH
#define TPositionalTriggerFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPositionalTriggerFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TComboBox *ComboBox1;
	TLabel *Label1;
	TFloatLabeledEdit *FloatLabeledEdit1;
	TRadioGroup *RadioGroup1;
	TComboBox *ComboBox2;
	TComboBox *ComboBox3;
	TGroupBox *GroupBox2;
	TFloatLabeledEdit *mNewVelE;
	TFloatLabeledEdit *mNewAccE;
	TLabel *Label2;
	TLabel *Label3;
private:	// User declarations
public:		// User declarations
	__fastcall TPositionalTriggerFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPositionalTriggerFrame *PositionalTriggerFrame;
//---------------------------------------------------------------------------
#endif
