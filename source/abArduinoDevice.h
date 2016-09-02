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
    The original classes are extended and modified in order to allow for a
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

									//!Read state of an Arduino digital pin
		virtual bool	 			readDigitalPin(int pin);

									//!Set (write) the state of an Arduino digital output pin
		virtual bool	   			writeDigitalPin(int pin);

									//!Send custom message to the Arduino
        bool						send(const string& msg);

        							//!send an integer
        bool						send(int nr);

        							//!The init callback is designed to give an ArduinoDevice client a
                                    //!way to update its state on initialization
		InitCallBack				init;

    private:

    								//!Serial communication can be quite complex. It is wrapped by the Serial class
                                    //and confined to the SerialPort class
        Serial						mSerial;

									//!Threat the serial port as a resource that can only be accesed from
                                    //the outside by one client at a time
		Mutex						mSerialPortMutex;
        string						mName;

        							//A stream makes it easy to compose messages
        std::stringstream		  	mSS;
        int					        readSerialPort();
};

#endif