#ifndef abArduinoServerH
#define abArduinoServerH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "mtkIPCServer.h"
#include "mtkSocketWorker.h"
#include "abPufferArduino.h"
#include "abLightsArduino.h"
#include <vector>
#include "mtkTimer.h"
#include "abRibbonController.h"
using mtk::IPCServer;
using mtk::IPCMessage;
using std::vector;

mtk::SocketWorker* AB_CORE createArduinoIPCReceiver(int portNr, int socketHandle, void* parent);

typedef void (__closure *OnMessageUpdateCB)(const string& msg);

//!The Arduino server is a component that serve clients with Arduino connections over a
//tcp/ip socket. The Arraybot Arduino server is designed to handle messages and data related to the
//arraybot project. The Arduino server is a descendant of the IPC server class that is implementing all
//network functionality.
//The Arduino server forwards any messages sent from the arduino board to any connected tcp/ip clients.

//There are currently two Arduino boards, the 'Puffer' board, and a 'Sensor' board containing sensors and
//light controlling logic.

class AB_CORE ArduinoServer : public IPCServer
{
	friend RibbonController;
    public:
                                            ArduinoServer(int portNumber = 50000);
	                                        ~ArduinoServer();

                                            //!The process message is an overide from the IPCServer base class.
                                            //!Process message implements arduino server specific processing.
                                            //!Messages sent to the server from a client are processed.
    	bool 					            processMessage(IPCMessage& msg);

    	PufferArduino& 			            getPufferArduino(){return mPufferArduino;}
    	LightsArduino& 			            getSensorArduino(){return mLightsArduino;}
        bool            		            shutDown();

		void        						enableAutoPuff();
		void        						disableAutoPuff();

		void        						enableAutoZeroCut();
		void        						disableAutoZeroCut();
        bool								setZeroCut();


        void								assignOnUpdateCallBack(OnMessageUpdateCB cb);
		void								onUpdateClientsTimer();
        void								broadcastStatus();

    protected:
    							            //!Container for Arduino devices
		vector<ArduinoDevice*> 	            mArduinos;

        									//We should create a mutex for each of these
                                            //devices...
    	PufferArduino 			            mPufferArduino;
    	LightsArduino 			            mLightsArduino;

		RibbonController				mRibbonController;

        OnMessageUpdateCB					onMessageUpdateCB;

		void					            pufferMessageReceived(const string& msg);
		void					            sensorMessageReceived(const string& msg);
        void								notifyClients(const string& msg);
};

#endif
