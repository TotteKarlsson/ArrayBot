#pragma hdrstop
#include "abProcessSequence.h"
#include "abProcess.h"
#include "mtkIniFile.h"
#include "abLinearMove.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ProcessSequence::ProcessSequence(const string& name, const string& fileExt)
:
mName(name),
mFileExtension(fileExt),
mProject(*this)
{}

ProcessSequence::~ProcessSequence()
{}

bool ProcessSequence::assignUnit(ABObject* o)
{
    Process* p = getFirst();
    while(p)
    {
    	p->assignUnit(o);
        p = getNext();
    }
    return true;
}

void ProcessSequence::clear()
{
	mProcesses.clear();
}

void ProcessSequence::init()
{
    Process* process = getFirst();
    int count = 1;
    while(process)
    {
    	process->init();
        process = getNext();
    }
}

bool ProcessSequence::read(const string& fName)
{
	return mProject.loadFromFile(fName);
}

bool ProcessSequence::isFirst(Process* p)
{
	return p == *(mProcesses.begin());
}

bool ProcessSequence::write(const string& folder)
{
	//Create XML document
    mProject.setFileFolder(folder);
	mProject.setModelFileName(mName + ".abp");
    mProject.save();
//
//	//Save to file
//    string fullFName = joinPath(folder, mName + "." + mFileExtension);
//	IniFile f(fullFName);
//
//    //Save some info about the Process Sequence
//    IniSection* genSec = f.createSection("SEQUENCE_INFO");
//    genSec->createKey("NAME", mName);
//
//    Process* process = getFirst();
//    int count = 1;
//    while(process)
//    {
//        IniSection *sec = f.createSection(process->getProcessName());
//        if(sec)
//        {
//            process->write(sec);
//        }
//        count++;
//        process = getNext();
//    }
//
//    return f.save();
}

bool ProcessSequence::add(Process* pos)
{
	//Check label
    mProcesses.push_back(pos);
    mProcessIter = mProcesses.begin();
    return true;
}

bool ProcessSequence::remove(Process* p)
{
	//Find item
    mProcesses.remove(p);
    return true;
}

bool ProcessSequence::remove(const string& lbl)
{
	//Find item with label
    return false;
}

Process* ProcessSequence::getFirst() const
{
    mProcessIter = mProcesses.begin();
    if(mProcessIter != mProcesses.end())
    {
        return (*mProcessIter);
    }
    return NULL;
}

Process* ProcessSequence::getCurrent() const
{
    if(mProcessIter != mProcesses.end())
    {
        return (*mProcessIter);
    }
    return NULL;
}

Process* ProcessSequence::getNext() const
{
    if(mProcessIter != mProcesses.end())
    {
        mProcessIter++;
        if(mProcessIter != mProcesses.end())
        {
            return (*mProcessIter);
        }
    }
    return NULL;
}

Process* ProcessSequence::getPrevious() const
{
    if(mProcessIter != mProcesses.end())
    {
        mProcessIter--;
        if(mProcessIter != mProcesses.end())
        {
            return (*mProcessIter);
        }
    }
    return NULL;
}


