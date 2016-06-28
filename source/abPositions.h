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
		bool					        add(const ab::Position& pos);
        bool					        remove(const string& lbl);
        ab::Position*                   getFirst() const;
        ab::Position*                   getNext() const;
        ab::Position*                   getPrevious() const;
        ab::Position*                   getCurrent() const;


	protected:
    	mutable deque<ab::Position> 		mPositions;
    	mutable deque<ab::Position>::iterator mPositionsIter;
};
#endif
