#pragma hdrstop
#include "abProcessSequences.h"
#include "mtkFileUtils.h"
#include <sstream>
#include "mtkUtils.h"
#include "mtkLogger.h"

//---------------------------------------------------------------------------
using namespace mtk;
using namespace std;

ProcessSequences::ProcessSequences(const string& fileFolder, const string& fileExtension, ArrayBot& ab)
:
mAB(ab),
mProcessSequencesIter(mProcessSequences.begin()),
mFileFolder(fileFolder),
mFileExtension(fileExtension)
{}

ProcessSequences::~ProcessSequences()
{}

ProcessSequence* ProcessSequences::select(const string& sName)
{
	ProcessSequence* s = getFirst();
    while(s)
    {
    	if(s->getName() == sName)
        {
        	return s;
        }
        s = getNext();
    }
    return NULL;
}

int	ProcessSequences::loadAll(const string& fileFolder)
{
    if(fileFolder.size() > 0)
    {
    	mFileFolder = fileFolder;
    }

	// Load all seqeunces in the current fileFolder, first clear out old ones...
    clear();
    StringList files = getFilesInDir(mFileFolder, mFileExtension);
    for(int i = 0; i < files.size(); i++)
    {
    	bool res = load(getFileNameNoPathNoExtension(files[i]));
        if(!res)
        {
        	Log(lError) << "Failed loading process sequence: "<< files[i];
        }
    }
}

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

bool ProcessSequences::load(const string& fName)
{
	if(fileExists(joinPath(mFileFolder, fName + ".abp")))
    {
    	ProcessSequence* s = new ProcessSequence(mAB);
        if(s->read(joinPath(mFileFolder, fName + ".abp")))
        {
        	return add(s);
        }
    }
	return false;
}

bool ProcessSequences::saveCurrent()
{
	if(getCurrent())
    {
		return getCurrent()->write(mFileFolder);
    }
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
    	s->setProjectName(ss.str());
		s->setFileName(ss.str() + ".abp");
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


