#ifndef abMoveSequenceH
#define abMoveSequenceH

#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <vector>
#include <string>
#include "abSMove.h"
//---------------------------------------------------------------------------

using std::list;
using std::vector;
using std::string;
class test;

class AB_CORE MoveSequence : public ABObject
{
    public:
//								MoveSequence(){}
//				        		~MoveSequence(){}
//		void					clear();
//
//		bool 					add(SMove* move);
//		bool 					remove(const string& lbl);
//
//        SMove*                   getFirst() const;
//        SMove*                   getNext() const;
//        SMove*                   getPrevious() const;
//        SMove*                   getCurrent() const;

    protected:
		mutable vector<SMove*>  			mMoves;
//        mutable list<SMove*>::iterator   mMovesIter;
};

#endif
