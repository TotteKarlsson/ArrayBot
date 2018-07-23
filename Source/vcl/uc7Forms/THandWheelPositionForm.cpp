#include <vcl.h>
#pragma hdrstop
#include "THandWheelPositionForm.h"
#include "Poco/TimeSpan.h"
#include "dslLogger.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace dsl;
THandWheelPositionForm *HandWheelPositionForm;

//---------------------------------------------------------------------------
__fastcall THandWheelPositionForm::THandWheelPositionForm(UC7StatusHistory& h, const string& regRoot, TComponent* Owner)
	: TRegistryForm(regRoot, "HandWheelPositionForm", Owner),
    mUC7StatusHistory(h)
{}

__fastcall THandWheelPositionForm::~THandWheelPositionForm()
{}

void THandWheelPositionForm::plot()
{
	if(!this->Visible)
    {
    	return;
    }

	Series1->Clear();

    deque<UC7StatusPoint> c = mUC7StatusHistory.getCurrentCycle();

    if(!c.size())
    {
    	return;
    }

   	UC7StatusPoint p = c[0];
    Poco::Timestamp start(p.time);
    for(int i = 0; i < c.size(); i++)
    {
    	Poco::Timespan span(c[i].time - start);
        double spanS = span.seconds() + (span.milliseconds() * 0.001);
        Log(lDebug) << "Adding XY Point" <<spanS<<", "<<c[i].status;
    	Series1->AddXY(spanS, c[i].status);
        if(spanS > Chart1->BottomAxis->Maximum)
        {
			Chart1->BottomAxis->Maximum = spanS * 1.10;
        }
    }
}

void __fastcall THandWheelPositionForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "Closing Hand WheelPosition form";
    TRegistryForm::FormClose(Sender, Action);
}

//---------------------------------------------------------------------------
void __fastcall THandWheelPositionForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	//Main app need to 'allow' form to close. If not allowed, just hide the forme
   	CanClose = mTimeToClose ? true : false;
    if(!CanClose)
    {
    	this->Visible = false;
    }
}

void THandWheelPositionForm::setTimeToClose()
{
	mTimeToClose = true;
}

//---------------------------------------------------------------------------
void __fastcall THandWheelPositionForm::FormShow(TObject *Sender)
{
	readRegistry();
    Chart1->Axes->Left->Items->Clear();
    Chart1->Axes->Left->Items->Add(ssBeforeCutting, toText(ssBeforeCutting).c_str());
    Chart1->Axes->Left->Items->Add(ssCutting, 		toText(ssCutting).c_str());
    Chart1->Axes->Left->Items->Add(ssAfterCutting, 	toText(ssAfterCutting).c_str());
    Chart1->Axes->Left->Items->Add(ssRetracting, 	toText(ssRetracting).c_str());
}

//---------------------------------------------------------------------------
void __fastcall THandWheelPositionForm::FormCreate(TObject *Sender)
{
	readRegistry();
}

//---------------------------------------------------------------------------
void __fastcall THandWheelPositionForm::FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}
