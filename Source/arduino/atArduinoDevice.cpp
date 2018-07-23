#pragma hdrstop
#include "atArduinoDevice.h"
#include "dslWin32Utils.h"
#include "dslLogger.h"
#include "Poco/Mutex.h"
using namespace dsl;

namespace at
{
    ArduinoDevice::ArduinoDevice(int pNr, int baudRate)
    :
    mSerial(pNr, baudRate),
    mMessageSender(*this),
    initCallBack(NULL)
    {}

    ArduinoDevice::~ArduinoDevice()
    {
    	mSerial.assignMessageReceivedCallBack(NULL);
        mSerial.disConnect();
    }

    bool ArduinoDevice::connect(int portNr, int baudRate)
    {
        mMessageSender.start();
    	bool cRes = mSerial.connect(portNr, baudRate);
        if(cRes && initCallBack)
        {
    		initCallBack();
        }
        return cRes;
    }

    void ArduinoDevice::assignInitFunction(InitCallBack cb)
    {
    	initCallBack = cb;
    }

    bool ArduinoDevice::isConnected()
    {
    	return mSerial.isConnected() || mMessageSender.isAlive();
    }

    bool ArduinoDevice::disConnect()
    {
    	mMessageSender.stop();
    	return mSerial.disConnect();
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
    	return send(dsl::toString(val));
    }

    bool ArduinoDevice::send(const string& msg)
    {
    	//Put the message on the utgoing queue
        {
            Poco::ScopedLock<Poco::Mutex> lock(mSendBufferMutex);
        	mOutgoingMessagesBuffer.push_back(msg);
        }

        //Send a signal
        mNewMessageToSendCondition.signal();
    	return true;
    }

    void ArduinoDevice::assignSerialMessageReceivedCallBack(SerialMessageReceivedCallBack cb)
    {
    	mSerial.assignMessageReceivedCallBack(cb);
    }

    bool ArduinoDevice::hasMessage()
    {
    	return mSerial.hasMessage();
    }

    string ArduinoDevice::getMessage()
    {
    	return mSerial.popMessage();
    }
}
