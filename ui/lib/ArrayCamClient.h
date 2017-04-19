#ifndef ArrayCamClientH
#define ArrayCamClientH
#include "atExporter.h"
#include "atATObject.h"
#include "mtkProperty.h"
#include "mtkMessageContainer.h"
#include "ArrayCamMessageProcessor.h"
#include "mtkSocketClient.h"

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
class ArrayCamClient : public SocketClient, public ATObject
{
	friend ArrayCamMessageProcessor;
	public:
                                            ArrayCamClient();
    	virtual                             ~ArrayCamClient();
        virtual bool                        shutDown();

        virtual bool                        init(int pNumber = 50001, const string& hostname = mtk::gEmptyString, bool connectOnInit = true);
        bool                                isConnected();
        bool                                disConnect();
        bool                                connect(int pNumber = -1, const string& host = mtk::gEmptyString);

		virtual void	 					getBoardStatus(){}
		void								getServerStatus();

									        //!Post a custom message to the message list
        virtual void                        postMessage(const string& msg);
        void		 						assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

    protected:
        ArrayCamMessageProcessor   			mMessageProcessor;
};

#endif
