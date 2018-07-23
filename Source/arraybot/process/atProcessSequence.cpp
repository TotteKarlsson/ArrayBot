#pragma hdrstop
#include "atProcessSequence.h"
#include "core/atProcess.h"
#include "dslIniFile.h"
#include "dslLogger.h"
#include <algorithm>
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;

namespace at
{
    ProcessSequence::ProcessSequence(ArrayBot& ab, ArrayCamClient& ac, const string& sequenceName, const string& fileExt)
    :
    mAB(ab),
    mProject(*this, ac, sequenceName),
    mCategory("General"),
    mOrder(0)
    {
    	mProcessIter = mProcesses.begin();
    }

    ProcessSequence::~ProcessSequence()
    {}

    bool ProcessSequence::assignSubject(ATObject* o)
    {
        Process* p = getFirst();
        while(p)
        {
        	p->assignSubject(o);
            p = getNext();
        }
        return true;
    }

    string ProcessSequence::getName()
    {
    	return mProject.getProjectName();
    }

    void ProcessSequence::clear()
    {
    	mProcesses.clear();
    }

    //Loop trough each process and "init" it.
    void ProcessSequence::init()
    {
        Process* process = getFirst();
        int count = 1;
        while(process)
        {
        	process->init(mAB);
            process = getNext();
        }

        //Initialize process iterator to first process..
        getFirst();
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

    string ProcessSequence::getCategory()
    {
    	return mCategory;
    }

    void ProcessSequence::setCategory(const string& c)
    {
    	mCategory = c;
    }

    int ProcessSequence::getOrder()
    {
    	return mOrder;
    }

    void ProcessSequence::setOrder(int o)
    {
    	mOrder = o;
    }

    bool ProcessSequence::getUseProcessController()
    {
    	return mUseProcessController;
    }

    void ProcessSequence::setUseProcessController(bool o)
    {
    	mUseProcessController = o;
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

    bool ProcessSequence::selectProcess(Process* p)
    {
    	Process* test = getFirst();
        while(test)
        {
        	if(test == p)
            {
            	return true;
            }
            test = getNext();
        }
        return false;
    }

    Process* ProcessSequence::getProcessWithName(const string& name)
    {
        list<Process*>::iterator  iter;
        iter = mProcesses.begin();
    	Process* test = *(iter);
        while(test)
        {
        	if(test && test->getProcessName() == name)
            {
            	return test;
            }
            test = *(iter++);
        }
        return NULL;
    }

    bool ProcessSequence::add(Process* p)
    {
    	//Check label
        p->assignProcessSequence(this);
        mProcesses.push_back(p);
        mProcessIter = mProcesses.begin();
        return true;
    }

    bool ProcessSequence::remove(Process* p)
    {
    	//Find item
        p->assignProcessSequence(NULL);
        mProcesses.remove(p);
        return true;
    }

    bool ProcessSequence::remove(const string& lbl)
    {
    	//Find item with label
        return false;
    }

    Process* ProcessSequence::peekNext()
    {
    	list<Process*>::iterator test = mProcessIter;
        test++;

        if(test != mProcesses.end())
        {
        	return *(test);
        }
        return NULL;
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

    bool ProcessSequence::read(const string& fName)
    {
    	if(mProject.loadXMLFromFile(fName))
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

    	bool saveRes(false);
        if(mProcessIter != mProcesses.begin())
        {
            //We need to preserve the current process iterator in the sequence
            list<Process*>::iterator savedIter = mProcessIter;

            saveRes = mProject.save();
            selectProcess(*(savedIter));
    	    return saveRes;
        }
        else
        {
            saveRes = mProject.save();
        }
        return saveRes;
    }

    string ProcessSequence::getXML()
    {
    	stringstream s;
        s << mProject.getXML();
        return s.str();
    }
}
