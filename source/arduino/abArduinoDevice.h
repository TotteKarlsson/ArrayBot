#ifndef abArduinoDeviceH
#define abArduinoDeviceH
#include "abExporter.h"
#include <sstream>
#include <iostream>
#include "Poco/Mutex.h"
#include "Poco/Condition.h"
#include "serial/abSerial.h"
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
    	virtual		    			~ArduinoDevice();

		void						setName(const string& name){mName = name;}
        string						getName(){return mName;}

        void		 				assignInitFunction(InitCallBack cb){init = cb;}
        void		 				assignSerialMessageReceivedCallBack(SerialMessageReceivedCallBack cb);

		bool						connect(int portNr, int baudRate = 9600);
        bool 						isConnected();
        bool						disConnect();

        bool						hasMessage();
		string						getMessage();

									//!Read state of an Arduino digital pin (not implemented)
		virtual bool	 			readDigitalPin(int pin);

									//!Set (write) the state of an Arduino digital output pin (not implemented)
		virtual bool	   			writeDigitalPin(int pin);

									//!Send custom message to the Arduino
        bool						send(const string& msg);

        							//!send an integer
        bool						send(int nr);

        							//!The init callback is designed to give an ArduinoDevice client a
                                    //!way to update its state on initialization
		InitCallBack				init;

    protected:
    								//!The arduino device name. Used in the INI file
        string						mName;

    								//!Serial communication can be quite complex. It is wrapped by the Serial class
                                    //and confined further with low level functions in the SerialPort class
        Serial						mSerial;

									//!Threat the serial port as a resource that can only be accesed from
                                    //the outside by one client at a time
		Mutex						mSerialPortMutex;

        							//A stream makes it easy to compose messages
        std::stringstream		  	mSS;

};

#endif