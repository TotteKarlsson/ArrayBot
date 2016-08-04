#pragma hdrstop
#include "TOptionsForm.h"
#include "TGeneralOptionsFrame.h"
#include "mtkIniFileProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TApplicationProperties& props, TComponent* Owner)
    :
TForm(Owner),
mGOF(NULL),
mCurrentOptionFrame(NULL),
mApplicationProperties(props),
mCancelBtnWasClicked(false)
{}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        this->ModalResult = mrCancel;
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    //If things been changed, ask before closing
    if(mCancelBtnWasClicked)
    {
        CanClose = true;
        return;
    }

    if(mApplicationProperties.hasChanges())
    {
//        int mrResult = MessageDlg("There are changes. \nSave?", mtWarning, TMsgDlgButtons() << mbYes<<mbNo<<mbCancel, 0);
//        if(mrResult == mrYes)
//        {
//            applyChanges();
//            CanClose = true;
//        }
//        else if(mrResult == mrNo)
//        {
//            CanClose = true;
//        }
//        else if(mrResult == mrCancel)
//        {
//            CanClose = false;
//        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}

TTreeNode* __fastcall TOptionsForm::getSelected()
{
    return mTree->Selected;
}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::mTreeClick(TObject *Sender)
{
    //Get selected node
    TTreeNode* aNode = getSelected();

    if(aNode)
    {
        if(aNode->Text == "General")
        {
            showFrame(ofGeneral);
        }
    }
}

void TOptionsForm::showFrame(OptionFrame of)
{
    switch(of)
    {
        case ofGeneral:
            if(!mGOF)
            {
                mGOF = new TGeneralOptionsFrame(mApplicationProperties, this);
                mGOF->Parent = Panel1;
                mCurrentOptionFrame = mGOF;
            }

        break;

        default:
        ;
    }

    if(mCurrentOptionFrame)
    {
        mCurrentOptionFrame->Visible = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::OKActionExecute(TObject *Sender)
{

    if(mApplicationProperties.hasChanges())
    {
        applyChanges();
    }
    OKAction->Enabled = false;

    //This causes the form to close
    this->ModalResult = mrOk;
}

void TOptionsForm::applyChanges()
{
    //Transfer changes
    Properties* props = mApplicationProperties.getFirstSection();
    while(props != NULL)
    {
        if(props->isModified())
        {
            props->applyModifications();
        }

        props = mApplicationProperties.getNextSection();
    }
}

//---------------------------------------------------------------------------
void __fastcall TOptionsForm::CancelBtnClick(TObject *Sender)
{
    mCancelBtnWasClicked = true;
}


//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
    //Fill out the tree
    Properties* props = mApplicationProperties.getFirstSection();
    while( props != NULL)
    {
        string section = props->getSection();
        if(compareStrings(section, "General", csCaseInsensitive) == true)
        {
            mTree->Items->Insert(NULL, section.c_str());
        }
        else
        {
            ;
        }


        props = mApplicationProperties.getNextSection();
    }

    //Select the top node
    TTreeNode* root = mTree->Items->GetFirstNode();
    mTree->Selected  = root;
    mTreeClick(Sender);

    if(mGOF)
    {
        mGOF->setup();
    }
}


