#include "abArduinoDevice.h"


ArduinoDevice::ArduinoDevice(char *comPort)
{
	mSerialPort = new Serial(comPort);
	mBuffer = new char[32];
	memset(mBuffer, 0, sizeof(mBuffer));

	mInBuffer = new char[16];
	memset(mInBuffer, 0, sizeof(mInBuffer));
	mEchoMode = 0;
}

ArduinoDevice::~ArduinoDevice()
{
	delete mSerialPort;
	delete [] mBuffer;
	delete [] mInBuffer;
}

bool ArduinoDevice::isConnected()
{
	if(mSerialPort->IsConnected())
	{
		clearStream();
		mStream << "[!z]";
		std::string strng = mStream.str();
		mBuffer = (char*)(strng.c_str());
		mSerialPort->WriteData(mBuffer, mStream.str().length());
		if(catchEcho().val != 0)
		{
			return 1;
		}
	}
	return 0;
}

////////////////////////Echo Handling///////////////////////////////////////
A_ECHO ArduinoDevice::catchEcho()
{
		clearInBuffer();
		tempVal[0] = 0;
		tempVal[2] = 0;

		while(tempVal[0] < 1) // wait for available data
		{
		tempVal[0] = mSerialPort->ReadData(mInBuffer, tempVal[0]); //keep grabbing data availability
		}

		for(tempVal[1] = 0; tempVal[1] < tempVal[0]; tempVal[1]++) //Using tempVal[1] as an iterator from 0 to available bytes.
		{
			if(mInBuffer[tempVal[1]] == '!') //if action found on current byte...
			{
				mInBuffer[0] = mInBuffer[tempVal[1] + 1]; //grab next byte and stick it in front.
			}
			if(mInBuffer[tempVal[1]] == '(') //if opening bracked found on current byte...
			{
				tempVal[1]++;
				for(;( mInBuffer[tempVal[1]] != ')' ) && tempVal[1] < tempVal[0]; tempVal[1]++ ) //...do this until closing bracket or end of data:
				{
					tempVal[2] = (mInBuffer[tempVal[1]] - '0') + (tempVal[2] * 10); //Multiply the previous bytes by 10, and add current byte.
				}
			}
		}
		A_ECHO aEcho = {mInBuffer[0], tempVal[2]};
		return aEcho;

}

void ArduinoDevice::printEcho(A_ECHO aEcho)
{
	std::cout << "Message: " << aEcho.msg << " Value: " << aEcho.val << std::endl;
}
////////////////////////////////Echo Handling///////////////////

////////////////////////////////Write/////////////////////////////

bool ArduinoDevice::pinMode(int pin, bool mode) //[!c(pin,value)]
{
	clearStream();
	mStream << "[!a(" << pin << ",0" << mode << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());

	if(mEchoMode && catchEcho().val)
		return 1;
	return 0;
}

bool ArduinoDevice::digitalWrite(int pin, bool value)
{
	clearStream();
	mStream << "[!b(" << pin << "," << value << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());

	if(mEchoMode && catchEcho().val)
		return 1;
	return 0;
}

bool ArduinoDevice::analogWrite(int pin, int value)
{
	clearStream();
	mStream << "[!c(" << pin << "," << value << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());

	if(mEchoMode && catchEcho().val)
		return 1;
	return 0;
}

void ArduinoDevice::setEcho(bool mode)
{
	clearStream();
	mStream << "[!y(" << mode << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());
	mEchoMode = mode;
}

bool ArduinoDevice::digitalRead(int pin)
{
	clearStream();
	mStream << "[!d(" << pin  << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());
	A_ECHO echo = catchEcho();
	if(echo.msg == 'D')
	{
		if(echo.val > 0)
			return 1;
	}
	return 0;
}

int ArduinoDevice::analogRead(int pin)
{
	clearStream();
	mStream << "[!e(" << pin  << ")]";
	std::string strng = mStream.str();
	mBuffer = (char*)(strng.c_str());
	mSerialPort->WriteData(mBuffer, mStream.str().length());
	A_ECHO echo = catchEcho();
	if(echo.msg == 'E')
		return echo.val;
	return 0;
}


///////////////////////////////////Read///////////////////



void ArduinoDevice::clearStream()
{
	mStream.clear();
	mStream.str("");
	memset(mBuffer, 0, sizeof(mBuffer));
	memset(mInBuffer, NULL, sizeof(mInBuffer));

}

void ArduinoDevice::clearInBuffer()
{
  memset(mInBuffer, NULL, sizeof(mInBuffer));
}