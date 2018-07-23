#ifndef atMotorMessageProcessorH
#define atMotorMessageProcessorH
#include "arraybot/atABExporter.h"
#include <string>
#include "dslThread.h"
#include "atATObject.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include "atMotorMessageProcessor.h"
#include "atMotorCommand.h"
//---------------------------------------------------------------------------

using dsl::StringList;
using dsl::gEmptyString;
typedef void __fastcall (__closure *UICallback)(void);

namespace at
{

    class MotorMessageContainer;
    class APTMotor;

    class AT_AB MotorMessageProcessor : public dsl::Thread, public ATObject
    {
        public:
                                                        MotorMessageProcessor(MotorMessageContainer& list, const string& threadName=gEmptyString);
                                                        ~MotorMessageProcessor();
            bool                                        openDataBase(const string& db);

                                                        // overridden from Thread
            void                                        run();
            virtual void                                worker();
            void                                        stop();
            bool                                        start(bool in_thread = true);
            void										assignMotor(APTMotor* motor);

            void                                        pauseProcessing();
            void                                        resumeProcessing();
            UICallback                                  mNotifyUI;
            MotorCommandEnum							getLastProcessedMessage();

    	protected:
    		long                                        mProcessedCount;
    		bool                                        mAllowProcessing;
    		MotorCommandEnum							mLastProcessedCommand;
            APTMotor*									mMotor;
            double										mProcessTimeDelay;
    		MotorMessageContainer&                      mMotorMessageContainer;
    };
}

#endif
