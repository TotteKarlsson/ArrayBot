#pragma hdrstop
#include "abMoveSequence.h"
#include "mtkIniFile.h"
#include "abAbsoluteMove.h"

using namespace mtk;

//---------------------------------------------------------------------------
MoveSequence::MoveSequence()
:
mName("MoveSequence")
{}

bool MoveSequence::assignUnit(ABObject* o)
{
    SpatialMove* move = getFirst();
    while(move)
    {
    	move->assignUnit(o);
        move = getNext();
    }
}

void MoveSequence::clear()
{
	mMoves.clear();
}

bool MoveSequence::load(const string& fName)
{
	IniFile f(fName, true);
    int count = 0;
	IniSection* sec = f.getSection(count);
    IniKey* key;

    while(sec)
    {
    	key = sec->getKey("TYPE");
    	if(key && key->mValue == "ABSOLUTE")
        {
	        string name;
        	key = sec->getKey("POSITION_NAME");
            if(key)
            {
            	name = key->mValue;
            }

        	key = sec->getKey("POSITION");
            double x = key->asFloat();
	    	SpatialMove* move = new AbsoluteMove(NULL, ab::Position(name, x, 0.0,0.0));

            key = sec->getKey("MAX_VELOCITY", true);
			double vel = key->asFloat();

            key = sec->getKey("ACCELERATION", true);
			double a = key->asFloat();

            key = sec->getKey("DWELL_TIME", true);
			double dt = key->asFloat();

            if(move)
            {
            	move->setMaxVelocity(vel);
                move->setAcceleration(a);
                move->setDwellTime(dt);
            	add(move);
            }
        }
        //Get next section
        sec = f.getSection(++count);
    }
}

bool MoveSequence::save()
{
	//Save to file
	IniFile f(mName + ".moves");

    SpatialMove* move = getFirst();
    int count = 1;
    while(move)
    {
        IniSection *sec = f.createSection("MOVE " + mtk::toString(count));
        if(sec)
        {
        	IniKey* key = sec->createKey("POSITION_NAME", move->getPositionName());

            double x = move->getPosition().x();
           	key = sec->createKey("TYPE", move->getType());
           	key = sec->createKey("POSITION", toString(x));
           	key = sec->createKey("MAX_VELOCITY", toString(move->getMaxVelocity()));
            key = sec->createKey("ACCELERATION", toString(move->getAcceleration()));
			key = sec->createKey("DWELL_TIME",   toString(move->getDwellTime()));


        }
        count++;
        move = getNext();
    }

    f.save();
}

bool MoveSequence::add(SpatialMove* pos)
{
	//Check label
    mMoves.push_back(pos);
    mMovesIter = mMoves.begin();
    return true;
}

bool MoveSequence::remove(const string& lbl)
{
	//Find item
    return false;
}

SpatialMove* MoveSequence::getFirst() const
{
    mMovesIter = mMoves.begin();
    if(mMovesIter != mMoves.end())
    {
        return (*mMovesIter);
    }
    return NULL;
}

SpatialMove* MoveSequence::getCurrent() const
{
    if(mMovesIter != mMoves.end())
    {
        return (*mMovesIter);
    }
    return NULL;
}

SpatialMove* MoveSequence::getNext() const
{
    if(mMovesIter != mMoves.end())
    {
        mMovesIter++;
        if(mMovesIter != mMoves.end())
        {
            return (*mMovesIter);
        }
    }
    return NULL;
}

SpatialMove* MoveSequence::getPrevious() const
{
    if(mMovesIter != mMoves.end())
    {
        mMovesIter--;
        if(mMovesIter != mMoves.end())
        {
            return (*mMovesIter);
        }
    }
    return NULL;
}


