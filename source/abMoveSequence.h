#ifndef abMoveSequenceH
#define abMoveSequenceH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <vector>
#include <string>
#include "abSpatialMove.h"
#include "abProcessSequence.h"
//---------------------------------------------------------------------------

using std::list;
using std::string;

class AB_CORE MoveSequence : public ProcessSequence
{
    public:
										        MoveSequence();
				        		                ~MoveSequence(){}
		bool					                assignUnit(ABObject* o);
		void					                clear();
        bool					                load(const string& fName);
        bool					                save();
		bool 					                add(SpatialMove* move);
		bool 					                remove(const string& lbl);

        SpatialMove*                 	        getFirst() const;
        SpatialMove*                          	getNext() const;
        SpatialMove*                          	getPrevious() const;
        SpatialMove*                          	getCurrent() const;

    protected:
  		string					        		mName;
		mutable list<SpatialMove*>  			mMoves;
        mutable list<SpatialMove*>::iterator 	mMovesIter;
};

#endif
