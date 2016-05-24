#ifndef abProcessSequencerH
#define abProcessSequencerH
#include <list>
#include "abExporter.h"
#include "abABObject.h"
#include "abProcessSequence.h"
#include "mtkTimer.h"

using mtk::Timer;
class SpatialMove;
//---------------------------------------------------------------------------
typedef void (__closure *MyOnTimerCFPtr)(); //Need to research this and make it portable

class AB_CORE ProcessSequencer : public ABObject
{
	public:
			      	        ProcessSequencer();
                  	        ~ProcessSequencer(){}
		bool				assignUnit(ABObject* o);
		bool				load(const string& seqFName);
		bool				save();
		void				clear();
		void		        start(bool continous = true);
		void		        forward();
        void		        reverse();
        void		        stop();
        bool				isRunning();
        void		        addProcess(Process* newMove);
        ProcessSequence&   	getSequence(){return mSequence;}

	private:
    	ProcessSequence		mSequence;
        bool				mRunContinous;
        bool				mIsRunning;
        Timer				mSequenceTimer;
		void			    runThreaded();
		MyOnTimerCFPtr	    inThreadCB;
};

#endif
