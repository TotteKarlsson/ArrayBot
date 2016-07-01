#include <vcl.h>
#pragma hdrstop
#include "TXYZProcessSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "abMove.h"
#include "abArrayBot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TXYZProcessSequencerFrame *XYZProcessSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

int TXYZProcessSequencerFrame::mFrameNr = 0;
__fastcall TXYZProcessSequencerFrame::TXYZProcessSequencerFrame(XYZUnit* u, ArrayBot* ab, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mXYZUnit(u),
    mAB(ab),
    mProcessSequencer(appFolder)
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + mtk::toString(++mFrameNr));

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

	if(mXYZUnit->getAngleMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit->getAngleMotor()->getName().c_str(), (TObject*) mXYZUnit->getAngleMotor() );
    }

    GroupBox1->Caption = GroupBox1->Caption + ": " + mXYZUnit->getName().c_str();
    mMovesFileExtension = mXYZUnit->getName();
    refreshSequencesCB();
}

void TXYZProcessSequencerFrame::init()
{
    if(mSequencesCB->Items->Count)
    {
        mSequencesCB->ItemIndex = 0;
		mSequencesCBChange(NULL);
    }
}

void __fastcall TXYZProcessSequencerFrame::mAddMoveBtnClick(TObject *Sender)
{
	if(!mProcessSequencer.getCurrentSequence())
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

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

	Move *move = new Move("", mtAbsolute, pos);

    mProcessSequencer.getCurrentSequence()->add(move);

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
void __fastcall TXYZProcessSequencerFrame::mDeleteMoveBtnClick(TObject *Sender)
{
//    int i = mMovesLB->ItemIndex;
//    if(i == -1)
//    {
//    	return;
//    }
//
//    Move* move = (Move*) mMovesLB->Items->Objects[i];
//	mMovesLB->DeleteSelected();
//
//    if(mMovesLB->Count > -1)
//    {
//		mMovesLB->ItemIndex = 0;
//		mMovesLBClick(NULL);
//    }
//
//    if(mProcessSequencer.removeProcess(move))
//    {
//    	Log(lInfo) << "Removed process: " << move->getProcessName();
//        delete move;
//    }
//    else
//    {
//    	Log(lError) << "Failed removing process: " << move->getProcessName();
//    }
}
//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::mDeleteSequenceBtnClick(TObject *Sender)

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
void __fastcall TXYZProcessSequencerFrame::mAddSeqBtnClick(TObject *Sender)
{
	//Create a new move file and sequence
	stringstream fName;
    int i = 1;
    do
    {
        fName.str("");
    	fName << "Sequence "<<i++<<"." << mMovesFileExtension;

    }
    while(fileExists(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", fName.str())));

    if(!createFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", fName.str())))
    {
    	MessageDlg("Failed creating move file!", mtError, TMsgDlgButtons() << mbOK, 0);
    }

    refreshSequencesCB();
	mSequencesCB->ItemIndex = mSequencesCB->Items->IndexOf(getFileNameNoExtension(fName.str()).c_str());
	mSequencesCBChange(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::refreshSequencesCB()
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

void __fastcall TXYZProcessSequencerFrame::mStartBtnClick(TObject *Sender)
{
    if(mStartBtn->Caption == "Start")
    {
    	if(mAB)
        {
	        if(mXYZUnit)
            {
            	mXYZUnit->disableJSAxes();
            }
        }

    	mProcessSequencer.start(true);
		mSequenceStatusTimer->Enabled = true;
    }
    else
    {
    	mProcessSequencer.stop();
	}
}
//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::mSaveSequenceBtnClick(TObject *Sender)
{
	saveSequence();
}
//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::mSequencesCBChange(TObject *Sender)
{
//	//Load the sequence
//    int index = mSequencesCB->ItemIndex;
//    if(index == -1)
//    {
//    	return;
//    }
//
//    mMovesLB->Clear();
//    string fName(stdstr(mSequencesCB->Items->Strings[index]) + "." + mMovesFileExtension);
//
//	if(mProcessSequencer.load(joinPath(gAppDataFolder,fName)))
//    {
//    	//Fill out listbox
//		ProcessSequence* seq = mProcessSequencer.getSequences().getSequence(;
//        if(!seq)
//        {
//        	return;
//        }
//
//        Process* move = seq->getFirst();
//        while(move)
//        {
//    		mMovesLB->Items->AddObject(move->getProcessName().c_str(), (TObject*) move);
//            move = seq->getNext();
//        }
//
//        //Select the first move in the sequence
//        if(mMovesLB->Count)
//        {
//	        mMovesLB->ItemIndex = 0;
//        }
//        mMovesLBClick(NULL);
//    }
//
//    mProcessSequencer.assignUnit(mXYZUnit);
}
//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::mMovesLBClick(TObject *Sender)
{
	//Retrieve current move and populate UI
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
    	return;
    }

    Move* move = (Move*) mMovesLB->Items->Objects[i];

    if(move)
    {
    	mMovePosE->setValue(move->getPosition().x());
        mMaxVelE->setValue(move->getMaxVelocity());
        mAccE->setValue(move->getAcceleration());
        mPostDwellTimeE->setValue(move->getPostDwellTime());
        mPreDwellTimeE->setValue(move->getPreDwellTime());

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
void __fastcall TXYZProcessSequencerFrame::moveParEdit(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1 || Key != vkReturn)
    {
    	return;
    }

    Move* move = (Move*) mMovesLB->Items->Objects[i];
	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);

    ab::Position p(move->getPositionName(), mMovePosE->getValue(),0,0);
    move->setPosition(p);
    move->setMaxVelocity(mMaxVelE->getValue());
    move->setAcceleration(mAccE->getValue());
    move->setPostDwellTime(mPostDwellTimeE->getValue());
    move->setPreDwellTime(mPreDwellTimeE->getValue());

    saveSequence();
}
//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::MotorsCBChange(TObject *Sender)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
        return;
    }

	//Check if a motor is selected
    ABObject* obj = (ABObject*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];

    APTMotor* 			motor = dynamic_cast<APTMotor*>(obj);
    if(motor)
    {
    	mMovePosE->Enabled = true;
        mAccE->Enabled = true;

        Move* move = (Move*) mMovesLB->Items->Objects[i];
        move->assignUnit(motor);
    }
    else
    {
    	mMovePosE->Enabled 	= false;
        mAccE->Enabled 		= false;
    }
	saveSequence();
}

void TXYZProcessSequencerFrame::saveSequence()
{
	//Save Current Sequence
    int indx = mSequencesCB->ItemIndex;
    string seqName (stdstr(mSequencesCB->Items->Strings[indx]));
//    mProcessSequencer.getSequence().setName(seqName);
//	mProcessSequencer.getSequence().setFileExtension(mMovesFileExtension);
//    mProcessSequencer.saveCurrent(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot"));
}

//---------------------------------------------------------------------------
void __fastcall TXYZProcessSequencerFrame::mSequenceTimerTimer(TObject *Sender)
{
	if(mProcessSequencer.isRunning())
    {
    	mStartBtn->Caption = "Stop";
        mStatusLbl->Caption = "Working on: " + vclstr(mProcessSequencer.getCurrentProcessName());
    }
    else
    {
		mSequenceStatusTimer->Enabled = false;
    	if(mAB)
        {
	        if(mXYZUnit)
            {
            	mXYZUnit->enableJSAxes();
            }
        }

    	mStartBtn->Caption = "Start";
	  	mStatusLbl->Caption = "Idle";
    }
}

