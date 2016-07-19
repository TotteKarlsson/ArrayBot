#ifndef H_ARDUINO
#define H_ARDUINO

#include "SerialClass.h"
#include <sstream>
#include <iostream>

#define PIN_MODE_INPUT 1
#define PIN_MODE_OUTPUT 0

struct A_ECHO
{
	char msg;
	int val;
};

class ARDUINO
{
public:
	ARDUINO(char* comPort);
	~ARDUINO();
	bool IsConnected();

	//Write
	bool pinMode(int pin, bool mode);
	void SetEcho(bool mode);
	bool analogWrite(int pin, int value);
	bool digitalWrite(int pin, bool value);

	//Read
	int analogRead(int pin);
	bool digitalRead(int pin);
	
private:
	Serial* SerialPort;

	//Buffers and Temps
	
	char *Buffer;
	char *inBuffer;
	int tempVal[10];
	std::stringstream A_Stream;

	//Echo Handling
	A_ECHO CatchEcho();
	int echoMode;
	void PrintEcho(A_ECHO aEcho);

	//Cleanup
	void ClearStream();
	void ClearinBuffer();
};



#endif