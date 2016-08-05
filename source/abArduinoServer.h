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
#include "mtkTimer.h"


using mtk::IPCServer;
using mtk::IPCMessage;
using std::vector;

mtk::SocketWorker* AB_CORE createArduinoIPCReceiver(int portNr, int socketHandle, void* parent);

typedef void (__closure *OnMessageUpdateCB)(const string& msg);
//---------------------------------------------------------------------------
class AB_CORE ArduinoServer : public IPCServer
{
    public:
                                            ArduinoServer(int portNumber = 50000);
	                                        ~ArduinoServer();

                                            //!The process message is an overide from the base class.
                                            //!Process message implements arduino server specific processing.
                                            //!Messages sent to the server from a client are processed.
    	bool 					            processMessage(IPCMessage& msg);

    	ArduinoDevice& 			            getPufferArduino(){return mPufferArduino;}
    	ArduinoDevice& 			            getSensorArduino(){return mSensorArduino;}
        bool            		            shutDown();

		void        						enableAutoPuff();
		void        						disableAutoPuff();
        bool					            puff();

		bool								toggleLED();
		bool								toggleCoax();


        void					            incrementSectionCount(){mSectionCount++;}
        int						            getSectionCount(){return mSectionCount;}
        void					            resetSectionCount();
		void								setPuffAfterSectionCount(int val);
        void								assignOnUpdateCallBack(OnMessageUpdateCB cb){onMessageUpdateCB = cb;}
		void								onUpdateClientsTimer();
        void								broadcastStatus();

    protected:
    							            //!Arduino Devices
		vector<ArduinoDevice*> 	            mArduinos;
    	ArduinoDevice 			            mPufferArduino;
    	ArduinoDevice 			            mSensorArduino;
        OnMessageUpdateCB					onMessageUpdateCB;

        int						            mSectionCount;
        int									mPuffAfterSectionCount;
        bool								mAutoPuff;
		void					            pufferMessageReceived(const string& msg);
		void					            sensorMessageReceived(const string& msg);
        void								updateClients(const string msg);
};

#endif
