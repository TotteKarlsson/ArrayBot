#ifndef atArrayBotClientH
#define atArrayBotClientH
#include "atCoreExporter.h"
#include "atATObject.h"
#include "dslProperty.h"
#include "dslMessageContainer.h"
#include "atArrayBotMessageProcessor.h"
#include "dslSocketClient.h"
#include "atArrayBotProtocol.h"

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

    //!The client class connects to a server over a socket.
    //!Messages are received, over the socket, by a socket receiver and placed in a message container.
    //!Received messages are processed by the MessageProcessor.
    class AT_CORE ArrayBotClient : public SocketClient, public ATObject
    {
    	friend ArrayBotMessageProcessor;
    	public:
                                                ArrayBotClient();
        	virtual                             ~ArrayBotClient();
            virtual bool                        shutDown();

            virtual bool                        init(int pNumber = 50001, const string& hostname = dsl::gEmptyString, bool connectOnInit = true);
            bool                                isConnected();
            bool                                disConnect();
            bool                                connect(int pNumber = -1, const string& host = dsl::gEmptyString);

    		virtual void	 					getBoardStatus(){}
    		void								getServerStatus();

    									        //!Post a custom request
            bool 		                        postRequest(const string& msg);
            bool 		                        postRequest(const string& msg, int p1);
            bool 		                        postRequest(const string& msg, int p1, int p2);

            void		 						assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

        protected:
            ArrayBotMessageProcessor   			mMessageProcessor;
            ArrayBotProtocol					mProtocol;
    };
}

#endif
