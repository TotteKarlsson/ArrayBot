#ifndef abMoveSequencerH
#define abMoveSequencerH
#include <list>
#include "abExporter.h"
#include "abABObject.h"
#include "abMoveSequence.h"
#include "mtkTimer.h"

using mtk::Timer;
//---------------------------------------------------------------------------
typedef void (__closure *MyOnTimerCFPtr)(); //Need to research this and make it portable

class AB_CORE MoveSequencer : public ABObject
{
	public:
			      	        MoveSequencer();
                  	        ~MoveSequencer(){}
		bool				assignUnit(ABObject* o);
		bool				load(const string& seqFName);
		bool				save();
		void				clear();
		void		        start(bool continous = true);
		void		        forward();
        void		        reverse();
        void		        stop();
        bool				isRunning();
        void		        addMove(SpatialMove* newMove);
        MoveSequence&		getSequence(){return mSequence;}

	private:
    	MoveSequence		mSequence;
        bool				mRunContinous;
        bool				mIsRunning;
        Timer				mSequenceTimer;
		void			    runThreaded();
		MyOnTimerCFPtr	    inThreadCB;
};

#endif
