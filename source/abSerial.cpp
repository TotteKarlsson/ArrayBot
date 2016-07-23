#pragma hdrstop
#include "abSerial.h"
#include "mtkUtils.h"
#include "mtkWin32Utils.h"

using namespace mtk;

Serial::Serial(int portNr, int baudRate)
:
mSP(),
mSerialWorker(*this, mSP)
{
    if(setupSerialPort(portNr, baudRate))
    {
  		//Start serving serial port...
    	mSerialWorker.start(true);
    }
}

Serial::~Serial()
{}

bool Serial::setupSerialPort(int pNr, int baudRate)
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
    lLastError = mSP.Setup(baudRate, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup serial port";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

	// Setup handshaking (default is no handshaking)
    lLastError = mSP.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup HandShaking";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }

    // Register only for the receive event
    lLastError = mSP.SetMask(CSerial::EEventBreak |
								CSerial::EEventCTS   |
								CSerial::EEventDSR   |
								CSerial::EEventError |
								CSerial::EEventRing  |
								CSerial::EEventRLSD  |
								CSerial::EEventRecv);
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
    lLastError = mSP.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
	if (lLastError != ERROR_SUCCESS)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to setup Read timeouts";
        Log(lError) <<"Error was: "<<errorMsg;
        return false;
    }
}

bool Serial::connect(int portNr, int baudRate)
{


}

bool Serial::disConnect()
{
    return false;
}

bool Serial::hasMessage()
{
	{
        Poco::ScopedLock<Poco::Mutex> lock(mReceivedMessagesMutex);
		return mReceivedMessages.size() ? true : false;
    }
}

string Serial::popMessage()
{
    {
        Poco::ScopedLock<Poco::Mutex> lock(mReceivedMessagesMutex);
		return mReceivedMessages.size() ? mReceivedMessages.popFront() : string("");
    }
}

bool Serial::send(const string& msg)
{
	OVERLAPPED osWrite = {0};
   	DWORD dwWritten;
   	DWORD dwRes;
   	BOOL fRes;

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
    	Log(lError) << "Failed to send..";
        return false;
    }
	return true;
}

bool Serial::isConnected()
{
    return mSP.IsOpen();
}

void SerialWorker::run()
{
	Log(lInfo) << "Starting reading/writing serial port..";
 	if(!mTheHost.isConnected())
    {
		Log(lInfo) << "Serial port is not connected.";
    }


	// Create a handle for the overlapped operations
	HANDLE hevtOverlapped = ::CreateEventA(0,TRUE,FALSE,0);
	if (hevtOverlapped == 0)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to CreateEvent";
        Log(lError) <<"Error was: "<<errorMsg;
        return;
    }

	// Setup the overlapped structure
	OVERLAPPED ov = {0};
	ov.hEvent = hevtOverlapped;

	// Open the "STOP" handle
	HANDLE hevtStop = ::CreateEventA(0,TRUE,FALSE,_T("Overlapped_Stop_Event"));
	if (hevtStop == 0)
    {
        string errorMsg = getLastWin32Error();
        Log(lError) <<"Unable to CreateEvent";
        Log(lError) <<"Error was: "<<errorMsg;
    }


	while(!mIsTimeToDie)
    {
        // Keep reading data, until an EOF (CTRL-Z) has been received
        // Wait for an event
        LONG lLastError = mSP.WaitEvent(&ov);
        if (lLastError != ERROR_SUCCESS)
        {
            string errorMsg = getLastWin32Error();
            Log(lError) <<"Unable to wait for a COM-port event.";
            Log(lError) <<"Error was: "<<errorMsg;
        }

        // Setup array of handles in which we are interested
        HANDLE ahWait[2];
        ahWait[0] = hevtOverlapped;
        ahWait[1] = hevtStop;

        // Wait until something happens
        switch (::WaitForMultipleObjects(sizeof(ahWait)/sizeof(*ahWait),ahWait,FALSE,INFINITE))
        {
            case WAIT_OBJECT_0:
            {
                // Save event
                const CSerial::EEvent eEvent = mSP.GetEventType();

                // Handle break event
                if (eEvent & CSerial::EEventBreak)
                {
                    printf("\n### BREAK received ###\n");
                }

                // Handle CTS event
                if (eEvent & CSerial::EEventCTS)
                {
                    printf("\n### Clear to send %s ###\n", mSP.GetCTS()?"on":"off");
                }

                // Handle DSR event
                if (eEvent & CSerial::EEventDSR)
                {
                    printf("\n### Data set ready %s ###\n", mSP.GetDSR()?"on":"off");
                }

                // Handle error event
                if (eEvent & CSerial::EEventError)
                {
                    printf("\n### ERROR: ");
                    switch (mSP.GetError())
                    {
                        case CSerial::EErrorBreak:		printf("Break condition");			break;
                        case CSerial::EErrorFrame:		printf("Framing error");			break;
                        case CSerial::EErrorIOE:		printf("IO device error");			break;
                        case CSerial::EErrorMode:		printf("Unsupported mode");			break;
                        case CSerial::EErrorOverrun:	printf("Buffer overrun");			break;
                        case CSerial::EErrorRxOver:		printf("Input buffer overflow");	break;
                        case CSerial::EErrorParity:		printf("Input parity error");		break;
                        case CSerial::EErrorTxFull:		printf("Output buffer full");		break;
                        default:						printf("Unknown");					break;
                    }
                    printf(" ###\n");
                }

                // Handle ring event
                if (eEvent & CSerial::EEventRing)
                {
                    printf("\n### RING ###\n");
                }

                // Handle RLSD/CD event
                if (eEvent & CSerial::EEventRLSD)
                {
                    printf("\n### RLSD/CD %s ###\n", mSP.GetRLSD()?"on":"off");
                }

                // Handle data receive event
                if (eEvent & CSerial::EEventRecv)
                {
                    // Read data, until there is nothing left
                    DWORD dwBytesRead = 0;
                    do
                    {
                        char szBuffer[1024];

                        // Read data from the COM-port
                        lLastError = mSP.Read(szBuffer, sizeof(szBuffer)-1, &dwBytesRead);
                        if (lLastError != ERROR_SUCCESS)
                        {
                            string errorMsg = getLastWin32Error();
                            Log(lError) <<"Unable to read from COM-port.";
                            Log(lError) <<"Error was: "<<errorMsg;
                            break;
                        }

                        if (dwBytesRead > 0)
                        {
                            // Finalize the data, so it is a valid message
                            szBuffer[dwBytesRead] = '\0';
                            for(int i = 0; i < dwBytesRead; i++)
                            {
                                mMessageBuilder.Build(szBuffer[i]);
                                if(mMessageBuilder.IsComplete())
                                {
                                    {
                                        Poco::ScopedLock<Poco::Mutex> lock(mTheHost.mReceivedMessagesMutex);
                                        mTheHost.mReceivedMessages.append(mMessageBuilder.GetMessage());
                                        Log(lInfo) << "Received: " << mMessageBuilder.GetMessage();
                                    }

                                    mMessageBuilder.Reset();
                                }
                            }
                        }
                    }
                    while (dwBytesRead > 0);
                }
            }
            break;
            case WAIT_OBJECT_0+1:
                {
                    // Set the continue bit to false, so we'll exit
                    mIsTimeToDie = true;
                }
                break;

            default:
                    // Something went wrong
                    string errorMsg = getLastWin32Error();
                    Log(lError) <<"Something went wrong";
                    Log(lError) <<"Error was: "<<errorMsg;
                    return;

                break;
        }
    }

    mIsRunning  = false;
    mIsFinished = true;
}
