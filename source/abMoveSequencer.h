#ifndef abMoveSequencerH
#define abMoveSequencerH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include "abMoveSequence.h"

using std::list;
//---------------------------------------------------------------------------
class Move;
class AB_CORE MoveSequencer : public ABObject
{
	public:
			      	        MoveSequencer(){}
                  	        ~MoveSequencer(){}
		void				clear();
		void		        forward();
        void		        reverse();
        void		        stop();
        void		        addMove(Move* newMove);


	private:
    	MoveSequence		mSequence;

};

#endif
