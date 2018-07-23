#ifndef atArduinoServerH
#define atArduinoServerH
#include "atCoreExporter.h"
#include "atATObject.h"
#include "dslIPCServer.h"
#include "dslSocketWorker.h"
#include "atLightsArduino.h"
#include "atSensorsArduino.h"
#include <vector>
#include "dslTimer.h"
//---------------------------------------------------------------------------

using dsl::IPCServer;
using dsl::IPCMessage;
using std::vector;



typedef void (__closure *OnMessageUpdateCB)(const string& msg);

//!The Arduino server is a component that serve clients with Arduino connections over a
//tcp/ip socket. The Arduino server is designed to handle messages and data related to the
//arraybot project. The Arduino server is a descendant of the IPC server class that is implementing all
//network functionality.
//The Arduino server forwards any messages sent from the arduino board to any connected tcp/ip clients.

namespace at
{
	dsl::SocketWorker* AT_ARDUINO createArduinoIPCReceiver(int portNr, int socketHandle, void* parent);

    class AT_ARDUINO ArduinoServer : public IPCServer, public ATObject
    {
        public:
                                                ArduinoServer(int portNumber = 50000);
    	                                        ~ArduinoServer();

                                                //!The process request is an overide from the IPCServer base class.
                                                //!ProcessRequest implements the arduino server specific processing.
                                                //!Requests are sent to the server from a client.
        	bool 					            processRequest(IPCMessage& msg);
        	LightsArduino& 			            getLightsArduino(){return mLightsArduino;}

            bool            		            shutDown();
            void								assignOnUpdateCallBack(OnMessageUpdateCB cb);
    		void								onUpdateClientsTimer();
            void								broadcastStatus();

        protected:
        							            //!Container for Arduino devices
    		vector<ArduinoDevice*> 	            mArduinos;

            									//We should create a mutex for device..
        	LightsArduino 			            mLightsArduino;

            OnMessageUpdateCB					onMessageUpdateCB;

    		void					            lightsArduinoMessageReceived(const string& msg);
            void								notifyClients(const string& msg);
    };
}

#endif
