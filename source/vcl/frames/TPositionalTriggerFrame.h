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
class Trigger;
class ArrayBot;

class PACKAGE TPositionalTriggerFrame : public TFrame
{
    __published:	// IDE-managed Components
		TFloatLabeledEdit *mPositionE;
		TRadioGroup *mOpRG;
		TComboBox *mDevicesCB;
        TFloatLabeledEdit *mNewVelE;
        TFloatLabeledEdit *mNewAccE;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
		TFloatLabeledEdit *mFinalPositionE;
		void __fastcall mPositionEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall mOpRGClick(TObject *Sender);
		void __fastcall mDevicesCBChange(TObject *Sender);
		void __fastcall mNewVelEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
        Trigger* 	 				mTrigger;
        ArrayBot*					mAB;
		void 						populateDevicesCB();

    public:
    					__fastcall 	TPositionalTriggerFrame(TComponent* Owner);
    	void						populate(ArrayBot& ab, Trigger* pt);
    	void						rePopulate(Trigger* p);
};

extern PACKAGE TPositionalTriggerFrame *PositionalTriggerFrame;
//---------------------------------------------------------------------------
#endif
