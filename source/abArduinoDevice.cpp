#pragma hdrstop
#include "abArduinoDevice.h"
#include "mtkWin32Utils.h"
#include "mtkLogger.h"
#include "Poco/Mutex.h"
using namespace mtk;

ArduinoDevice::ArduinoDevice(int pNr, int baudRate)
:
mSerial(pNr, baudRate)
{}

ArduinoDevice::~ArduinoDevice()
{
	mSerial.assignMessageReceivedCallBack(NULL);
    mSerial.disConnect();
}

bool ArduinoDevice::connect(int portNr, int baudRate)
{
	return mSerial.connect(portNr, baudRate);
}

bool ArduinoDevice::readDigitalPin(int pin)
{
	return false;
}

bool ArduinoDevice::writeDigitalPin(int pin)
{
	return false;
}

bool ArduinoDevice::send(int val)
{
	Poco::ScopedLock<Poco::Mutex> lock(mSerialPortMutex);
	return send(toString(val));
}

bool ArduinoDevice::send(const string& msg)
{
	Poco::ScopedLock<Poco::Mutex> lock(mSerialPortMutex);
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
