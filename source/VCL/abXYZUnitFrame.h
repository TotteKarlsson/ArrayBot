#ifndef abXYZUnitFrameH
#define abXYZUnitFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "abXYZUnit.h"
#include "abMotorFrame.h"
//---------------------------------------------------------------------------

class TXYZUnitFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *mainGB;
	TPanel *Panel1;
	TScrollBox *ScrollBox1;
	TMotorFrame *TMotorFrame1;
	TMotorFrame *MotorFrame1;
	TMotorFrame *MotorFrame2;
    private:	// User declarations
        XYZUnit*			mUnit;

    public:		// User declarations
        __fastcall TXYZUnitFrame(TComponent* Owner);
        void			assignUnit(XYZUnit* u);
};
//---------------------------------------------------------------------------
extern PACKAGE TXYZUnitFrame *XYZUnitFrame;
//---------------------------------------------------------------------------
#endif
