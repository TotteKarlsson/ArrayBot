#include <vcl.h>
#pragma hdrstop
#include "TReticlePopupForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "dslTPropertyCheckBox"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TReticlePopupForm *ReticlePopupForm;

//---------------------------------------------------------------------------
__fastcall TReticlePopupForm::TReticlePopupForm(TReticle& reticle, TComponent* Owner)
	: TForm(Owner),
    mMovingReticle(false),
    mReticle(reticle)

{
}

//---------------------------------------------------------------------------
__fastcall TReticlePopupForm::~TReticlePopupForm()
{
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::mReticleTBChange(TObject *Sender)
{
	TTrackBar* tb = dynamic_cast<TTrackBar*>(Sender);

    if(!mMovingReticle)
    {
        if(tb == mReticleRadiusTB)
        {
            mReticle.setCircleRadius(tb->Position);
        }
        else if(tb == mReticleCenterXTB)
        {
            mReticle.setReticleCenter(tb->Position, mReticleCenterYTB->Position);
        }
        else if(tb == mReticleCenterYTB)
        {
            mReticle.setReticleCenter(mReticleCenterXTB->Position, tb->Position);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::mCenterReticleBtnClick(TObject *Sender)
{
    mReticle.setReticleCenter(0,0);
    mReticleCenterXTB->Position = 0;
    mReticleCenterYTB->Position = 0;
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::mReticleVisibilityCBClick(TObject *Sender)
{
	mReticleVisibilityCB->OnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::ShowTimerTimer(TObject *Sender)
{
	ShowTimer->Enabled = false;
    this->Hide();
}

//---------------------------------------------------------------------------
void __fastcall TReticlePopupForm::GroupBox1Click(TObject *Sender)
{
    this->Hide();
}
