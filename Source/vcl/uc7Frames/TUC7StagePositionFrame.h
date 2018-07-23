#ifndef TUC7StagePositionFrameH
#define TUC7StagePositionFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerEdit.h"
#include "dslTIntLabel.h"
#include "dslTIntLabel.h"
//---------------------------------------------------------------------------

class PACKAGE TUC7StagePositionFrame : public TFrame
{
    __published:
        TIntegerEdit *ValueMM;
        TLabel *Label1;
        TIntegerEdit *Valueum;
        TLabel *Label2;
        TIntegerEdit *Valuenm;
        TLabel *Label3;
	TGroupBox *GroupBox1;
	TIntLabel *AbsPosE;
        void __fastcall AbsPosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall posEdit(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
		void				updateFromInput(unsigned int input);
        unsigned int   		mUC7Value;

    public:
        		__fastcall 	TUC7StagePositionFrame(TComponent* Owner);
        unsigned int		getValue();
        void				setValue(unsigned int absValue);
};

extern PACKAGE TUC7StagePositionFrame *UC7StagePositionFrame;
#endif
