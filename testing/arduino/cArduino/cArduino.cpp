#include "cArduino.h"


ARDUINO::ARDUINO(char *comPort)
{
	SerialPort = new Serial(comPort);
	Buffer = new char[32];
	memset(Buffer, 0, sizeof(Buffer));

	inBuffer = new char[16];
	memset(inBuffer, 0, sizeof(inBuffer));
	echoMode = 0;
}

ARDUINO::~ARDUINO()
{
	delete SerialPort;
	delete [] Buffer;
	delete [] inBuffer;
}

bool ARDUINO::IsConnected()
{
	if(SerialPort->IsConnected())
	{
		ClearStream();
		A_Stream << "[!z]";
		std::string strng = A_Stream.str();
		Buffer = (char*)(strng.c_str());
		SerialPort->WriteData(Buffer, A_Stream.str().length());
		if(CatchEcho().val != 0)
		{
			return 1;
		}
	}
	return 0;
}

////////////////////////Echo Handling///////////////////////////////////////
A_ECHO ARDUINO::CatchEcho()
{
		ClearinBuffer();
		tempVal[0] = 0;
		tempVal[2] = 0;

		while(tempVal[0] < 1) // wait for available data
		{
		tempVal[0] = SerialPort->ReadData(inBuffer, tempVal[0]); //keep grabbing data availability
		}

		for(tempVal[1] = 0; tempVal[1] < tempVal[0]; tempVal[1]++) //Using tempVal[1] as an iterator from 0 to available bytes.
		{
			if(inBuffer[tempVal[1]] == '!') //if action found on current byte...
			{
				inBuffer[0] = inBuffer[tempVal[1] + 1]; //grab next byte and stick it in front.
			}
			if(inBuffer[tempVal[1]] == '(') //if opening bracked found on current byte...
			{
				tempVal[1]++;
				for(;( inBuffer[tempVal[1]] != ')' ) && tempVal[1] < tempVal[0]; tempVal[1]++ ) //...do this until closing bracket or end of data:
				{
					tempVal[2] = (inBuffer[tempVal[1]] - '0') + (tempVal[2] * 10); //Multiply the previous bytes by 10, and add current byte.
				}
			}
		}
		A_ECHO aEcho = {inBuffer[0], tempVal[2]};
		return aEcho;

}

void ARDUINO::PrintEcho(A_ECHO aEcho)
{
	std::cout << "Message: " << aEcho.msg << " Value: " << aEcho.val << std::endl;
}
////////////////////////////////Echo Handling///////////////////

////////////////////////////////Write/////////////////////////////

bool ARDUINO::pinMode(int pin, bool mode) //[!c(pin,value)]
{
	ClearStream();
	A_Stream << "[!a(" << pin << ",0" << mode << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());

	if(echoMode && CatchEcho().val)
		return 1;
	return 0;
}

bool ARDUINO::digitalWrite(int pin, bool value)
{
	ClearStream();
	A_Stream << "[!b(" << pin << "," << value << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());

	if(echoMode && CatchEcho().val)
		return 1;
	return 0;
}

bool ARDUINO::analogWrite(int pin, int value)
{
	ClearStream();
	A_Stream << "[!c(" << pin << "," << value << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());

	if(echoMode && CatchEcho().val)
		return 1;
	return 0;
}

void ARDUINO::SetEcho(bool mode)
{
	ClearStream();
	A_Stream << "[!y(" << mode << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());
	echoMode = mode;
}

///////////////////////////////////Write//////////////////

///////////////////////////////////Read///////////////////

bool ARDUINO::digitalRead(int pin)
{
	ClearStream();
	A_Stream << "[!d(" << pin  << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());
	A_ECHO echo = CatchEcho();
	if(echo.msg == 'D')
	{
		if(echo.val > 0)
			return 1;
	}
	return 0;
}

int ARDUINO::analogRead(int pin)
{
	ClearStream();
	A_Stream << "[!e(" << pin  << ")]";
	std::string strng = A_Stream.str();
	Buffer = (char*)(strng.c_str());
	SerialPort->WriteData(Buffer, A_Stream.str().length());
	A_ECHO echo = CatchEcho();
	if(echo.msg == 'E')
		return echo.val;
	return 0;
}


///////////////////////////////////Read///////////////////



void ARDUINO::ClearStream()
{
	A_Stream.clear();
	A_Stream.str("");
	memset(Buffer, 0, sizeof(Buffer));
	memset(inBuffer, NULL, sizeof(inBuffer));
	
}

void ARDUINO::ClearinBuffer()
{
  memset(inBuffer, NULL, sizeof(inBuffer));
}