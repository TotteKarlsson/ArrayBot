#ifndef abMotorMessageProcessorH
#define abMotorMessageProcessorH
#include "CoreExporter.h"
#include <string>
#include "mtkThread.h"
#include "mtkConstants.h"
//#include <System.Classes.hpp>
//#include "amlAccountDB.h"
#include "mtkStringList.h"
//---------------------------------------------------------------------------
class MotorMessageContainer;

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

        void                                        pauseProcessing();
        void                                        resumeProcessing();
        UICallback                                  mNotifyUI;
		bool										importOrderData(const StringList& motorCMD);
		bool										importCustomerData(const StringList& motorCMD);
		bool										importStateOrRegionData(const StringList& motorCMD);

	protected:
		long                                        mOrderProcessedCount;
		bool                                        mAllowProcessing;
		string                                      mDBPath;
		MotorMessageContainer&                             mMotorMessageContainer;
//		AccountDB&                                  mDB;
};

#endif
