#include <vcl.h>
#pragma hdrstop
#include "TMoveSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TMoveSequencerFrame *MoveSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

__fastcall TMoveSequencerFrame::TMoveSequencerFrame(XYZUnit* u, TComponent* Owner)
	: TFrame(Owner),
    mXYZUnit(u),
    mMoveSequencer()
{
	if(!mXYZUnit)
    {
    	return;
    }

    //Fill out sequencer frame
	if(mXYZUnit->getXMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit->getXMotor()->getName().c_str(), (TObject*) mXYZUnit->getXMotor() );
    }

	if(mXYZUnit->getYMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit->getYMotor()->getName().c_str(), (TObject*) mXYZUnit->getYMotor() );
    }

	if(mXYZUnit->getZMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit->getZMotor()->getName().c_str(), (TObject*) mXYZUnit->getZMotor() );
    }

    GroupBox1->Caption = GroupBox1->Caption + ": " + mXYZUnit->getName().c_str();
    mMovesFileExtension = mXYZUnit->getName();
    refreshSequencesCB();
}

void __fastcall TMoveSequencerFrame::mAddMoveBtnClick(TObject *Sender)
{
	//Create and add a move to the sequencer
    ab::Position pos("", 0.0, 0.0, 0.0);
	if(MotorsCB->ItemIndex == -1 || MotorsCB->Items->Objects[MotorsCB->ItemIndex] == NULL)
    {
    	Log(lError) << "No motor is selected. can't create move";
        MessageDlg("Select a Motor before adding a move", mtInformation, TMsgDlgButtons() << mbOK, 0);
    	return;
    }

    APTMotor* motor = (APTMotor*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
    if(!motor)
    {
    	Log(lError) << "Can't happen...";
    	return;
    }

	LinearMove *move = new LinearMove("", motor, mtAbsolute, pos);

    mMoveSequencer.addProcess(move);

    //Update LB
    if(move->getPositionName() == "")
    {
    	//Make move name unique
    	int i = 1;
    	string lbl = "MOVE " + mtk::toString(mMovesLB->Count + i);
        do
        {
            lbl = "MOVE " + mtk::toString(mMovesLB->Count + i);
            i++;
        }while(mMovesLB->Items->IndexOf(vclstr(lbl)) != -1);

        move->setPositionName(lbl);
	    move->setProcessName(lbl);
    }
    mMovesLB->Items->AddObject(move->getPositionName().c_str(), (TObject*) move);
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mDeleteMoveBtnClick(TObject *Sender)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
    	return;
    }

    LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];
	mMovesLB->DeleteSelected();

    if(mMovesLB->Count > -1)
    {
		mMovesLB->ItemIndex = 0;
		mMovesLBClick(NULL);
    }

    if(mMoveSequencer.removeProcess(move))
    {
    	Log(lInfo) << "Removed process: " << move->getProcessName();
        delete move;
    }
    else
    {
    	Log(lError) << "Failed removing process: " << move->getProcessName();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mDeleteSequenceBtnClick(TObject *Sender)

{
	//Check selected sequence and delete it
    int idx = mSequencesCB->ItemIndex;
    if(idx > -1)
    {
    	string seqName = stdstr(mSequencesCB->Items->Strings[idx]);
		mSequencesCB->DeleteSelected();
		mMovesLB->Clear();
        removeFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", seqName + "." + mMovesFileExtension));
    }
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mAddSeqBtnClick(TObject *Sender)
{
	//Create a new move file and sequence

	stringstream fName;
    int i = 1;
    do
    {
        fName.str("");
    	fName << "Sequence "<<i++<<"." << mMovesFileExtension;

    }while(fileExists(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", fName.str())));

    if(!createFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", fName.str())))
    {
    	MessageDlg("Failed creating move file!", mtError, TMsgDlgButtons() << mbOK, 0);
    }

    refreshSequencesCB();
	mSequencesCB->ItemIndex = mSequencesCB->Items->IndexOf(getFileNameNoExtension(fName.str()).c_str());
}

//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::refreshSequencesCB()
{
    //Load moves
    //Get all move files in folder
    StringList files = getFilesInDir(gAppDataFolder, mMovesFileExtension);
    mSequencesCB->Clear();
    for(int i = 0; i < files.count() ; i++)
    {
    	mSequencesCB->Items->Add(getFileNameNoPathNoExtension(files[i]).c_str());
    }
    mMovesLB->Clear();
}

void __fastcall TMoveSequencerFrame::mStartBtnClick(TObject *Sender)
{
	TButton* btn = (TButton*)Sender;
    if(btn->Caption == "Start")
    {
    	mMoveSequencer.start(true);
		mSequenceTimer->Enabled = true;
    }
    else
    {
    	mMoveSequencer.stop();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mSaveSequenceBtnClick(TObject *Sender)
{
	//Save Current Sequence
    int indx = mSequencesCB->ItemIndex;
    string seqName (stdstr(mSequencesCB->Items->Strings[indx]));
    mMoveSequencer.getSequence().setName(seqName);
	mMoveSequencer.getSequence().setFileExtension(mMovesFileExtension);
    mMoveSequencer.save(gAppDataFolder);
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mSequencesCBChange(TObject *Sender)
{
	//Load the sequence
    int index = mSequencesCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }

    mMovesLB->Clear();
    string fName(stdstr(mSequencesCB->Items->Strings[index]) + "." + mMovesFileExtension);

	if(mMoveSequencer.load(joinPath(gAppDataFolder,fName)))
    {
    	//Fill out listbox
		ProcessSequence& seq = mMoveSequencer.getSequence();
        Process* move = seq.getFirst();
        while(move)
        {
    		mMovesLB->Items->AddObject(move->getProcessName().c_str(), (TObject*) move);
            move = seq.getNext();
        }
    }

    mMoveSequencer.assignUnit(mXYZUnit);
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mMovesLBClick(TObject *Sender)
{
	//Retrieve current move and populate UI
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
    	return;
    }

    LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];

    if(move)
    {
    	mMovePosE->setValue(move->getPosition().x());
    	mMovePositionLabel->setValue(move->getPositionName());
        mMaxVelE->setValue(move->getMaxVelocity());
        mAccE->setValue(move->getAcceleration());
        mDwellTimeE->setValue(move->getDwellTime());

        APTMotor* mtr = dynamic_cast<APTMotor*>(move->getUnit());
        if(!mtr)
        {
        	//Look for motor in the Checkbox
            string unitLbl = move->getMotorName();
			int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
            if(idx != -1)
            {
            	move->assignUnit( (APTMotor*) MotorsCB->Items->Objects[idx] );
				MotorsCB->ItemIndex = idx;
            }
        }
        else
        {
        	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
			MotorsCB->ItemIndex = idx;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::moveParEdit(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1 || Key != vkReturn)
    {
    	return;
    }

    LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];
	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);

//    if(e == mMovePosE)
    {
    	ab::Position p(move->getPositionName(), mMovePosE->getValue(),0,0);
		move->setPosition(p);
    }

//    if(e == mMaxVelE)
    {
		move->setMaxVelocity(mMaxVelE->getValue());
    }

//    if(e == mAccE)
    {
		move->setAcceleration(mAccE->getValue());
    }

//    if(e == mDwellTimeE)
    {
		move->setDwellTime(mDwellTimeE->getValue());
    }

	{
    	move->setPositionName(mMovePositionLabel->getValue().c_str());
    }
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::MotorsCBChange(TObject *Sender)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
        return;
    }

	//Check if a motor is selected

    APTMotor* motor = (APTMotor*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];

    if(motor)
    {
    	mMovePosE->Enabled = true;
        mAccE->Enabled = true;

        LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];
        move->assignUnit(motor);
    }
    else
    {
    	mMovePosE->Enabled = false;
        mAccE->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMoveSequencerFrame::mSequenceTimerTimer(TObject *Sender)
{
	if(mMoveSequencer.isRunning())
    {
    	mStartBtn->Caption = "Stop";
    }
    else
    {
    	mStartBtn->Caption = "Start";
    }
}
//---------------------------------------------------------------------------
