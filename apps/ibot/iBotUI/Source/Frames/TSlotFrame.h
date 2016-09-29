#ifndef TSlotFrameH
#define TSlotFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

class TSlotFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TButton *Button3;
	TButton *Button1;
	TComboBox *mRibbonCB;
private:	// User declarations

public:		// User declarations
	__fastcall TSlotFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSlotFrame *SlotFrame;
//---------------------------------------------------------------------------
#endif
