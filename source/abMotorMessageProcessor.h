#ifndef abMotorMessageProcessorH
#define abMotorMessageProcessorH
#include "CoreExporter.h"
#include <string>
#include "mtkThread.h"
#include "mtkConstants.h"
#include "mtkStringList.h"
//---------------------------------------------------------------------------
class MotorMessageContainer;
class APTMotor;
using mtk::StringList;

using mtk::gEmptyString;
typedef void __fastcall (__closure *UICallback)(void);

class AB_CORE MotorMessageProcessor : public mtk::Thread
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

	protected:
		long                                        mProcessedCount;
		bool                                        mAllowProcessing;
        APTMotor*									mMotor;

		MotorMessageContainer&                      mMotorMessageContainer;
};

#endif
