#include <vcl.h>
#pragma hdrstop
#include "TNavitarPresetFrame.h"
#include "navitar/atNavitarMotorController.h"
#include "navitar/atNavitarPreset.h"
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace at;
TNavitarPresetFrame *NavitarPresetFrame;
static int frameNr = 0;
//---------------------------------------------------------------------------
__fastcall TNavitarPresetFrame::TNavitarPresetFrame(NavitarPreset& preset, TComponent* Owner)
	: TFrame(Owner),
    mPreset(preset)
{
	this->Name = "NavitarPresetFrame_" + IntToStr(frameNr++);
    MainGB->Caption = preset.getName().c_str();
	FocusPos->setValue(mPreset.getFocusPreset());
    ZoomPos->setValue(mPreset.getZoomPreset());
}

//---------------------------------------------------------------------------
void __fastcall TNavitarPresetFrame::GoButtonClick(TObject *Sender)
{
	mPreset.set();
}

//---------------------------------------------------------------------------
void __fastcall TNavitarPresetFrame::onKey(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
		TIntegerLabeledEdit* e = dynamic_cast<TIntegerLabeledEdit*>(Sender);
        if(e == FocusPos)
        {
	        mPreset.setFocus(e->getValue());
        }
        else if(e == ZoomPos)
        {
        	mPreset.setZoom(e->getValue());
        }
    }
}


