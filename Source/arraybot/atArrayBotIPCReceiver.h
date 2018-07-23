#ifndef atArrayBotIPCReceiverH
#define atArrayBotIPCReceiverH
#include "dslIPCReceiver.h"
#include "dslIPCServer.h"
#include "arraybot/atABExporter.h"
//---------------------------------------------------------------------------

using dsl::SocketWorker;
SocketWorker* AT_AB createArrayBotIPCReceiver(int portNr, int socketHandle, void* server);

class AT_AB ArrayBotIPCReceiver : public dsl::IPCReceiver
{
    public:
						        		ArrayBotIPCReceiver(int portNr = -1, int socket_handle = -1, dsl::IPCServer* server = NULL);
						        		~ArrayBotIPCReceiver();
		virtual void                    Worker();

    protected:

};

#endif
