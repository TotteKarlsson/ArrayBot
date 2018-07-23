#ifndef atArduinoIPCServerReceiverH
#define atArduinoIPCServerReceiverH
#include "dslIPCReceiver.h"
#include "dslIPCServer.h"
//---------------------------------------------------------------------------

using dsl::SocketWorker;
SocketWorker* PACKAGE createArrayCamIPCReceiver(int portNr, int socketHandle, void* server);

class PACKAGE ArrayCamIPCReceiver : public dsl::IPCReceiver
{
    public:
						        		ArrayCamIPCReceiver(int portNr = -1, int socket_handle = -1, dsl::IPCServer* server = NULL);
						        		~ArrayCamIPCReceiver();
		virtual void                    Worker();

    protected:

};

#endif
