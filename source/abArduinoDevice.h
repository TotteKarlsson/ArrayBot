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
    The classes ArduinoDevide and Serial are based on classes
    found at: http://playground.arduino.cc/Interfacing/CPPWindows
    The original classes are extended to allow for a more robust serial communication
    mechanism, involving reading/writing on the serial port in a seperate thread.
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
        void		 				assignMessageReceivedCallBack(MessageReceivedCallBack cb);

		bool						connect(int portNr, int baudRate = 9600);
        bool 						isConnected();
        bool						disConnect();

		bool						postMessage(const string& msg);
        bool                        setPinMode(int pin, bool mode);
        bool						hasMessage();
		string						getMessage();

        							//Read
        int                         analogRead(int pin);
        bool                        digitalRead(int pin);

        							//Write
        bool                        analogWrite(int pin, int value);
        bool                        digitalWrite(int pin, bool value);
        bool						send(const string& msg);
		InitCallBack				init;

    private:
        Serial						mSerial;
        string						mName;


        							//A stream makes it easy to compose messages
        std::stringstream		  	mSS;

        int					        readSerialPort();

};

#endif