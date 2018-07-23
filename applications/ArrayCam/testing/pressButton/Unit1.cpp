#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "dslVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"

TForm1 *Form1;

using namespace dsl;



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    clickOnWindow(WinCaption->getValue(), ClickX->getValue(), ClickY->getValue());
}


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    HWND hwnd = FindWindow(0, wstr(WinCaption->getValue()).c_str() );
    if(hwnd)
    {
    	enableDisableGroupBox(GroupBox1, true);
	    POINT p;
		if (GetCursorPos(&p))
        {
        	if (::ScreenToClient(hwnd, &p))
			{
			    //p.x and p.y are now relative to hwnd's client area
		        winXLbl->Caption = "X = " + IntToStr((int) p.x);
		        winYLbl->Caption = "Y = " + IntToStr((int) p.y);
			}
        }
    }
    else
    {
    	enableDisableGroupBox(GroupBox1, false);
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	Timer1->Enabled = true;
}



