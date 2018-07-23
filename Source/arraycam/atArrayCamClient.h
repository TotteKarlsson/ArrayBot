#ifndef atArrayCamClientH
#define atArrayCamClientH
#include "atCoreExporter.h"
#include "atATObject.h"
#include "dslProperty.h"
#include "dslMessageContainer.h"
#include "atArrayCamMessageProcessor.h"
#include "dslSocketClient.h"
#include "atArrayCamProtocol.h"

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
    class AT_CORE ArrayCamClient : public SocketClient, public ATObject
    {
    	friend ArrayCamMessageProcessor;
    	public:
                                                ArrayCamClient();
        	virtual                             ~ArrayCamClient();
            virtual bool                        shutDown();

            virtual bool                        init(int pNumber = 50001, const string& hostname = dsl::gEmptyString, bool connectOnInit = true);
            bool                                isConnected();
            bool                                disConnect();
            bool                                connect(int pNumber = -1, const string& host = dsl::gEmptyString);

    		virtual void	 					getBoardStatus(){}
    		void								getServerStatus();
            bool								startVideo();
            bool								stopVideo();

            bool								setWhiskerSyncOff();
            bool								setWhiskerSyncOn();

            bool								setZoomAndFocus(int zoom, int focus);
            bool								zoomIn(int val);
            bool								zoomOut(int val);

            bool								focusIn(int val);
            bool								focusOut(int val);

            bool								setLEDIntensity(int intensity);

            bool								triggerRibbonSeparator();

            bool								takeSnapShot();
            bool								enableBarcodeScanner();
            bool								disableBarcodeScanner();

            bool								startUC7();
            bool								stopUC7();

    									        //!Post a custom request
            bool 		                        postRequest(const string& msg);
            bool 		                        postRequest(const string& msg, int p1);
            bool 		                        postRequest(const string& msg, int p1, int p2);

            void		 						assignOnMessageReceivedCallBack(OnMessageReceivedCB cb);

        protected:
            ArrayCamMessageProcessor   			mMessageProcessor;
            ArrayCamProtocol					mProtocol;
    };

}

#endif
