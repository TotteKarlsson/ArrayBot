#ifndef abSerialH
#define abSerialH
#include "abExporter.h"
#include "mtkStringList.h"
#include "mtkIPCMessageBuilder.h"
#include "Poco/Mutex.h"
#include "Poco/Condition.h"
#include "Serial.h"

using Poco::Mutex;
using Poco::Condition;

using mtk::StringList;
using mtk::IPCMessageBuilder;

class Serial;

class SerialWorker : public mtk::Thread
{
	public:
                                        SerialWorker(Serial& h, CSerial& s) : mTheHost(h), mSP(s), mMessageBuilder('[', ']'){}
        void			                run();
        Serial&			                mTheHost;
        CSerial&	 	                mSP;
	private:
    	IPCMessageBuilder				mMessageBuilder;
};

class AB_CORE Serial
{
	friend SerialWorker;
    public:
                                            //Initialize Serial communication with the given COM port
                                            Serial(int portNr, int rate = 9600);
                                            ~Serial();
        bool					            connect(int portNr, int baudRate);

        					                //Check if we are actually connected
        bool 				                isConnected();

                                            //Close the connection
        bool					            disConnect();

        									//!Client checks for messages
		bool					            hasMessage();

        									//!Retrieve message from internal queue
        string					            popMessage();

        									//!Post message to internal output queue
		bool								send(const string& msg);

    private:
        									//CSerial is doint the work
		CSerial								mSP;

        									//The serial worker reads/write data on the serial port
                                            //in a thread. Incoming messages are placed in the mMessages
                                            //list
        SerialWorker						mSerialWorker;

        bool								setupSerialPort(int pNr, int baudRate);


        						            //Messages from an arduino
		Mutex					            mReceivedMessagesMutex;
        StringList				            mReceivedMessages;

};

#endif