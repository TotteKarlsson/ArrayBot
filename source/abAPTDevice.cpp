#pragma hdrstop
#include "abAPTDevice.h"
//---------------------------------------------------------------------------


APTDevice::APTDevice(int serial)
:
mSerial(toString(serial)),
mIsConnected(false)
{}

APTDevice::~APTDevice()
{}

string APTDevice::getSerial()
{
	return mSerial.getValue();
}
bool APTDevice::isConnected()
{
	return mIsConnected;
}


