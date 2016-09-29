#ifndef abArduinoMessageProcessorH
#define abArduinoMessageProcessorH
#include <string>
#include "mtkThread.h"
#include "abExporter.h"
//----------------------------------------------------------------

using mtk::Thread;

namespace mtk
{
	class MessageContainer;
}

using mtk::MessageContainer;
class ArduinoClient;
typedef void (__closure *OnMessageReceivedCB)(const string& msg);

//!The Arduino Message processor processes messages sent from a
//!Arduino Server.
class AB_CORE ArduinoMessageProcessor : public Thread
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

#endif
