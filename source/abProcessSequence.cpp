#pragma hdrstop
#include "abProcessSequence.h"
#include "abProcess.h"
#include "mtkIniFile.h"
#include "abMove.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ProcessSequence::ProcessSequence(ArrayBot& ab, const string& name, const string& fileExt)
:
mAB(ab),
mProject(*this, fileExt)
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
    	process->init(mAB);
        process = getNext();
    }
}

bool ProcessSequence::moveForward(Process* ps)
{
	//Check first if it is possible
    list<Process*>::iterator it1 = find(mProcesses.begin(), mProcesses.end(), ps);
    list<Process*>::iterator it2 = it1;
    it2++;

    if(it1 != mProcesses.end() || it2 != mProcesses.end())
    {
        swap(*it1, *it2);
        return true;
    }
    return false;
}

bool ProcessSequence::moveBack(Process* ps)
{
	//Check first if it is possible
    list<Process*>::iterator it1 = find(mProcesses.begin(), mProcesses.end(), ps);
    list<Process*>::iterator it2 = it1;
    it2--;

    if(it1 != mProcesses.begin() || it2 != mProcesses.begin())
    {
        swap(*it1, *it2);
        return true;
    }
    return false;
}

bool ProcessSequence::isFirst(Process* p)
{
	return p == *(mProcesses.begin());
}

void ProcessSequence::setProjectName(const string& name)
{
	mProject.setProjectName(name);
}

void ProcessSequence::setFileFolder(const string& f)
{
	mProject.setFileFolder(f);
}

void ProcessSequence::setFileName(const string& f)
{
	mProject.setFileName(f);
}

void ProcessSequence::setFileExtension(const string& e)
{
	mProject.setFileExtension(e);
}

string ProcessSequence::getFileFolder()
{
	return mProject.getFileFolder();
}

string ProcessSequence::getFileName()
{
	return mProject.getFileName();
}

bool ProcessSequence::read(const string& fName)
{
	if(mProject.loadFromFile(fName))
    {
    	bool res = mProject.open();
    	return res;
    }
    return false;
}

bool ProcessSequence::write(const string& folder)
{
	if(folder.size())
    {
		//Create XML document
	    mProject.setFileFolder(folder);
    }

    if(mProject.getFileName() == "")
    {
        mProject.setFileName(mProject.getProjectName() + ".abp");
    }
    return mProject.save();
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


