#pragma hdrstop
#include "abArduinoDevice.h"
#include "mtkWin32Utils.h"
#include "mtkLogger.h"


using namespace mtk;

ArduinoDevice::ArduinoDevice(int pNr, int baudRate)
:
mSerial(4,9600)
{
}

ArduinoDevice::~ArduinoDevice()
{}


bool ArduinoDevice::isConnected()
{
	return false;
}

bool ArduinoDevice::disConnect()
{
	return false;
}

bool ArduinoDevice::hasMessage()
{
//	return mSP.hasMessage();
	return false;
}

string ArduinoDevice::getMessage()
{
//	return mSP.popMessage();
}

bool ArduinoDevice::setPinMode(int pin, bool mode)
{
	mSS.str("");

	mSS << "[!a(" << pin << ",0" << mode << ")]";
//	return mSP.postMessage(mSS.str());
}

bool ArduinoDevice::digitalWrite(int pin, bool value)
{
	mSS.str("");
	mSS << "[!b(" << pin << "," << value << ")]";
//	return mSP.postMessage(mSS.str());
}

bool ArduinoDevice::analogWrite(int pin, int value)
{
	mSS.str("");
	mSS << "[!c(" << pin << "," << value << ")]";
//	return mSP.postMessage(mSS.str());
}

bool ArduinoDevice::digitalRead(int pin)
{
	mSS.str("");
	mSS << "[!d(" << pin  << ")]";
//	return mSP.postMessage(mSS.str());
}

int ArduinoDevice::analogRead(int pin)
{
	mSS.str("");
	mSS << "[!e(" << pin  << ")]";
//	return mSP.postMessage(mSS.str());
}

