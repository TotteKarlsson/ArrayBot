#pragma hdrstop
#include "abSerial.h"
#include "mtkUtils.h"
#include "mtkWin32Utils.h"

using namespace mtk;

Serial::Serial(int portNr, int baudRate)
:
mSP(),
mSerialWorker(*this, mSP),
mReceivedCB(NULL)
{
    if(portNr != -1)
    {
    	connect(portNr, baudRate);
    }
}

Serial::~Serial()
{
	mSerialWorker.stop();
}

bool Serial::connect(int pNr, int baudRate)
{
    if(setupAndOpenSerialPort(pNr, baudRate))
    {
        Log(lInfo) <<"Connected to COM port: " <<pNr<<" using BaudRate: "<<baudRate;

        //Start serving serial port...
        mSerialWorker.start(true);
    }
    else
    {
        Log(lError) <<"Failed opening serial port: "<<pNr<<" using baudrate: "<<baudRate;
        return false;
    }

	return true;
}

bool Serial::send(const string& msg)
{
	OVERLAPPED osWrite = {0};
   	DWORD dwWritten;
	Log(lDebug5) << "Sending serial message: "<<msg;

   	// Create this write operation's OVERLAPPED structure's hEvent.
   	osWrite.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
   	if (osWrite.hEvent == NULL)
    {
      	// error creating overlapped event handle
    	Log(lError) << "Failed to create overlapped Event handle";
      	return false;
    }

	int error = mSP.Write(msg.c_str(), msg.size(), &dwWritten, &osWrite);
    if(error)
    {
    	Log(lError) << "Failed to send over Serial Port..";
        return false;
    }
	return true;
}

string Serial::popMessage()
{
    {
        Poco::ScopedLock<Poco::Mutex> lock(mReceivedMessagesMutex);
		return mReceivedMessages.size() ? mReceivedMessages.popBack() : string("");
    }
}

void Serial::assignMessageReceivedCallBack(SerialMessageReceivedCallBack cb)
{
	mReceivedCB = cb;
}

bool Serial::setupAndOpenSerialPort(int pNr, int baudRate)
{
	LONG    lLastError = ERROR_SUCCESS;
    string portNr("COM" + toString(pNr));
    lLastError = mSP.Open(_T(portNr.c_str()),0,0,true);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to open COM-port";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

    // Setup the mSP port (9600,8N1, which is the default setting)
    lLastError = mSP.Setup((SerialPort::EBaudrate) baudRate, SerialPort::EData8, SerialPort::EParNone, SerialPort::EStop1);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup serial port";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

	// Setup handshaking (default is no handshaking)
    lLastError = mSP.SetupHandshaking(SerialPort::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup HandShaking";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

    // Register only for the receive event
    lLastError = mSP.SetMask(SerialPort::EEventBreak 	|
								SerialPort::EEventCTS   |
								SerialPort::EEventDSR   |
								SerialPort::EEventError |
								SerialPort::EEventRing  |
								SerialPort::EEventRLSD  |
								SerialPort::EEventRecv);

	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to set mask setting";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

	// Use 'non-blocking' reads, because we don't know how many bytes
	// will be received. This is normally the most convenient mode
	// (and also the default mode for reading data).
    lLastError = mSP.SetupReadTimeouts(SerialPort::EReadTimeoutNonblocking);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup Read timeouts";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

    return true;
}

bool Serial::disConnect()
{
    //Then the serial port itself
	mSP.Close();

	//First stop the worker
	mSerialWorker.stop();

    return true;
}

bool Serial::hasMessage()
{
	{
        Poco::ScopedLock<Poco::Mutex> lock(mReceivedMessagesMutex);
		return mReceivedMessages.size() ? true : false;
    }
}

bool Serial::isConnected()
{
    return mSP.IsOpen();
}


