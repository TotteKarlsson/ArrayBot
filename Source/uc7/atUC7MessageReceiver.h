#ifndef atUC7MessageReceiverH
#define atUC7MessageReceiverH
#include "atCoreExporter.h"
#include <string>
#include "dslThread.h"
#include "atATObject.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include "atUC7Exporter.h"
//---------------------------------------------------------------------------

using dsl::gEmptyString;

namespace at
{

    class UC7;
    //The message consumer monitors the referenced UC7 object for new
    //messages. When a new message is available, the message is popped
    //from the UC7 queue and propagated to the main UI, which is responsible
    //to handle it.
    class AT_UC7 UC7MessageReceiver : public dsl::Thread, public ATObject
    {
        public:
                                                        UC7MessageReceiver(UC7& list,  HWND__ *h, const string& threadName = gEmptyString);
                                                        ~UC7MessageReceiver();

                                                        //overridden from Thread
            void                                        run();
            virtual void                                worker();
            void                                        stop();
            bool                                        start(bool in_thread = true);
            void                                        pauseProcessing();
            void                                        resumeProcessing();

    	protected:
    		long                                        mProcessedCount;
    		bool                                        mAllowProcessing;
            double										mProcessTimeDelay;
    		UC7&                      					mUC7;

            											//The handle is needed for window messaging
            HWND__*										mHandle;
    };

}

#endif
