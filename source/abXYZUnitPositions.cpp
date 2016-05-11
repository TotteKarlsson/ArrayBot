#pragma hdrstop
#include "abXYZUnitPositions.h"
//---------------------------------------------------------------------------

XYZUnitPositions::XYZUnitPositions()
{}

XYZUnitPositions::~XYZUnitPositions()
{}

bool XYZUnitPositions::add(const XYZUnitPosition& pos)
{
	//Check label
    mPositions.push_front(pos);
    return true;
}

bool XYZUnitPositions::remove(const string& lbl)
{
	//Find item
    return false;
}

XYZUnitPosition* XYZUnitPositions::getFirst() const
{
    mPositionsIter = mPositions.begin();
    if(mPositionsIter != mPositions.end())
    {
        return &(*mPositionsIter);
    }
    return NULL;
}

XYZUnitPosition* XYZUnitPositions::getCurrent() const
{
    if(mPositionsIter != mPositions.end())
    {
        return &(*mPositionsIter);
    }
    return NULL;
}

XYZUnitPosition* XYZUnitPositions::getNext() const
{
    if(mPositionsIter != mPositions.end())
    {
        mPositionsIter++;
        if(mPositionsIter != mPositions.end())
        {
            return &(*mPositionsIter);
        }
    }
    return NULL;
}

XYZUnitPosition* XYZUnitPositions::getPrevious() const
{
    if(mPositionsIter != mPositions.end())
    {
        mPositionsIter--;
        if(mPositionsIter != mPositions.end())
        {
            return &(*mPositionsIter);
        }
    }
    return NULL;
}


