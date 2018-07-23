#ifndef atElloUIClientH
#define atElloUIClientH
#include "atCoreExporter.h"
#include "atATObject.h"
#include "dslProperty.h"
#include "dslMessageContainer.h"
#include "atElloUIMessageProcessor.h"
#include "dslSocketClient.h"

namespace dsl
{
	class SocketClient;
    class Thread;
}

using dsl::SocketClient;
using dsl::Thread;
using dsl::Property;
using dsl::MessageContainer;
using dsl::SocketReceiver;

namespace at
{

    //!The ElloUI (socket) client class connects to a ElloUI server over a socket.
    //!Messages are received, over the socket, by a socket receiver and placed in a message container.
    //!Received messages are processed by the ElloUIMessageProcessor.
    class AT_CORE ElloUIClient : public SocketClient, public ATObject
    {
    	friend ElloUIMessageProcessor;
    	public:
                                                ElloUIClient();
        	virtual                             ~ElloUIClient();
            virtual bool                        shutDown();

            virtual bool                        init(int pNumber = 50002, const string& hostname = dsl::gEmptyString, bool connectOnInit = true);
            bool                                isConnected();
            bool                                disConnect();
            bool                                connect(int pNumber = 50002, const string& host = dsl::gEmptyString);

    		void								run();

    									        //!Post a custom message to the message list
            virtual void                        postMessage(const string& msg);
            void		 						assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

        protected:
            ElloUIMessageProcessor   			mMessageProcessor;
    };

}

#endif
