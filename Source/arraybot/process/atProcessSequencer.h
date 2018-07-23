#ifndef atProcessSequencerH
#define atProcessSequencerH
#include <list>
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atProcessSequence.h"
#include "dslTimer.h"
#include "atProcessSequenceProject.h"
#include "atProcessSequences.h"

using dsl::Timer;
namespace at
{

class Move;
class ArrayBot;
class ArrayCamClient;
//!The Process Sequencer executes and maintain a process sequence.
//!A sequence consists of individual processes that can be executed step by step, or executed
//!continously.

//!The sequencer do currently load all available sequences into a sequence container.
//Todo: Break out the sequence container to simplify the complexity of the sequencer
//Todo: Derive from this an ArrayBot sequences
//!The sequencer will hand resources, such as the ArrayCamClient, and/or ArrayBot, to
//!executing processes in a sequence

//---------------------------------------------------------------------------
class AT_AB ProcessSequencer : public ATObject
{
	public:
			      	                        ProcessSequencer(ArrayBot& ab, ArrayCamClient& acc, const string& fileFolder);
                  	                        ~ProcessSequencer();
		bool				                load(const string& sName);
		bool				                loadAll(const string& fileFolder);
		bool						        selectSequence(const string& sName);

        bool								initCurrentSequence();

        bool						        deleteSequence(const string& seq);
		bool				                saveCurrent();
		void				                clear();

											//!There are Five main controlling actions, start, stop, pause, resume and forward
		void		                        start(bool continous = true);
        void		                        stop();
		void		                        pause();
		bool 		                        resume();
		bool		                        forward();

		bool		                        reset();
		bool								continueExecution();
        bool								canContinue();

        bool				                isRunning();
        bool				                isPaused();
        bool				                isCurrentProcessActive();

        									//!After all processes are executed, the processsequence is done
        bool								isDone();

        ProcessSequence*   	                getCurrentSequence();
        string				                getCurrentSequenceName();
        string				                getCurrentProcessName();
		string								getNextProcessName();

        bool						        addSequence(ProcessSequence* seq);
        ProcessSequences&			        getSequences();
        ArrayBot&							getArrayBot(){return mAB;}
       	ArrayCamClient&						getArrayCamClient(){return mArrayCamClient;}

	private:
    								        //!The sequencer is executing each sequence handing
                                            //various resources to the sequnce
    	ArrayBot&					        mAB;
    	ArrayCamClient&				        mArrayCamClient;
    	ProcessSequences	                mSequences;

        							        //!ExecuteAutomatic executes individual processes
                                            //!in sequence. If set false, each sequence need to be
                                            //!manually executed using the forward() function
        bool				                mExecuteAutomatic;

        									//!The sequence time checks the state of the sequence
                                            //!and individual processes every 50 ms
        Timer				                mSequenceTimer;
		void			                    onTimerFunc();
};

}
#endif
