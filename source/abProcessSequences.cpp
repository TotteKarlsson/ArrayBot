#pragma hdrstop
#include "abProcessSequences.h"
#include "mtkFileUtils.h"
#include <sstream>
//---------------------------------------------------------------------------
using namespace mtk;
using namespace std;


ProcessSequences::ProcessSequences(const string& fileFolder)
:
mFileFolder(fileFolder)
{}

ProcessSequences::~ProcessSequences()
{}

bool ProcessSequences::clear()
{
	//TODO: Do proper de allocation later on
	mProcessSequences.clear();
    mProcessSequencesIter = mProcessSequences.begin();
    return true;
}

bool ProcessSequences::setFileFolder(const string& fileFolder)
{
	mFileFolder = fileFolder;
    return (folderExists(mFileFolder)) ? true : false;
}

string  ProcessSequences::getFileFolder()
{
	return mFileFolder;
}

bool ProcessSequences::load(const string& sName)
{
	if(fileExists(joinPath(mFileFolder, sName + ".abp")))
    {
    	ProcessSequence* s = new ProcessSequence();
        if(s->read(joinPath(mFileFolder, sName + ".abp")))
        {
        	s->setName(sName);
        	return add(s);
        }
    }
	return false;
}

bool ProcessSequences::saveCurrent()
{
	return false;
}

string ProcessSequences::getCurrentSequenceName()
{
	return (getCurrent()) ? getCurrent()->getName() : string("");
}

bool ProcessSequences::add(ProcessSequence* s)
{
	//Check name
    if(s->getName() == "")
    {
    	stringstream ss;
        ss<<"Sequence "<<countFiles(mFileFolder, "*.abp") + 1;
    	s->setName(ss.str());
        s->write(mFileFolder);
    }

    mProcessSequences.push_back(s);
    mProcessSequencesIter = mProcessSequences.end();
    mProcessSequencesIter--;
    return true;
}

bool ProcessSequences::remove(const string& lbl)
{
	//Find item
    return false;
}

ProcessSequence* ProcessSequences::getFirst() const
{
    mProcessSequencesIter = mProcessSequences.begin();
    if(mProcessSequencesIter != mProcessSequences.end())
    {
        return (*mProcessSequencesIter);
    }
    return NULL;
}

ProcessSequence* ProcessSequences::getCurrent() const
{
    if(mProcessSequencesIter != mProcessSequences.end())
    {
        return (*mProcessSequencesIter);
    }
    return NULL;
}

ProcessSequence* ProcessSequences::getNext() const
{
    if(mProcessSequencesIter != mProcessSequences.end())
    {
        mProcessSequencesIter++;
        if(mProcessSequencesIter != mProcessSequences.end())
        {
            return (*mProcessSequencesIter);
        }
    }
    return NULL;
}

ProcessSequence* ProcessSequences::getPrevious() const
{
    if(mProcessSequencesIter != mProcessSequences.end())
    {
        mProcessSequencesIter--;
        if(mProcessSequencesIter != mProcessSequences.end())
        {
            return (*mProcessSequencesIter);
        }
    }
    return NULL;
}


