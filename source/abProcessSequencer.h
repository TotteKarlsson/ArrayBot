#ifndef abProcessSequencerH
#define abProcessSequencerH
#include <list>
#include "abExporter.h"
#include "abABObject.h"
#include "abProcessSequence.h"
#include "mtkTimer.h"

using mtk::Timer;
class LinearMove;
//---------------------------------------------------------------------------
typedef void (__closure *MyOnTimerCFPtr)(); //Need to research this and make it portable

class AB_CORE ProcessSequencer : public ABObject
{
	public:
			      	        ProcessSequencer();
                  	        ~ProcessSequencer(){}
		bool				assignUnit(ABObject* o);
		bool				load(const string& seqFName);
		bool				save(const string& folder);
		void				clear();
		void		        start(bool continous = true);
		void		        forward();
        void		        reverse();
        void		        stop();
        bool				isRunning();
        bool				isProcessActive();
        void		        addProcess(Process* p);
        bool		        removeProcess(Process* p);
        bool		        removeProcess(const string& name);

        ProcessSequence&   	getSequence(){return mSequence;}

	private:
    	ProcessSequence		mSequence;
        bool				mRunContinous;
        Timer				mSequenceTimer;
		void			    runThreaded();
		MyOnTimerCFPtr	    inThreadCB;
};

#endif
