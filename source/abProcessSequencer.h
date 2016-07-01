#ifndef abProcessSequencerH
#define abProcessSequencerH
#include <list>
#include "abExporter.h"
#include "abABObject.h"
#include "abProcessSequence.h"
#include "mtkTimer.h"
#include "abProcessSequenceProject.h"
#include "abProcessSequences.h"
using mtk::Timer;
class LinearMove;
//---------------------------------------------------------------------------
typedef void (__closure *MyOnTimerCFPtr)();

class AB_CORE ProcessSequencer : public ABObject
{
	public:
			      	                ProcessSequencer(const string& fileFolder);
                  	                ~ProcessSequencer(){}
		bool				        assignUnit(ABObject* o);

		bool						selectSequence(const string& sName);

		bool				        load(const string& sName);
		bool				        loadAll(const string& fileFolder);

		bool				        saveCurrent();

		void				        clear();
		void		                start(bool continous = true);
		void		                forward();
        void		                reverse();
        void		                stop();
        bool				        isRunning();
        bool				        isCurrentProcessActive();

        ProcessSequence*   	        getCurrentSequence();
        string				        getCurrentSequenceName();
        string				        getCurrentProcessName();

        bool						addSequence(ProcessSequence* seq);
        ProcessSequences&			getSequences();

	private:

    	ProcessSequences	        mSequences;

        							//!ExecuteAutomatic executes individual processes
                                    //!in sequence. If set false, each sequence need to be
                                    //!manually executed using the forward() function
        bool				        mExecuteAutomatic;
        Timer				        mSequenceTimer;
		void			            runThreaded();
		MyOnTimerCFPtr	            inThreadCB;
};

#endif
