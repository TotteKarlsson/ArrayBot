#pragma hdrstop
#include "atSerial.h"
#include "dslUtils.h"
#include "dslWin32Utils.h"
#include "dslStringUtils.h"
#include "dslLogger.h"

using namespace dsl;

namespace at
{
    Serial::Serial(int portNr, int baudRate, char ld, char rd, SerialPort::EHandshake handShake)
    :
    mSP(),
    mHandShake(handShake),
    mSerialWorker(*this, mSP, ld, rd),
    mReceivedCB(NULL),
    mOverLappedIO(true),
    mReceiveBufferSize(1024),
    mSendBufferSize(1024)
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
        if(setupAndOpenSerialPort(pNr, baudRate, mHandShake))
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

    bool Serial::setupAndOpenSerialPort(int pNr, int baudRate, SerialPort::EHandshake handShake)
    {
    	LONG    lLastError = ERROR_SUCCESS;
        string portNr;//("COM" + toString(pNr));
    	if(pNr > 10)
        {
        	portNr = "\\\\.\\COM" + dsl::toString(pNr);
        }
        else
        {
    	    portNr = "COM" + dsl::toString(pNr);
        }

        lLastError = mSP.Open( _T(portNr.c_str() ), mReceiveBufferSize, mSendBufferSize, mOverLappedIO);
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
    //    lLastError = mSP.SetupHandshaking(SerialPort::EHandshakeHardware);
        lLastError = mSP.SetupHandshaking(SerialPort::EHandshake::EHandshakeOff);
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

    bool Serial::send(const unsigned char b)
    {
    	OVERLAPPED osWrite = {0};
       	DWORD dwWritten;

        stringstream log;
        log << "Sending byte (hex): ";
    	log <<toHex(b);

    	Log(lDebug) << log.str();

       	// Create this write operation's OVERLAPPED structure's hEvent.
       	osWrite.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
       	if (osWrite.hEvent == NULL)
        {
          	// error creating overlapped event handle
        	Log(lError) << "Failed to create overlapped Event handle";
          	return false;
        }

        string m;
        m.push_back(b);

        LPCSTR buffer = m.c_str();

    	int error = mSP.Write(buffer, &dwWritten, &osWrite);
        if(error)
        {
        	Log(lError) << "Failed to send over Serial Port..";
            return false;
        }
    	return true;
    }

    bool Serial::send(const string& msg)
    {
    	OVERLAPPED osWrite = {0};
       	DWORD dwWritten;

    //    stringstream log;
    //    log << "Sending bytes (hex): ";
    //    for(int byte = 0; byte < msg.size(); byte++)
    //    {
    //		log << ""<<toHex(msg[byte])<<"";
    //        if(byte < msg.size() -1 )
    //        {
    //        	log <<" ";
    //        }
    //    }
    //
    //	Log(lDebug) << log.str();

        const char* buffer = msg.c_str();

       	// Create this write operation's OVERLAPPED structure's hEvent.
       	osWrite.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
       	if (osWrite.hEvent == NULL)
        {
          	// error creating overlapped event handle
        	Log(lError) << "Failed to create overlapped Event handle";
          	return false;
        }

    	int error = mSP.Write(buffer, msg.size(), &dwWritten, &osWrite, mOverLappedIO);
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

    void Serial::assignMessageReceivedCallBackC(SerialMessageReceivedCallBackC cb)
    {
    	mReceivedCB_C = cb;
    }

    void Serial::assignMessageReceivedCallBack(SerialMessageReceivedCallBack cb)
    {
    	mReceivedCB = cb;
    }

    bool Serial::disConnect()
    {
    	//First stop the worker
    	mSP.Close();
    	mSerialWorker.stop();

    	while(mSerialWorker.isAlive())
        {
        	Log(lInfo) << "closing..";
        }

        //Then the serial port itself
    	//mSP.Close();
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
}


