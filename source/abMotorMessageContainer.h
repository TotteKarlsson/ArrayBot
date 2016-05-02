#ifndef abMotorMessageContainerH
#define abMotorMessageContainerH
#include <deque>
#include "CoreExporter.h"
#include "Poco/Condition.h"
#include "abMotorMessageProcessor.h"
//---------------------------------------------------------------------------
using std::deque;

//The motorCMD container is used after fetching new motorCMDs from amazon
//An motorCMDs populator is popping motorCMDs from the container, pushing them into local database
//The motorCMDs are simple strings
class AB_CORE MotorMessageContainer
{
	friend  MotorMessageProcessor;
	public:
												MotorMessageContainer();
												~MotorMessageContainer();
		void                                    post(const string& motorCMD);

		bool                                    hasMessage();
		int                                     count();
		string                                  pop();
		string                                  peek();

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
		deque<string>                           mCommands;
};

#endif
