#ifndef atArduinoDeviceH
#define atArduinoDeviceH
#include "atCoreExporter.h"
#include <sstream>
#include <iostream>
#include "Poco/Mutex.h"
#include "Poco/Condition.h"
#include "serial/atSerial.h"
#include <deque>
#include "atArduinoSerialMessageSender.h"
#include "dslStringList.h"

using Poco::Mutex;
using Poco::Condition;
using std::deque;
using dsl::StringList;

/*
    The ArduinoDevice and Serial classes are based on classes
    found at: http://playground.arduino.cc/Interfacing/CPPWindows
    The original classes are extended and modified in order to allow for a
    robust serial communication mechanism, involving reading/writing on the serial
    port in a seperate thread.
*/

typedef void (__closure *InitCallBack)();
typedef void (__closure *SerialMessageReceivedCallBack)(const string& msg);

namespace at
{
    class AT_ARDUINO ArduinoDevice : public ATObject
    {
    	friend ArduinoSerialMessageSender;
        public:
            							ArduinoDevice(int portNr, int baudRate = 9600);
        	virtual		    			~ArduinoDevice();

    		void						setName(const string& name){mName = name;}
            string						getName(){return mName;}

            void		 				assignInitFunction(InitCallBack cb);
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
    		InitCallBack				initCallBack;

        protected:
        								//!The arduino device name. Used in the INI file
            string						mName;

        								//!Serial communication can be quite complex. It is wrapped by the Serial class
                                        //and confined further with low level functions in the SerialPort class
            Serial						mSerial;


            deque<string> 				mIncomingMessagesBuffer;
            Poco::Mutex		  			mReceiveBufferMutex;
            Poco::Condition	  			mNewReceivedMessageCondition;

            ArduinoSerialMessageSender 	mMessageSender;
    		deque<string>  	  			mOutgoingMessagesBuffer;
            Poco::Mutex		  			mSendBufferMutex;
            Poco::Condition	  			mNewMessageToSendCondition;

            							//A stream makes it easy to compose messages
            std::stringstream		  	mSS;

    };
}

#endif