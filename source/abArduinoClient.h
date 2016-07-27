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

class AB_CORE ArduinoClient : public ABObject
{
     public:
                                            ArduinoClient();
        virtual                             ~ArduinoClient();

        virtual bool                        init(int pNumber = 50010, const string& hostname = mtk::gEmptyString, bool connectOnInit = true);
        virtual bool                        shutDown();

        virtual void                        postMessage(const string& msg);                        //Post a message to the message list
        string                              getClientInfo();

        bool                                isConnected();

        bool                                disConnect();
        bool                                connect(int pNumber = -1, const string& host = mtk::gEmptyString);

    protected:
        SocketClient						mSocketClient;          //Socket to the server

        MessageContainer                 	mIncomingMessages;
        SocketReceiver						mReceiver;
        ArduinoMessageProcessor   			mMessageProcessor;
};


#endif
