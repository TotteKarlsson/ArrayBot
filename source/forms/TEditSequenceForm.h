#ifndef TEditSequenceFormH
#define TEditSequenceFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include "TIntegerLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TPropertyCheckBox.h"
//---------------------------------------------------------------------------

class PACKAGE TEditSequenceForm : public TForm
{
    __published:	// IDE-managed Components
        TSTDStringLabeledEdit *SequenceNameE;
        TIntegerLabeledEdit *SequenceOrderE;
        TArrayBotButton *OKBtn;
        TArrayBotButton *CancelBtn;
	TPropertyCheckBox *UseProcessControllerCB;
    private:

    public:
        __fastcall TEditSequenceForm(TComponent* Owner);
};

extern PACKAGE TEditSequenceForm *EditSequenceForm;
#endif
