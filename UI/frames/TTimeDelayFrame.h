#ifndef TTimeDelayFrameH
#define TTimeDelayFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TMotorMoveProcessFrame.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "abArrayBot.h"
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TIntegerLabeledEdit.h"

class Process;
class TimeDelay;

class XYZUnit;
//---------------------------------------------------------------------------
class TTimeDelayFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *mTimeDelayE;

    private:	// User declarations
		ArrayBot*						mAB;
		TimeDelay*						mTimeDelay;


	public:		// User declarations
							__fastcall  TTimeDelayFrame(TComponent* Owner);

    	void							populate(ArrayBot& ab, Process* p);
    	void							rePopulate(Process* p);
};

extern PACKAGE TTimeDelayFrame *TimeDelayFrame;
#endif
