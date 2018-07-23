#include <vcl.h>
#pragma hdrstop
#include "TActionsForm.h"
#include "ArrayCamMessages.h"
#include "dslLogger.h"
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TActionsForm *ActionsForm;
using namespace dsl;


//---------------------------------------------------------------------------
__fastcall TActionsForm::TActionsForm(HWND__* handle, TComponent* Owner)
	: TForm(Owner),
    mHandle(handle)
{
}

//---------------------------------------------------------------------------
void __fastcall TActionsForm::FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	int sc_DragMove = 0xF012;
    ReleaseCapture();
    Perform( WM_SYSCOMMAND, sc_DragMove, 0 );
}


//---------------------------------------------------------------------------
void __fastcall TActionsForm::StopAtTopAExecute(TObject *Sender)
{
	//Send application message to stop at top
    int msg=10;
    if(!PostMessage(mHandle, UWM_AM_MESSAGE, atMiscMessage, (long) msg))
    {
    	Log(lError) << "Post message failed in UC7 Message receiver.";
    }
}


