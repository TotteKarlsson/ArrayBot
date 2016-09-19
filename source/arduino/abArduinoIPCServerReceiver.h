#ifndef abArduinoIPCServerReceiverH
#define abArduinoIPCServerReceiverH
#include "mtkIPCReceiver.h"
#include "mtkIPCServer.h"
#include "abExporter.h"
#include "abABObject.h"
//---------------------------------------------------------------------------

class AB_CORE ArduinoServerIPCReceiver : public mtk::IPCReceiver
{
    public:
						        		ArduinoServerIPCReceiver(int portNr = -1, int socket_handle = -1, mtk::IPCServer* server = NULL);
						        		~ArduinoServerIPCReceiver();
		virtual void                    Worker();

    protected:

};

#endif
