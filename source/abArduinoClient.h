#ifndef abArduinoClientH
#define abArduinoClientH
#include "abExporter.h"
#include "abABObject.h"
#include "mtkProperty.h"
#include "mtkMessageContainer.h"
#include "abArduinoMessageProcessor.h"
#include "mtkSocketClient.h"
#include "mtkSocketReceiver.h"

namespace mtk
{
	class SocketClient;
    class Thread;
}

using mtk::SocketClient;
using mtk::Thread;
using mtk::Property;
using mtk::MessageContainer;
using mtk::SocketReceiver;

//!The Arduino (socket) client class connects to a server over a socket.
//!Messages are received, over the socket, by a socket receiver and placed in a message container.
//!Received messages are processed by the ArduinoMessageProcessor.

class AB_CORE ArduinoClient : public SocketClient
{
	friend ArduinoMessageProcessor;
     public:
                                            ArduinoClient();
        virtual                             ~ArduinoClient();

        virtual bool                        init(int pNumber = 50010, const string& hostname = mtk::gEmptyString, bool connectOnInit = true);
        virtual bool                        shutDown();

        									//Requests to the server
        void								resetSectionCounter();
        void								setPuffAfterSectionCount(int c);
        void								enableAutoPuff();
        void								disableAutoPuff();
		void								toggleLED();
		void								toggleCoax();


		void								getStatus();

        virtual void                        postMessage(const string& msg);                        //Post a message to the message list
        string                              getClientInfo();

        bool                                isConnected();

        bool                                disConnect();
        bool                                connect(int pNumber = -1, const string& host = mtk::gEmptyString);

        void		 						assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

    protected:
        MessageContainer                 	mIncomingMessages;
        SocketReceiver						mReceiver;
        ArduinoMessageProcessor   			mMessageProcessor;
};


#endif
