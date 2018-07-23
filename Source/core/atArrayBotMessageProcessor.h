#ifndef atArrayBotMessageProcessorH
#define atArrayBotMessageProcessorH
#include <string>
#include "dslThread.h"
#include "atCoreExporter.h"
#include "atATObject.h"
//----------------------------------------------------------------

using dsl::Thread;
using std::vector;
namespace dsl
{
	class MessageContainer;
}

using dsl::MessageContainer;
typedef void (__closure *OnMessageReceivedCB)(const string& msg);
namespace at
{

    class ArrayBotClient;
    //!The ArrayBot Message processor processes messages sent from a
    //!ArrayBot Server.
    class AT_CORE ArrayBotMessageProcessor : public Thread, public ATObject
    {

        public:
                                            ArrayBotMessageProcessor(ArrayBotClient& client);
                                            ~ArrayBotMessageProcessor();

                                            // overridden from Thread
            void                            worker();
            void                            run();

            bool                            start(bool inThread);
            void                            stop();
            virtual void                    processMessage(const string& msg);
            void                            suspendProcessing() {mAllowProcessing = false;}
            void                            resumeProcessing()  {mAllowProcessing = true;}

            								//Might be nicer to setup a proper subject/observer mechanism
    		void							assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);


    	private:
            string                          mServerName;
            bool                            mAllowProcessing;
            MessageContainer&            	mMessageContainer;
            vector<OnMessageReceivedCB>		onMessageReceivedCallbacks;

    		ArrayBotClient&					mClient;
    };
}

#endif
