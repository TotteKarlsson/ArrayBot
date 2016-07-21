#ifndef abArduinoServerH
#define abArduinoServerH
//---------------------------------------------------------------------------
//!An arduino server is a component that serve clients with Arduino connections over
//tcp/ip. The arraybot arduino server is designed to handle messages and data related to the
//arraybot project. The Arduino server is a descendant of the IPC server class, implementing all
//network functionality

#include "abExporter.h"
#include "abABObject.h"
#include "mtkIPCServer.h"
#include "mtkSocketWorker.h"


using mtk::IPCServer;
using mtk::IPCMessage;

mtk::SocketWorker* AB_CORE createArduinoIPCReceiver(int portNr, int socketHandle, void* parent);
//---------------------------------------------------------------------------
class AB_CORE ArduinoServer : public IPCServer
{
    public:
                                ArduinoServer(int portNumber = 50000);
	                            ~ArduinoServer();

                                //!The process message is an overirde from the base class.
                                //Process message implements arduino server specific processing
    bool 						processMessage(IPCMessage& msg);

    protected:

};

#endif
