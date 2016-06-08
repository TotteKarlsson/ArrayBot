#pragma hdrstop
#include "abPairedMoves.h"
#include "mtkStringList.h"
//---------------------------------------------------------------------------
using namespace mtk;

PairedMoves::PairedMoves(const string& iniSection, IniFile& iniFile)
:
mIniSection(iniSection),
mIniFile(iniFile)
{
    readINIParameters();
}

PairedMoves::~PairedMoves()
{
	writeINIParameters();
}

bool PairedMoves::readINIParameters()
{
	IniSection* sec =  mIniFile.getSection(mIniSection, true);

    if(sec)
    {
    	IniKey* aKey = sec->getFirst();
        while(aKey)
        {
        	StringList vals(aKey->mValue,',');
        	PairedMove pm(aKey->mKey, toDouble(vals[0]), toDouble(vals[1]), toDouble(vals[2]));
	        add(pm);
            aKey = sec->getNext();
        }
    }
    return true;
}

bool PairedMoves::writeINIParameters()
{
	//For each setting, create a iniKey and write to inifile
	PairedMove* pm = getFirst();
	IniSection* sec =  mIniFile.getSection(mIniSection, true);
    while(pm && sec)
    {
        IniKey* key = sec->getKey(pm->mLabel, true);
        if(key)
        {
            key->mValue = pm->asIniRecord();
        }
		pm = getNext();
    }
    return true;
}

PairedMove* PairedMoves::add(const PairedMove& pos)
{
	//Check label
    mPairedMoves.push_front(pos);
    return &(*(mPairedMoves.begin()));
}

bool PairedMoves::remove(const string& lbl)
{
	//Find item
    return false;
}

PairedMove* PairedMoves::getPairedMove(const string& name)
{
	PairedMove* pm = getFirst();
    while(pm)
    {
        if(compareNoCase(pm->mLabel, name))
        {
        	return pm;
        }
		pm = getNext();
    }
	return NULL;
}

PairedMove* PairedMoves::getFirst() const
{
    mPairedMovesIter = mPairedMoves.begin();
    if(mPairedMovesIter != mPairedMoves.end())
    {
        return &(*mPairedMovesIter);
    }
    return NULL;
}

PairedMove* PairedMoves::getCurrent() const
{
    if(mPairedMovesIter != mPairedMoves.end())
    {
        return &(*mPairedMovesIter);
    }
    return NULL;
}

PairedMove* PairedMoves::getNext() const
{
    if(mPairedMovesIter != mPairedMoves.end())
    {
        mPairedMovesIter++;
        if(mPairedMovesIter != mPairedMoves.end())
        {
            return &(*mPairedMovesIter);
        }
    }
    return NULL;
}

PairedMove* PairedMoves::getPrevious() const
{
    if(mPairedMovesIter != mPairedMoves.end())
    {
        mPairedMovesIter--;
        if(mPairedMovesIter != mPairedMoves.end())
        {
            return &(*mPairedMovesIter);
        }
    }
    return NULL;
}
