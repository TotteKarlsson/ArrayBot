#include <vcl.h>
#pragma hdrstop
#include "TCombinedMoveFrame.h"
#include "mtkVCLUtils.h"
#include "abProcess.h"
#include "abMove.h"
#include "abCombinedMove.h"
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "abAPTMotor.h"
#include "abAbsoluteMove.h"

#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"

using namespace mtk;

TCombinedMoveFrame *CombinedMoveFrame;
//---------------------------------------------------------------------------

__fastcall TCombinedMoveFrame::TCombinedMoveFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TCombinedMoveFrame::populate(ArrayBot& ab, Process* p)
{
	mAB = &ab;
	rePopulate(p);
}

void TCombinedMoveFrame::rePopulate(Process* p)
{
	mMoveLB->Clear();

	//Populate, update frame with data from process
    mCombinedMove = dynamic_cast<CombinedMove*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

	mProcessNameE->setValue(mCombinedMove->getProcessName());
    //Fill out the listbox with moves
    for(int i = 0; i < mCombinedMove->getNumberOfMoves(); i++)
    {
    	ab::Move* mv = mCombinedMove->getMove(i);
        if(mv)
        {
        	mMoveLB->Items->Add(vclstr(mv->getProcessName()));
        }
    }

  	EnableDisableFrame(this, true);
   	EnableDisableFrame(this->TMotorMoveProcessFrame1, false);
}

void __fastcall TCombinedMoveFrame::addMoveAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mCombinedMove)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

    ab::Move* lm = new AbsoluteMove("");

    //Add the move to the container.. this will give the move a name
    mCombinedMove->addMove(lm);

    //Add move to Listbox
    int indx = mMoveLB->Items->Add(lm->getProcessName().c_str());
	mMoveLB->ItemIndex = indx;

	//Select the new process
    selectItem(lm);
}

//---------------------------------------------------------------------------
void __fastcall TCombinedMoveFrame::removeMoveAExecute(TObject *Sender)
{
	//Get selected move
    int index = mMoveLB->ItemIndex;
    if(index != -1)
    {
    	string moveName = stdstr(mMoveLB->Items->Strings[index]);
        mCombinedMove->removeMove(moveName);
		rePopulate(mCombinedMove);
    }
}

void TCombinedMoveFrame::selectItem(ab::Move* mv)
{
	if(dynamic_cast<AbsoluteMove*>(mv))
    {
		this->TMotorMoveProcessFrame1->populate(mAB, dynamic_cast<AbsoluteMove*>(mv));
   		EnableDisableFrame(this->TMotorMoveProcessFrame1, true);
    }
}

void __fastcall TCombinedMoveFrame::mMoveLBClick(TObject *Sender)
{
	if(mMoveLB->ItemIndex == -1 || mCombinedMove == NULL)
    {
    	return;
    }

	//Get Current itemIndex, retrieve the move and populate the move frame
	string moveName = stdstr(mMoveLB->Items->Strings[mMoveLB->ItemIndex]);
    ab::Move* mv = mCombinedMove->getMove(moveName);

    selectItem(mv);
}


//---------------------------------------------------------------------------
void __fastcall TCombinedMoveFrame::mProcessNameEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mCombinedMove != NULL)
    {
   		mCombinedMove->setProcessName(mProcessNameE->getValue());
    }
}

