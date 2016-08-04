#pragma hdrstop
#include "abArduinoDevice.h"
#include "mtkWin32Utils.h"
#include "mtkLogger.h"


using namespace mtk;

ArduinoDevice::ArduinoDevice(int pNr, int baudRate)
:
mSerial(pNr, baudRate)
{
}

ArduinoDevice::~ArduinoDevice()
{}

bool ArduinoDevice::connect(int portNr, int baudRate)
{
	return mSerial.connect(portNr, baudRate);
}

bool ArduinoDevice::send(const string& msg)
{
	return mSerial.send(msg);
}

void ArduinoDevice::assignSerialMessageReceivedCallBack(SerialMessageReceivedCallBack cb)
{
	mSerial.assignMessageReceivedCallBack(cb);
}


bool ArduinoDevice::isConnected()
{
	return mSerial.isConnected();
}

bool ArduinoDevice::disConnect()
{
	return mSerial.disConnect();
}

bool ArduinoDevice::hasMessage()
{
	return mSerial.hasMessage();
}

string ArduinoDevice::getMessage()
{
	return mSerial.popMessage();
}

//bool ArduinoDevice::setPinMode(int pin, bool mode)
//{
//	mSS.str("");
//
//	mSS << "[!a(" << pin << ",0" << mode << ")]";
////	return mSP.postMessage(mSS.str());
//	return false;
//}
//
//bool ArduinoDevice::digitalWrite(int pin, bool value)
//{
//	mSS.str("");
//	mSS << "[!b(" << pin << "," << value << ")]";
////	return mSP.postMessage(mSS.str());
//	return false;
//}
//
//bool ArduinoDevice::analogWrite(int pin, int value)
//{
//	mSS.str("");
//	mSS << "[!c(" << pin << "," << value << ")]";
////	return mSP.postMessage(mSS.str());
//	return false;
//}
//
//bool ArduinoDevice::digitalRead(int pin)
//{
//	mSS.str("");
//	mSS << "[!d(" << pin  << ")]";
////	return mSP.postMessage(mSS.str());
//	return false;
//}
//
//int ArduinoDevice::analogRead(int pin)
//{
//	mSS.str("");
//	mSS << "[!e(" << pin  << ")]";
////	return mSP.postMessage(mSS.str());
//	return false;
//}

