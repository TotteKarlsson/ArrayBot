#pragma hdrstop
#include "abParallell.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"
#include "abMove.h"
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
Parallell::Parallell(const string& lbl)
:
Process(lbl, NULL)
{
	mProcessType = ptParallell;
}

const string Parallell::getTypeName() const
{
	return "combinedMove";
}

void Parallell::init(ArrayBot& ab)
{
	Process::init(ab);

    //Call init for each sub move
    for(int i = 0; i < mProcesses.size(); i++)
    {
    	if(mProcesses[i])
        {
        	mProcesses[i]->init(ab);
        }
    }
}

void Parallell::clear()
{
	mProcesses.clear();
}

void Parallell::addProcess(Process* lm)
{
	if(lm && lm->getProcessName() =="")
    {
    	lm->setProcessName("Process " + mtk::toString((mProcesses.size() + 1)));
    }

    if(lm)
    {
		mProcesses.push_back(lm);
    }

}

bool Parallell::removeProcess(const string& name)
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	if(mProcesses[i]->getProcessName() == name)
        {
        	Process* lm = (mProcesses[i]);
            mProcesses.erase(mProcesses.begin() + i);
        }
    }
    return true;
}

bool Parallell::removeProcess(Process* m)
{
	return false;
}

Process* Parallell::getProcess(int i)
{
	if(i < mProcesses.size())
    {
    	return (mProcesses[i]);
    }
    return NULL;
}

Process*	Parallell::getProcess(const string& lbl)
{
	// look for item
    for(int i = 0 ; i < mProcesses.size(); i++)
    {
    	Process* mv = mProcesses[i];
        if(mv->getProcessName() == lbl)
        {
        	return mv;
        }
    }
    return NULL;
}

XMLElement* Parallell::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	Process* lm = mProcesses[i];
        lm->addToXMLDocumentAsChild(doc, docRoot);
    }

    return dynamic_cast<XMLElement*>(docRoot);
}

bool Parallell::isBeingProcessed()
{
	if(isDone())
    {
		mIsBeingProcessed = false;
        mIsProcessed = true;
       	Timestamp now;
        mEndTime = now;
    }

    return mIsBeingProcessed;
}

bool Parallell::isProcessed()
{
    if(mIsProcessed == true)
    {
    	return true;
    }

    if(isDone())
    {
        //Consider this process to be "processed"
        mIsProcessed 		= true;
        mIsBeingProcessed 	= false;
        return true;
    }

	return false;
}

bool Parallell::isCommandPending()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
//    	if(mProcesses[i]->isMotorCommandPending())
//        {
//        	return true;
//        }
    }

    return false;
}

bool Parallell::areMotorsActive()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
//    	if(mProcesses[i]->isMotorActive())
//        {
//        	return true;
//        }
    }

    return false;
}

bool Parallell::start()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	mProcesses[i]->start();
        Log(lInfo) << "Started Process \"" << mProcesses[i]->getProcessName()<<"\"";
    }

	return Process::start();
}

bool Parallell::stop()
{
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	mProcesses[i]->stop();
    }

	return Process::stop();
}

bool Parallell::isDone()
{
	//Check all subprocesses here
	for(int i = 0; i < mProcesses.size(); i++)
    {
    	if(!mProcesses[i]->isDone())
        {
        	return false;
        }
    }

    return true;
}

bool Parallell::undo()
{
	return false;
}
