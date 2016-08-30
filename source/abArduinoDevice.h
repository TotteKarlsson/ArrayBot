#ifndef abArduinoDeviceH
#define abArduinoDeviceH
#include "abExporter.h"
#include <sstream>
#include <iostream>
#include "Poco/Mutex.h"
#include "Poco/Condition.h"
#include "abSerial.h"
using Poco::Mutex;
using Poco::Condition;

using mtk::StringList;

/*
    The ArduinoDevice and Serial classes are based on classes
    found at: http://playground.arduino.cc/Interfacing/CPPWindows
    The original classes are extended and modified in order to allow for a more
    robust serial communication mechanism, involving reading/writing on the serial
    port in a seperate thread.
*/

typedef void (__closure *InitCallBack)();

class AB_CORE ArduinoDevice : public ABObject
{
    public:
        							ArduinoDevice(int portNr, int baudRate = 9600);
    								~ArduinoDevice();

		void						setName(const string& name){mName = name;}
        string						getName(){return mName;}

        void		 				assignInitFunction(InitCallBack cb){init = cb;}
        void		 				assignSerialMessageReceivedCallBack(SerialMessageReceivedCallBack cb);

		bool						connect(int portNr, int baudRate = 9600);
        bool 						isConnected();
        bool						disConnect();

        bool						hasMessage();
		string						getMessage();

        bool						send(const string& msg);
        bool						send(int val);
		InitCallBack				init;

    private:
    								//!Serial communication can be quite complex. It is wrapped by the Serial class
                                    //and confined to the SerialPort class
        Serial						mSerial;
        string						mName;

        							//A stream makes it easy to compose messages
        std::stringstream		  	mSS;
        int					        readSerialPort();
};

#endif