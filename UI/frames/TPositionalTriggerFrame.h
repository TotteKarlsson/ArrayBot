#ifndef TPositionalTriggerFrameH
#define TPositionalTriggerFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class PositionalTrigger;
class Process;
class AbsoluteMove;
namespace ab
{
	class Move;
}
class ArrayBot;

class TPositionalTriggerFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *MainGB;
        TFloatLabeledEdit *FloatLabeledEdit1;
        TRadioGroup *RadioGroup1;
	TComboBox *mDevicesCB;
        TComboBox *ComboBox3;
        TGroupBox *GroupBox2;
        TFloatLabeledEdit *mNewVelE;
        TFloatLabeledEdit *mNewAccE;
        TLabel *Label2;
        TLabel *Label3;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;

    private:
		PositionalTrigger*			mTrigger;
        ab::Move* 	   					mMove;
        ArrayBot*					mAB;
		void 						populateDevicesCB();


    public:
    					__fastcall 	TPositionalTriggerFrame(TComponent* Owner);
    	void						populate(ArrayBot& ab, ab::Move* p);
    	void						rePopulate(ab::Move* p);

};

//---------------------------------------------------------------------------
extern PACKAGE TPositionalTriggerFrame *PositionalTriggerFrame;
//---------------------------------------------------------------------------
#endif
