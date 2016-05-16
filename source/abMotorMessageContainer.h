#ifndef abMotorMessageContainerH
#define abMotorMessageContainerH
#include <deque>
#include "abExporter.h"
#include "Poco/Condition.h"
#include "abMotorMessageProcessor.h"
#include "abMotorCommand.h"
//---------------------------------------------------------------------------
using std::deque;

//The motorCMD container is used after fetching new motorCMDs from amazon
//An motorCMDs populator is popping motorCMDs from the container, pushing them into local database
//The motorCMDs are simple strings
class AB_CORE MotorMessageContainer : public ABObject
{
	friend  MotorMessageProcessor;
	public:
												MotorMessageContainer();
												~MotorMessageContainer();
		void                                    post(const MotorCommand& cmd);
//		void                                    post(const string& motorCMD);

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

#endif
