#ifndef ArrayCamMessageProcessorH
#define ArrayCamMessageProcessorH
#include <string>
#include "mtkThread.h"
#include "atExporter.h"
#include "atATObject.h"
//----------------------------------------------------------------

using mtk::Thread;

namespace mtk
{
	class MessageContainer;
}

using mtk::MessageContainer;
class ArrayCamClient;
typedef void (__closure *OnMessageReceivedCB)(const string& msg);

//!The ArrayCam Message processor processes messages sent from a
//!ArrayCam Server.
class AT_CORE ArrayCamMessageProcessor : public Thread, public ATObject
{

    public:
                                        ArrayCamMessageProcessor(ArrayCamClient& client);
                                        ~ArrayCamMessageProcessor();

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
		ArrayCamClient&					mClient;
};

#endif
