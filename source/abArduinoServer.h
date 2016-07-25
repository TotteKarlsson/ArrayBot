#ifndef abArduinoServerH
#define abArduinoServerH
//---------------------------------------------------------------------------
//!An arduino server is a component that serve clients with Arduino connections over
//tcp/ip. The arraybot arduino server is designed to handle messages and data related to the
//arraybot project. The Arduino server is a descendant of the IPC server class, implementing all
//network functionality.
//In short, an arduino server forwards any messages sent from the arduino board to any connected tcp/ip clients

#include "abExporter.h"
#include "abABObject.h"
#include "mtkIPCServer.h"
#include "mtkSocketWorker.h"
#include "abArduinoDevice.h"
#include <vector>

using mtk::IPCServer;
using mtk::IPCMessage;
using std::vector;

mtk::SocketWorker* AB_CORE createArduinoIPCReceiver(int portNr, int socketHandle, void* parent);
//---------------------------------------------------------------------------
class AB_CORE ArduinoServer : public IPCServer
{
    public:
                                ArduinoServer(int portNumber = 50000);
	                            ~ArduinoServer();

                                //!The process message is an overirde from the base class.
                                //Process message implements arduino server specific processing
    	bool 					processMessage(IPCMessage& msg);

    	ArduinoDevice& 			getArduinoDevice(int dev);
        bool            		shutDown();


    protected:
    							//!Arduino Devices
		vector<ArduinoDevice*> 	mArduinos;
    	ArduinoDevice 			mA1;
		void					messageReceived(const string& msg);


};

#endif
