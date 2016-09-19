#ifndef abMotorMessageProcessorH
#define abMotorMessageProcessorH
#include "abExporter.h"
#include <string>
#include "mtkThread.h"
#include "abABObject.h"
#include "mtkConstants.h"
#include "mtkStringList.h"
#include "abMotorMessageProcessor.h"
#include "abMotorCommand.h"
//---------------------------------------------------------------------------
class MotorMessageContainer;
class APTMotor;
using mtk::StringList;

using mtk::gEmptyString;
typedef void __fastcall (__closure *UICallback)(void);

class AB_CORE MotorMessageProcessor : public ABObject, public mtk::Thread
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

#endif
