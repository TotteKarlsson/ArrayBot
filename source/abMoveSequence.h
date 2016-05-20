#ifndef abMoveSequenceH
#define abMoveSequenceH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <string>

//---------------------------------------------------------------------------
using std::list;
using std::string;
class Move;
class AB_CORE MoveSequence : public ABObject
{
    public:
								MoveSequence(){}
				        		~MoveSequence(){}
		void					clear();

		bool 					add(Move* move);
		bool 					remove(const string& lbl);

        Move*                   getFirst() const;
        Move*                   getNext() const;
        Move*                   getPrevious() const;
        Move*                   getCurrent() const;



    protected:
		mutable list<Move*>  			mMoves;
        mutable list<Move*>::iterator   mMovesIter;
};

#endif
