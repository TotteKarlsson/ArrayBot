#ifndef atArrayBotServerH
#define atArrayBotServerH
#include "dslIPCServer.h"
#include "dslSocketWorker.h"
#include <vector>
//#include "arraybot/atArrayBot.h"
#include "atArrayBotProtocol.h"
#include "dslIPCMessage.h"
#include "dslConstants.h"
#include "arraybot/atArrayBot.h"
//---------------------------------------------------------------------------
using dsl::IPCServer;
using dsl::gEmptyString;
dsl::SocketWorker* createArrayBotIPCReceiver(int portNr, int socketHandle, void* parent);

class ArrayBot;
//typedef void (__closure *OnMessageUpdateCB)(const string& msg);

//!The ArrayBot server is a component that serve clients with an ArrayBot connection over a
//tcp/ip socket. The ArrayBot server is designed to handle messages and data related to the
//arraybot project. The ArrayBot server is a descendant of the IPC server class that is implementing all
//network functionality.
class AT_CORE ArrayBotServer : public IPCServer
{
    public:
                                            ArrayBotServer(ArrayBot& ab, int portNumber = 50000);
	                                        ~ArrayBotServer();

											//!Requests are sent to the server from a client.
                                            //!The process request is an overide from the IPCServer base class.
                                            //!ProcessRequest implements the ArrayBot server specific processing.
    	bool 					            processRequest(dsl::IPCMessage& msg);
        bool            		            shutDown();
//        void								assignOnUpdateCallBack(OnMessageUpdateCB cb);
		void								onUpdateClientsTimer();
        void								broadcastStatus();
        void								broadcast(ABMessageID id, const string& arg1  = gEmptyString, const string& arg2 = gEmptyString, const string& arg3 = gEmptyString);

    protected:
//        OnMessageUpdateCB					onMessageUpdateCB;

        									//!The Arraybot object that the server interacts with
        ArrayBot&							mArrayBot;
        void								notifyClients(const string& msg);
        ArrayBotProtocol					mProtocol;
};

#endif
