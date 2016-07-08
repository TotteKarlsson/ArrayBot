#pragma hdrstop
#include "abCombinedMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"
#include "abMove.h"
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
CombinedMove::CombinedMove(const string& lbl)
:
Process(lbl, ptCombinedMove)
{
	mProcessType = ptCombinedMove;
}

void CombinedMove::clear()
{
	mMoves.clear();
}

void CombinedMove::addMove(Move* lm)
{
	if(lm && lm->getProcessName() =="")
    {
    	lm->setProcessName("Move " + mtk::toString((mMoves.size() + 1)));
    }

    if(lm)
    {
		mMoves.push_back(lm);
    }

}

bool CombinedMove::removeMove(const string& name)
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	if(mMoves[i]->getProcessName() == name)
        {
        	Move* lm = (mMoves[i]);
            mMoves.erase(mMoves.begin() + i);
        }
    }
    return true;
}

bool CombinedMove::removeMove(Move* m)
{
	return false;
}

Move* CombinedMove::getMove(int i)
{
	if(i < mMoves.size())
    {
    	return (mMoves[i]);
    }
    return NULL;
}

Move*	CombinedMove::getMove(const string& lbl)
{
	// look for item
    for(int i = 0 ; i < mMoves.size(); i++)
    {
    	Move* mv = mMoves[i];
        if(mv->getProcessName() == lbl)
        {
        	return mv;
        }
    }
    return NULL;
}

XMLElement* CombinedMove::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  = doc.NewElement("processes");
    XMLNode*    rootNode = doc.InsertFirstChild(processNode);

    //Attributes
    //processNode->SetAttribute("id", getID().toString().c_str());

	for(int i = 0; i < mMoves.size(); i++)
    {
    	Move* lm = mMoves[i];
        lm->addToXMLDocumentAsChild(doc, rootNode);
    }

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

bool CombinedMove::isBeingProcessed()
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

bool CombinedMove::isProcessed()
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

bool CombinedMove::isCommandPending()
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	if(mMoves[i]->isMotorCommandPending())
        {
        	return true;
        }
    }

    return false;
}

bool CombinedMove::areMotorsActive()
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	if(mMoves[i]->isMotorActive())
        {
        	return true;
        }
    }

    return false;
}

bool CombinedMove::start()
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	mMoves[i]->start();
        Log(lInfo) << "Started MoveProcess \"" << mMoves[i]->getProcessName()<<"\"";
    }

	return Process::start();
}

bool CombinedMove::stop()
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	mMoves[i]->stop();
    }

	return Process::stop();
}

bool CombinedMove::isDone()
{
	//Check all subprocesses here
	for(int i = 0; i < mMoves.size(); i++)
    {
    	if(!mMoves[i]->isDone())
        {
        	return false;
        }
    }

    return true;
}

bool CombinedMove::undo()
{
	return false;
}
