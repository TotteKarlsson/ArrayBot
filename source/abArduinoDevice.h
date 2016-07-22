#ifndef abArduinoDeviceH
#define abArduinoDeviceH
#include "abExporter.h"
#include "abSerial.h"
#include <sstream>
#include <iostream>

/*
    The classes ArduinoDevide and Serial are based on classes
    found at: http://playground.arduino.cc/Interfacing/CPPWindows
    The original classes are extended to allow for a more robust serial communication
    mechanism, involving serial port reading/writing in a seperate thread.
*/

#define PIN_MODE_INPUT 	1
#define PIN_MODE_OUTPUT 0

struct A_ECHO
{
	char msg;
	int val;
};

class AB_CORE ArduinoDevice
{
    public:
        							ArduinoDevice(int pNr);
    								~ArduinoDevice();
        bool 						isConnected();

        //Write
        bool                        pinMode(int pin, bool mode);
        void                        setEcho(bool mode);
        bool                        analogWrite(int pin, int value);
        bool                        digitalWrite(int pin, bool value);

        //Read
        int                         analogRead(int pin);
        bool                        digitalRead(int pin);

    private:
        Serial* 					mSerialPort;

        //Buffers and Temps
        char*                       mBuffer;
        char*                       mInBuffer;
        int 						tempVal[10];
        std::stringstream 			mStream;

        //Echo Handling
        A_ECHO 						catchEcho();
        int 						mEchoMode;
        void 						printEcho(A_ECHO aEcho);

        //Cleanup
        void                        clearStream();
        void                        clearInBuffer();
};

#endif