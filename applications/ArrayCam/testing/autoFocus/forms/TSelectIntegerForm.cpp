#include <vcl.h>
#pragma hdrstop
#include "TSelectIntegerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
TSelectIntegerForm *SelectIntegerForm;
//---------------------------------------------------------------------------
__fastcall TSelectIntegerForm::TSelectIntegerForm(TComponent* Owner)
	: TForm(Owner)
{
	NumbersList->Clear();
	for(int i = 0; i < 501; i++)
    {
		NumbersList->AddItem(IntToStr(i), NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectIntegerForm::NumbersListClick(TObject *Sender)
{
	int index = NumbersList->ItemIndex;
    if(index > -1)
    {
		int nr = NumbersList->Items->Strings[index].ToInt();
        mTheNumberLbl->setValue(nr);
    }
}

bool TSelectIntegerForm::setCurrentNumber(int nr)
{
	for(int i = 0; i < NumbersList->Count; i++)
    {
		int cnr = NumbersList->Items->Strings[i].ToInt();
        if(nr == cnr)
        {
			NumbersList->ItemIndex = i;
        }
    }
	NumbersListClick(NULL);
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TSelectIntegerForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSelectIntegerForm::NumbersListDrawItem(TWinControl *Control,
          int Index, TRect &Rect, TOwnerDrawState State)
{

// with (Control as TListBox).Canvas do
//	begin
//      FillRect(Rect);
//      NumbersList->Canvas->O
//      Offset := Round( Rect.Right/2 - TextWidth((Control as TListBox).Items[Index])/2 );
//      TextOut( Offset, Rect.Top, (Control as TListBox).Items[Index]  );
//	end;
}

