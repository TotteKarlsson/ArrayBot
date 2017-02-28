#pragma hdrstop
#include "TGeneralOptionsFrame.h"
#include "mtkIniFileProperties.h"
#include "TOptionsForm.h"
#include "mtkVCLUtils.h"
#include "amlApplicationMessages.h"
#include "ApplicationUtilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
TGeneralOptionsFrame *GeneralOptionsFrame;
//---------------------------------------------------------------------------

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TGeneralOptionsFrame::TGeneralOptionsFrame(TApplicationProperties& props, TComponent* Owner)
:
TFrame(Owner),
mApplicationProperties(props),
mParent(dynamic_cast<TOptionsForm*>(Owner))
{}

__fastcall TGeneralOptionsFrame::~TGeneralOptionsFrame()
{}

void __fastcall TGeneralOptionsFrame::setup()
{
    ClearHistoryA->Enabled = true;
    Properties* generalProperties = mApplicationProperties.getSection("General");
    if(generalProperties)
    {

        //Setup frame
        Property<int> *hist = dynamic_cast<Property<int>* >(generalProperties->getProperty("NUMBER_OF_HISTORY_ITEMS"));
        if(hist)
        {
            mNrOfHistoryItems->assignExternalProperty(hist, false);
            hist->resetModifiedFlag();
        }
    }

    Properties* splashProperties = mApplicationProperties.getSection("Splash");
    if(splashProperties)
    {
        Property<bool> *showSplash = dynamic_cast< Property<bool>* >(splashProperties->getProperty("ShowOnStartup"));
        if(showSplash)
        {
            ShowSplashOnStartupCB->assignExternalProperty(showSplash, false);
            showSplash->resetModifiedFlag();
        }
    }
}

bool TGeneralOptionsFrame::hasChanges()
{
    return mApplicationProperties.hasChanges();
}

//---------------------------------------------------------------------------
void __fastcall TGeneralOptionsFrame::mNrOfHistoryItemsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == vkReturn)
    {
        //Check sender parameter and set corresponding property to modified
        TIntegerLabeledEdit *test = dynamic_cast< TIntegerLabeledEdit* >(Sender);
        if(test)
        {
            test->getProperty()->setModifiedFlag();
        }

        if(mParent)
        {
            mParent->OKAction->Enabled = true;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TGeneralOptionsFrame::CheckBoxClick(TObject *Sender)
{
    //Check sender parameter and set corresponding property to modified
    TPropertyCheckBox *test = dynamic_cast< TPropertyCheckBox* >(Sender);

    if(test)
    {
        test->OnClick(Sender);
    }

    if(test && test->getProperty())
    {
        test->getProperty()->setModifiedFlag();
    }

    if(mParent)
    {
        mParent->OKAction->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TGeneralOptionsFrame::ClearHistoryAExecute(TObject *Sender)
{
    ClearHistoryA->Enabled = false;

    //Send message to main application to clear history
    HWND hWnd = Application->MainForm->Handle;
    if(sendAppMessage(hWnd, amClearHistory) != true)
    {
        ;
    }
}



