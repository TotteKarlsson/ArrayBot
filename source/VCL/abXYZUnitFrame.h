#ifndef abXYZUnitFrameH
#define abXYZUnitFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//#include "abXYZUnit.h"
#include "abMotorFrame.h"
//---------------------------------------------------------------------------

class XYZUnit;
class TXYZUnitFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox 		*mainGB;
		TPanel 			*TopPanel;
        TScrollBox 		*ScrollBox1;
		TTimer 			*mMotorStatusTimer;
	void __fastcall mMotorStatusTimerTimer(TObject *Sender);

    private:	// User declarations
        XYZUnit*			mUnit;
        TMotorFrame*		mXMotorFrame;
        TMotorFrame*		mYMotorFrame;
        TMotorFrame*		mZMotorFrame;

    public:		// User declarations
        __fastcall 			TXYZUnitFrame(TComponent* Owner);
        void				assignUnit(XYZUnit* u);
        void				disable();
};
extern PACKAGE TXYZUnitFrame *XYZUnitFrame;

#endif
