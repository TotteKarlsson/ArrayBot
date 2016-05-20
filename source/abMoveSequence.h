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
using std::string;

class AB_CORE MoveSequence : public ABObject
{
    public:
								MoveSequence();
				        		~MoveSequence(){}
		bool					assignUnit(ABObject* o);
		void					clear();
        bool					load(const string& fName);
        bool					save();
		bool 					add(SMove* move);
		bool 					remove(const string& lbl);

        SMove*                 	getFirst() const;
        SMove*                  getNext() const;
        SMove*                  getPrevious() const;
        SMove*                  getCurrent() const;

    protected:
  		string					mName;
		mutable list<SMove*>  			 mMoves;
        mutable list<SMove*>::iterator   mMovesIter;
};

#endif
