#ifndef ArrayCamServerH
#define ArrayCamServerH
#include "dslIPCServer.h"
#include "dslSocketWorker.h"
#include <vector>
#include "dslTimer.h"
#include "core/atArrayCamProtocol.h"
#include "dslIPCMessage.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------
using dsl::IPCServer;
using dsl::gEmptyString;
dsl::SocketWorker* createArrayCamIPCReceiver(int portNr, int socketHandle, void* parent);

typedef void (__closure *OnMessageUpdateCB)(const string& msg);

//!The ArrayCam server is a component that serve clients with an ArrayCam connection over a
//tcp/ip socket. The ArrayCam server is designed to handle messages and data related to the
//arraybot project. The ArrayCam server is a descendant of the IPC server class that is implementing all
//network functionality.
class TMainForm;
class PACKAGE ArrayCamServer : public IPCServer
{
    public:
                                            ArrayCamServer(TMainForm& mf, int portNumber = 50000);
	                                        ~ArrayCamServer();

											//!Requests are sent to the server from a client.
                                            //!The process request is an overide from the IPCServer base class.
                                            //!ProcessRequest implements the ArrayCam server specific processing.
    	bool 					            processRequest(dsl::IPCMessage& msg);
        bool            		            shutDown();
        void								assignOnUpdateCallBack(OnMessageUpdateCB cb);
		void								onUpdateClientsTimer();
        void								broadcastStatus();
        void								broadcast(ACMessageID id, const string& arg1  = gEmptyString, const string& arg2 = gEmptyString, const string& arg3 = gEmptyString);

    protected:
        OnMessageUpdateCB					onMessageUpdateCB;
        TMainForm&							mMainForm;
        void								notifyClients(const string& msg);
        ArrayCamProtocol					mProtocol;
};

#endif
