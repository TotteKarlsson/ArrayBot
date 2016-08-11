#ifndef abSerialH
#define abSerialH
#include "abExporter.h"
#include "abABObject.h"
#include "mtkStringList.h"
#include "Poco/Mutex.h"
#include "Poco/Condition.h"
#include "abSerialPort.h"
#include "abSerialWorker.h"

using Poco::Mutex;
using Poco::Condition;

using mtk::StringList;
using mtk::IPCMessageBuilder;

typedef void (*SerialMessageReceivedCallBackC)(const string& msg);
typedef void (__closure *SerialMessageReceivedCallBack)(const string& msg);

class AB_CORE Serial : public ABObject
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

        void								assignMessageReceivedCallBackC(SerialMessageReceivedCallBackC cb);
        void								assignMessageReceivedCallBack(SerialMessageReceivedCallBack cb);

    private:
        									//CSerial is doing the underlying serial port work
		SerialPort							mSP;

        									//The serial worker reads data on the serial port
                                            //in a thread. Incoming messages are placed in the mMessages
                                            //list
        SerialWorker						mSerialWorker;
        bool								setupAndOpenSerialPort(int pNr, int baudRate);

        						            //Messages from an arduino
		Mutex					            mReceivedMessagesMutex;

        									//!Messages are stored in a list of strings and consumed
                                            //by the Arduino server
        StringList				            mReceivedMessages;

        SerialMessageReceivedCallBack	 	mReceivedCB;
        Poco::Condition                     mGotMessage;
};

#endif