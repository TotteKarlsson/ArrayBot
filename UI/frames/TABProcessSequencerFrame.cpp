#include <vcl.h>
#pragma hdrstop
#include "TABProcessSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "abCombinedLinearMove.h"
#include "abArrayBot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TMotorMoveProcessFrame"
#pragma resource "*.dfm"
TABProcessSequencerFrame *ABProcessSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

int TABProcessSequencerFrame::mFrameNr = 0;
__fastcall TABProcessSequencerFrame::TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mAB(ab),
	mCoverSlipUnit(mAB.getCoverSlipUnit()),
	mWhiskerUnit(mAB.getWhiskerUnit()),
    mProcessSequencer(appFolder)
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + mtk::toString(++mFrameNr));

    retrieveMotorsFromUnit(mWhiskerUnit);
	retrieveMotorsFromUnit(mCoverSlipUnit);

    GroupBox1->Caption = "ArrayBot Process Sequencer";
    mProcessFileExtension = "abp";
    refreshSequencesCB();
}

void TABProcessSequencerFrame::retrieveMotorsFromUnit(XYZUnit& unit)
{
	//Fill out sequencer frame
//	if(unit.getXMotor())
//    {
//    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, unit.getXMotor()->getName().c_str(), (TObject*) unit.getXMotor() );
//    }
//
//	if(unit.getYMotor())
//    {
//    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, unit.getYMotor()->getName().c_str(), (TObject*) unit.getYMotor() );
//    }
//
//	if(unit.getZMotor())
//    {
//    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, unit.getZMotor()->getName().c_str(), (TObject*) unit.getZMotor() );
//    }
//
//	if(unit.getAngleMotor())
//    {
//    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, unit.getAngleMotor()->getName().c_str(), (TObject*) unit.getAngleMotor() );
//    }
}

void TABProcessSequencerFrame::init()
{
    if(mSequencesCB->Items->Count)
    {
        mSequencesCB->ItemIndex = 0;
		mSequencesCBChange(NULL);
    }
}

void __fastcall TABProcessSequencerFrame::mDeleteSequenceBtnClick(TObject *Sender)
{
	//Check selected sequence and delete it
    int idx = mSequencesCB->ItemIndex;
    if(idx > -1)
    {
    	string seqName = stdstr(mSequencesCB->Items->Strings[idx]);
		mSequencesCB->DeleteSelected();
		mProcessesLB->Clear();
        removeFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", seqName + "." + mProcessFileExtension));
    }
}
//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mAddSeqBtnClick(TObject *Sender)
{
    //Save current sequence, if any
    mProcessSequencer.saveCurrent();

	ProcessSequence* s = new ProcessSequence();
    mProcessSequencer.addSequence(s);

	mSequencesCB->Items->Add(vclstr(s->getName()));
	mSequencesCB->ItemIndex = mSequencesCB->Items->IndexOf(vclstr(s->getName()));
	mSequencesCBChange(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::refreshSequencesCB()
{
    //Get all move files in folder
    StringList files = getFilesInDir(gAppDataFolder, mProcessFileExtension);
    mSequencesCB->Clear();
    for(int i = 0; i < files.count() ; i++)
    {
    	mSequencesCB->Items->Add(getFileNameNoPathNoExtension(files[i]).c_str());
    }
    mProcessesLB->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequencesCBChange(TObject *Sender)
{
	//Load the sequence
    int index = mSequencesCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }

    //Save current sequence
    mProcessSequencer.saveCurrent();

    mProcessesLB->Clear();
    string sName(stdstr(mSequencesCB->Items->Strings[index]));

	if(mProcessSequencer.load(sName))
    {
    	//Fill out listbox
		ProcessSequence* seq = mProcessSequencer.getCurrentSequence();
        if(!seq)
        {
        	return;
        }

        Process* p = seq->getFirst();
        while(p)
        {
    		mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
            p = seq->getNext();
        }

        //Select the first move in the sequence
        if(mProcessesLB->Count)
        {
	        mProcessesLB->ItemIndex = 0;
        }
        mProcessesLBClick(NULL);
    }
    else
    {
        MessageDlg("Failed loading that sequence", mtError, TMsgDlgButtons() << mbOK, 0);
    }

    mProcessSequencer.assignUnit(&mAB);
}

void __fastcall TABProcessSequencerFrame::mStartBtnClick(TObject *Sender)
{
    if(mStartBtn->Caption == "Start")
    {
        mWhiskerUnit.disableJSAxes();
        mCoverSlipUnit.disableJSAxes();

    	mProcessSequencer.start(true);
		mSequenceStatusTimer->Enabled = true;
    }
    else
    {
    	mProcessSequencer.stop();
	}
}
//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSaveSequenceBtnClick(TObject *Sender)
{
	saveSequence();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mProcessesLBClick(TObject *Sender)
{
	//Retrieve current process and populate UI
    int i = mProcessesLB->ItemIndex;
    if(i == -1)
    {
    	return;
    }

    Process* p = (Process*) mProcessesLB->Items->Objects[i];

    if(p)
    {
//    	mMovePosE->setValue(move->getPosition().x());
//        mMaxVelE->setValue(move->getMaxVelocity());
//        mAccE->setValue(move->getAcceleration());
//        mPostDwellTimeE->setValue(move->getPostDwellTime());
//        mPreDwellTimeE->setValue(move->getPreDwellTime());
//
//        APTMotor* mtr = dynamic_cast<APTMotor*>(move->getUnit());
//        if(!mtr)
//        {
//        	//Look for motor in the Checkbox
//            string unitLbl = move->getMotorName();
//			int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
//            if(idx != -1)
//            {
//            	move->assignUnit( (APTMotor*) MotorsCB->Items->Objects[idx] );
//				MotorsCB->ItemIndex = idx;
//            }
//        }
//        else
//        {
//        	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
//			MotorsCB->ItemIndex = idx;
//        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::moveParEdit(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    int i = mProcessesLB->ItemIndex;
    if(i == -1 || Key != vkReturn)
    {
    	return;
    }

//    LinearMove* move = (LinearMove*) mProcessesLB->Items->Objects[i];
//	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);
//
//    ab::Position p(move->getPositionName(), mMovePosE->getValue(),0,0);
//    move->setPosition(p);
//    move->setMaxVelocity(mMaxVelE->getValue());
//    move->setAcceleration(mAccE->getValue());
//    move->setPostDwellTime(mPostDwellTimeE->getValue());
//    move->setPreDwellTime(mPreDwellTimeE->getValue());
//
    saveSequence();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::MotorsCBChange(TObject *Sender)
{
    int i = mProcessesLB->ItemIndex;
    if(i == -1)
    {
        return;
    }

//	//Check if a motor is selected
//    ABObject* obj = (ABObject*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
//
//    APTMotor* 			motor = dynamic_cast<APTMotor*>(obj);
//    if(motor)
//    {
//    	mMovePosE->Enabled = true;
//        mAccE->Enabled = true;
//
//        LinearMove* move = (LinearMove*) mProcessesLB->Items->Objects[i];
//        move->assignUnit(motor);
//    }
//    else
//    {
//    	mMovePosE->Enabled 	= false;
//        mAccE->Enabled 		= false;
//    }
	saveSequence();
}

void TABProcessSequencerFrame::saveSequence()
{
	//Save Current Sequence
    int indx = mSequencesCB->ItemIndex;
    string seqName (stdstr(mSequencesCB->Items->Strings[indx]));

//    mProcessSequencer.getSequence().setName(seqName);
//	mProcessSequencer.getSequence().setFileExtension(mProcessFileExtension);
    mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequenceTimerTimer(TObject *Sender)
{
	if(mProcessSequencer.isRunning())
    {
    	mStartBtn->Caption = "Stop";
        mStatusLbl->Caption = "Working on: " + vclstr(mProcessSequencer.getCurrentProcessName());
    }
    else
    {
		mSequenceStatusTimer->Enabled = false;
        mWhiskerUnit.enableJSAxes();
        mCoverSlipUnit.enableJSAxes();

    	mStartBtn->Caption = "Start";
	  	mStatusLbl->Caption = "Idle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::addProcessAExecute(TObject *Sender)
{
	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
	if(!s)
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

    int nr  = s->getNumberOfProcesses() + 1;

	//Create and add a process to the sequence
	Process *p = new CombinedLinearMove("Process " + mtk::toString(nr));

   	s->add(p);

    //Update LB
    mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::removeProcessAExecute(TObject *Sender)
{
	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
	if(!s)
    {
    	Log(lError) << "Tried to remove process from NULL sequence";
    	return;
    }

    int i = mProcessesLB->ItemIndex;


    Process* p = (Process*) mProcessesLB->Items->Objects[i];


    s->remove(p);
    mProcessesLB->DeleteSelected();

    if(mProcessesLB->Count > -1)
    {
		mProcessesLB->ItemIndex = 0;
		mProcessesLBClick(NULL);
    }
}


