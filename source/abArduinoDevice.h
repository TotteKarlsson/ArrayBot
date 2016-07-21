#ifndef abArduinoDeviceH
#define abArduinoDeviceH
#include "abExporter.h"
#include "abSerial.h"
#include <sstream>
#include <iostream>

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
        							ArduinoDevice(char* comPort);
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