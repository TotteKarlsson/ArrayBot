#include <vcl.h>
#pragma hdrstop
#include "TCombinedMoveFrame.h"
#include "mtkVCLUtils.h"
#include "abProcess.h"
#include "abLinearMove.h"
#include "abCombinedLinearMove.h"
#include "mtkLogger.h"
#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"
#pragma resource "*.dfm"

using namespace mtk;

TCombinedMoveFrame *CombinedMoveFrame;
//---------------------------------------------------------------------------

__fastcall TCombinedMoveFrame::TCombinedMoveFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TCombinedMoveFrame::populate(Process* p)
{
	mMoveLB->Clear();

	//Populate, update frame with data from process
    mCombinedMove = dynamic_cast<CombinedLinearMove*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    //Fill out the listbox with moves
    for(int i = 0; i < mCombinedMove->getNumberOfMoves(); i++)
    {
    	LinearMove* mv = mCombinedMove->getMove(i);
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

    LinearMove* lm = new LinearMove("", NULL);

    //Add the move to the container.. this will give the move a name
    mCombinedMove->addMove(*lm);

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
		populate(mCombinedMove);
    }

}

void TCombinedMoveFrame::selectItem(LinearMove* mv)
{
	if(mv)
    {
		this->TMotorMoveProcessFrame1->populate(mv);
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
    LinearMove* mv = mCombinedMove->getMove(moveName);

    selectItem(mv);
}


