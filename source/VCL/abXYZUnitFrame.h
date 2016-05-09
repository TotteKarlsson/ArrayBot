//---------------------------------------------------------------------------

#ifndef abXYZUnitFrameH
#define abXYZUnitFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TXYZUnitFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *mNameE;
private:	// User declarations
public:		// User declarations
	__fastcall TXYZUnitFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TXYZUnitFrame *XYZUnitFrame;
//---------------------------------------------------------------------------
#endif
