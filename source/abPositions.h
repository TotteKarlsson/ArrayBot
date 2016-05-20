#ifndef abPositionsH
#define abPositionsH
#include "abExporter.h"
#include "abABObject.h"
#include <deque>
#include "abPosition.h"
//---------------------------------------------------------------------------
using std::deque;


class AB_CORE Positions : public ABObject
{
	public:
								        Positions();
								        ~Positions();
		bool					        add(const Position& pos);
        bool					        remove(const string& lbl);
        Position*                       getFirst() const;
        Position*                       getNext() const;
        Position*                       getPrevious() const;
        Position*                       getCurrent() const;


	protected:
    	mutable deque<Position> 		mPositions;
    	mutable deque<Position>::iterator mPositionsIter;
};
#endif
