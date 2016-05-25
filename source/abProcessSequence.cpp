#pragma hdrstop
#include "abProcessSequence.h"
#include "abProcess.h"
#include "mtkIniFile.h"
#include "abLinearMove.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ProcessSequence::ProcessSequence()
:
mName("MoveSequence"),
mFileExtension("proc")
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

bool ProcessSequence::read(const string& fName)
{
	IniFile f(fName, true);
    int count = 0;
	IniSection* sec = f.getSection(count);
    IniKey* key;

    while(sec)
    {
    	key = sec->getKey("PROCESS_TYPE");
        if(key && key->mValue == "SPATIAL_MOVE")
        {
	    	LinearMove* p = new LinearMove(sec->mName, NULL);

            if(p->read(sec))
            {
            	add(p);
            }
            else
            {
            	Log(lError) <<"Failed reading process: "<<sec->mName;
            }
        }

        //Get next section
        sec = f.getSection(++count);
    }
    return true;
}

bool ProcessSequence::write()
{
	//Save to file
	IniFile f(mName + "." + mFileExtension);

    Process* process = getFirst();
    int count = 1;
    while(process)
    {
        IniSection *sec = f.createSection("PROCESS " + mtk::toString(count));
        if(sec)
        {
            process->write(sec);
        }
        count++;
        process = getNext();
    }

    return f.save();
}

bool ProcessSequence::add(Process* pos)
{
	//Check label
    mProcesses.push_back(pos);
    mProcessIter = mProcesses.begin();
    return true;
}

bool ProcessSequence::remove(const string& lbl)
{
	//Find item
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


