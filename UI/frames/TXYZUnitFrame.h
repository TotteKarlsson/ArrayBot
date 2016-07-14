#ifndef TXYZUnitFrameH
#define TXYZUnitFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class XYZUnit;
class TMotorFrame;

class TXYZUnitFrame : public TFrame
{
    __published:
        TGroupBox 		*mainGB;
		TPanel 			*TopPanel;
        TScrollBox 		*ScrollBox1;

    private:
        XYZUnit*			    mUnit;
        TMotorFrame*		    mXMotorFrame;
        TMotorFrame*		    mYMotorFrame;
        TMotorFrame*		    mZMotorFrame;
        TMotorFrame*		    mAngleMotorFrame;
		static int				mFrameNr;

    public:
        __fastcall 			    TXYZUnitFrame(TComponent* Owner);
        void				    assignUnit(XYZUnit* u);
        void				    disable();
};
extern PACKAGE TXYZUnitFrame *XYZUnitFrame;

#endif
