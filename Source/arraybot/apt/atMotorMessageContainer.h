#ifndef atMotorMessageContainerH
#define atMotorMessageContainerH
#include <deque>
#include "arraybot/atABExporter.h"
#include "Poco/Condition.h"
#include "atMotorMessageProcessor.h"
#include "atMotorCommand.h"
//---------------------------------------------------------------------------
using std::deque;

namespace at
{
    //The motorCMD container is used after fetching new motorCMDs from amazon
    //An motorCMDs populator is popping motorCMDs from the container, pushing them into local database
    //The motorCMDs are simple strings
    class AT_AB MotorMessageContainer : public ATObject
    {
    	friend  MotorMessageProcessor;
    	public:
    												MotorMessageContainer();
    												~MotorMessageContainer();

    		void                                    post(const MotorCommand& cmd);

    		bool                                    hasMessage();
    		int                                     count();
    		MotorCommand                            pop();
    		MotorCommand                            peek();

    												//The motorCMD proceesor is waiting
    												//for signals from the container
    												//use wakeUpWatchers, to move them out of
    												//waiting state
    		void									wakeUpWatchers();

    	protected:
    		Poco::Mutex                             mListMutex;
    		Poco::Condition                         mNewCommandCondition;
    		int 									mNrOfProcessedCommands;

    	private:
    		deque<MotorCommand>                     mCommands;
    };
}
#endif
