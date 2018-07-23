#ifndef atArduinoMessageProcessorH
#define atArduinoMessageProcessorH
#include <string>
#include "dslThread.h"
#include "atCoreExporter.h"
#include "atATObject.h"
#include "atArduinoExporter.h"
//----------------------------------------------------------------

using dsl::Thread;

namespace dsl
{
	class MessageContainer;
}

using dsl::MessageContainer;

typedef void (__closure *OnMessageReceivedCB)(const string& msg);

namespace at
{
class ArduinoClient;
//!The Arduino Message processor processes messages sent from a
//!Arduino Server.
class AT_ARDUINO ArduinoMessageProcessor : public Thread, public ATObject
{
    public:
                                        ArduinoMessageProcessor(ArduinoClient& client);
                                        ~ArduinoMessageProcessor();

                                        // overridden from Thread
        void                            worker();
        void                            run();

        bool                            start(bool inThread);
        void                            stop();
        virtual void                    processMessage(const string& msg);
        void                            suspendProcessing() {mAllowProcessing = false;}
        void                            resumeProcessing()  {mAllowProcessing = true;}
		void							assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

	private:
        string                          mServerName;
        bool                            mAllowProcessing;
        MessageContainer&            	mMessageContainer;
        OnMessageReceivedCB		  		onMessageReceivedCB;
		ArduinoClient&					mClient;
};

}
#endif
