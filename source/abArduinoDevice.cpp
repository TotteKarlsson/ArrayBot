#pragma hdrstop
#include "abArduinoDevice.h"
#include "mtkWin32Utils.h"
#include "mtkLogger.h"


using namespace mtk;

ArduinoDevice::ArduinoDevice(int pNr, int baudRate)
:
mSerial(pNr, baudRate)
{}

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


