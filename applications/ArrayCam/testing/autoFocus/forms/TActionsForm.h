#ifndef TActionsFormH
#define TActionsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "TArrayBotBtn.h"
//---------------------------------------------------------------------------


class PACKAGE TActionsForm : public TForm
{
    __published:
	TActionList *ActionList1;
	TAction *StopAtTopA;
	TArrayBotButton *ArrayBotButton1;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall StopAtTopAExecute(TObject *Sender);


    private:
        											//The handle is needed for window messaging
        HWND__*										mHandle;

    public:
        					__fastcall TActionsForm(HWND__* handle, TComponent* Owner);
};


extern PACKAGE TActionsForm *ActionsForm;
#endif
