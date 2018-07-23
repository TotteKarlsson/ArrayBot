#ifndef THandWheelPositionFormH
#define THandWheelPositionFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "uc7/atUC7StatusHistory.h"
#include "forms/dslTRegistryForm.h"
#include <VclTee.TeeGDIPlus.hpp>

class PACKAGE THandWheelPositionForm : public TRegistryForm
{
    __published:
        TChart*						            Chart1;
        TLineSeries*				            Series1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
		UC7StatusHistory&			            mUC7StatusHistory;
        bool									mTimeToClose;

    public:
    					__fastcall              THandWheelPositionForm(UC7StatusHistory& h,  const string& regRoot, TComponent* Owner);
    					__fastcall              ~THandWheelPositionForm();
		void						            reset();
        void									plot();
        void									setTimeToClose();
};

extern PACKAGE THandWheelPositionForm *HandWheelPositionForm;
#endif
