#ifndef atPositionsH
#define atPositionsH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include <deque>
#include "atPosition.h"
//---------------------------------------------------------------------------
using std::deque;


class AT_AB Positions : public ATObject
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
