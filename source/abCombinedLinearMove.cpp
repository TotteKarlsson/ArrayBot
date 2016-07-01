#pragma hdrstop
#include "abCombinedLinearMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
#include "mtkLogger.h"

using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
CombinedLinearMove::CombinedLinearMove(const string& lbl)
:
Process(lbl)
{
	mProcessType = ptCombinedLinearMove;
}

void CombinedLinearMove::addMove(LinearMove& lm)
{
	if(lm.getProcessName() =="")
    {
    	lm.setProcessName("Move " + mtk::toString((mMoves.size() + 1)));
    }
	mMoves.push_back(lm);
}

bool CombinedLinearMove::removeMove(const string& name)
{
	for(int i = 0; i < mMoves.size(); i++)
    {
    	if(mMoves[i].getProcessName() == name)
        {
        	LinearMove* lm = &(mMoves[i]);
            mMoves.erase(mMoves.begin() + i);
        }
    }
    return true;
}

bool CombinedLinearMove::removeMove(LinearMove* m)
{
	return false;
}

LinearMove* CombinedLinearMove::getMove(int i)
{
	if(i < mMoves.size())
    {
    	return &(mMoves[i]);
    }
    return NULL;
}

LinearMove*	CombinedLinearMove::getMove(const string& lbl)
{
	// look for item
    for(int i = 0 ; i < mMoves.size(); i++)
    {
    	LinearMove& mv = mMoves[i];
        if(mv.getProcessName() == lbl)
        {
        	return &mv;
        }
    }
    return NULL;
}

XMLElement* CombinedLinearMove::addToXMLDocumentAsChildProcess(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    XMLElement* processNode  = doc.NewElement("processes");
    XMLNode*    rootNode = doc.InsertFirstChild(processNode);

    //Attributes
    //processNode->SetAttribute("id", getID().toString().c_str());

	for(int i = 0; i < mMoves.size(); i++)
    {
    	LinearMove& lm = mMoves[i];
        //lm.addToXMLDocument(doc, rootNode);
        lm.addToXMLDocumentAsChild(doc, rootNode);
    }

    processNode->InsertEndChild(rootNode);
    docRoot->InsertEndChild(processNode);

    return processNode;
}

bool CombinedLinearMove::isBeingProcessed()
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

bool CombinedLinearMove::isProcessed()
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
    else
    {
        return false;
    }

	return false;
}

bool CombinedLinearMove::isDone()
{
	//Check all subprocesses here
    return false;
}

bool CombinedLinearMove::isCommandPending()
{
	return false;
}

bool CombinedLinearMove::areMotorsActive()
{
    return false;
}

bool CombinedLinearMove::write(IniSection* sec)
{
    return true;
}

bool CombinedLinearMove::read(IniSection* sec)
{
    return true;
}

bool CombinedLinearMove::start()
{
	Process::start();
    return false;
}

bool CombinedLinearMove::stop()
{
	Process::stop();

    return false;
}

bool CombinedLinearMove::undo()
{
	return false;
}
