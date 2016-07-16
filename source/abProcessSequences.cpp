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

ProcessSequence* ProcessSequences::select(ProcessSequence* se)
{
	ProcessSequence* s = getFirst();
    while(s)
    {
    	if(s == se)
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

	// Load all sequences in the current fileFolder, first clear out old ones...
    clear();
	int count(0);
    StringList files = getFilesInDir(mFileFolder, mFileExtension);
    for(int i = 0; i < files.size(); i++)
    {
    	bool res = load(getFileNameNoPathNoExtension(files[i]));
        if(!res)
        {
        	Log(lError) << "Failed loading process sequence: "<< files[i];
        }
        count++;
    }
    return count;
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
        	//Setup function objects here

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
        //Create a file name that does not exist
	   	stringstream ss;
        int fileNo(0);
        do
        {
        	ss.str("");
	        fileNo++;

            ss<<"Sequence "<<fileNo;

        }while(fileExists(joinPath(mFileFolder, ss.str() + ".abp")));

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

    ProcessSequence* s = select(lbl);
    if(s)
    {
    	string fullFName = joinPath(s->getFileFolder(), s->getFileName());
        if(removeFile(fullFName))
        {
        	Log(lInfo) << "Removed process sequence file: "<<fullFName;
        }
        else
        {
			Log(lError) << "Failed removing process sequence file: "<<fullFName;
        }

        mProcessSequences.erase(mProcessSequencesIter);
		mProcessSequencesIter = mProcessSequences.begin();
        return true;
    }
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


