#pragma hdrstop
#include "atPositions.h"
//---------------------------------------------------------------------------

using ab::Position;
Positions::Positions()
{}

Positions::~Positions()
{}

bool Positions::add(const ab::Position& pos)
{
	//Check label
    mPositions.push_front(pos);
    return true;
}

bool Positions::remove(const string& lbl)
{
	//Find item
    return false;
}

Position* Positions::getFirst() const
{
    mPositionsIter = mPositions.begin();
    if(mPositionsIter != mPositions.end())
    {
        return &(*mPositionsIter);
    }
    return NULL;
}

Position* Positions::getCurrent() const
{
    if(mPositionsIter != mPositions.end())
    {
        return &(*mPositionsIter);
    }
    return NULL;
}

Position* Positions::getNext() const
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

Position* Positions::getPrevious() const
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


