#ifndef THomeMotorProcessFrameH
#define THomeMotorProcessFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslTFloatLabeledEdit.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

class HomeMotor;
class ProcessSequencer;
class ArrayBot;

class PACKAGE THomeMotorProcessFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *mMainGB;
	TComboBox *MotorsCB;
	TLabel *Label1;
	TLabel *mActionInfo;
	TPanel *Panel2;
	TPanel *Panel1;
	void __fastcall MotorsCBChange(TObject *Sender);
	void __fastcall mActionInfoClick(TObject *Sender);

    private:	// User declarations
        HomeMotor* 	   				mHomeMotorProcess;
        ProcessSequencer&			mProcessSequencer;
        ArrayBot&					mAB;
		void 						populateMotorCB();

    public:		// User declarations
                        __fastcall THomeMotorProcessFrame(ProcessSequencer& ps, TComponent* Owner);
        void            		   populate(HomeMotor* m);
        void            		   rePopulate(HomeMotor* m);
        void            		   update();
};

extern PACKAGE THomeMotorProcessFrame *HomeMotorProcessFrame;
#endif
