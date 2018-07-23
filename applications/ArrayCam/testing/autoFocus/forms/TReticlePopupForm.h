#ifndef TReticlePopupFormH
#define TReticlePopupFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include "dslTPropertyCheckBox.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include "atReticle.h"
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
//---------------------------------------------------------------------------

class PACKAGE TReticlePopupForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TTrackBar *mReticleRadiusTB;
        TTrackBar *mReticleCenterXTB;
        TTrackBar *mReticleCenterYTB;
        TArrayBotButton *mCenterReticleBtn;
        TPropertyCheckBox *mReticleVisibilityCB;
		TTimer *ShowTimer;
        void __fastcall mReticleTBChange(TObject *Sender);
        void __fastcall mCenterReticleBtnClick(TObject *Sender);
        void __fastcall mReticleVisibilityCBClick(TObject *Sender);
		void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall ShowTimerTimer(TObject *Sender);
		void __fastcall GroupBox1Click(TObject *Sender);
    private:

		bool									mMovingReticle;
        TReticle&								mReticle;

	public:
		__fastcall 								TReticlePopupForm(TReticle& reticle, TComponent* Owner);
		__fastcall 								~TReticlePopupForm();
};

extern PACKAGE TReticlePopupForm *ReticlePopupForm;
#endif
