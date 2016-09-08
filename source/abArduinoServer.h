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
//
//There are currently two Arduino boards, the 'Puffer' board, and a 'Sensor' board containing sensors and
//light controlling logic.

class AB_CORE ArduinoServer : public IPCServer
{
    public:
                                            ArduinoServer(int portNumber = 50000);
	                                        ~ArduinoServer();

                                            //!The process message is an overide from the base class.
                                            //!Process message implements arduino server specific processing.
                                            //!Messages sent to the server from a client are processed.
    	bool 					            processMessage(IPCMessage& msg);

    	PufferArduino& 			            getPufferArduino(){return mPufferArduino;}
    	LightsArduino& 			            getSensorArduino(){return mLightsArduino;}
        bool            		            shutDown();

		bool        						enablePuffer();
		void        						enableAutoPuff();
		void        						disableAutoPuff();
        bool					            puff();

		void        						enableAutoZeroCut();
		void        						disableAutoZeroCut();
        bool								setZeroCut();

		bool								toggleLED();
        bool								turnLEDLightOn();
        bool								turnLEDLightOff();

		bool								toggleCoax();
        bool								turnCoaxLightOn();
        bool								turnCoaxLightOff();

        void					            incrementSectionCount(){mSectionCount++;}
        int						            getSectionCount(){return mSectionCount;}
        void					            resetSectionCount();
		void								setPuffAfterSectionCount(int val);
        void								assignOnUpdateCallBack(OnMessageUpdateCB cb){onMessageUpdateCB = cb;}
		void								onUpdateClientsTimer();
        void								broadcastStatus();

    protected:
    							            //!Container for Arduino devices
		vector<ArduinoDevice*> 	            mArduinos;

        									//We need to create a mutex for each of these
                                            //devices...
    	PufferArduino 			            mPufferArduino;
    	LightsArduino 			            mLightsArduino;

        									//!ArduinoLines
		int 								mLEDLightONLine;
		int									mLEDLightOFFLine;

		int 								mCoaxLightONLine;
		int									mCoaxLightOFFLine;

        OnMessageUpdateCB					onMessageUpdateCB;

									        //!The section count is compared to the mDesiredRibbonLength
                                            //used for emitting a puff
        int						            mSectionCount;

        int									mDesiredRibbonLength;
        bool								mAutoPuff;
        bool								mAutoZeroCut;
		void					            pufferMessageReceived(const string& msg);
		void					            sensorMessageReceived(const string& msg);
        void								updateClients(const string& msg);
};

#endif
