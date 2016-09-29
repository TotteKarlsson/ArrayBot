#pragma hdrstop
#include "abSerialWorker.h"
#include "mtkLogger.h"
#include "abSerial.h"
//---------------------------------------------------------------------------
using namespace mtk;

void SerialWorker::run()
{
	Log(lInfo) << "Starting reading/writing serial port..";
 	if(!mTheHost.isConnected())
    {
		Log(lInfo) << "Serial port is not connected.";
    }

	// Create a handle for the overlapped operations
	HANDLE hevtOverlapped = mSP.m_hevtOverlapped; //::CreateEventA(0,TRUE,FALSE,0);

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
            {		//To allow for local variables
                    // Save event
                    const SerialPort::EEvent eEvent = mSP.GetEventType();

                    // Handle break event
                    if (eEvent & SerialPort::EEventBreak)
                    {
                        printf("\n### BREAK received ###\n");
                    }

                    // Handle CTS event
                    if (eEvent & SerialPort::EEventCTS)
                    {
                        printf("\n### Clear to send %s ###\n", mSP.GetCTS()?"on":"off");
                    }

                    // Handle DSR event
                    if (eEvent & SerialPort::EEventDSR)
                    {
                        printf("\n### Data set ready %s ###\n", mSP.GetDSR()?"on":"off");
                    }

                    // Handle error event
                    if (eEvent & SerialPort::EEventError)
                    {
                        switch (mSP.GetError())
                        {
                            case SerialPort::EErrorBreak:		Log(lError) <<("Break condition");			break;
                            case SerialPort::EErrorFrame:		Log(lError) <<("Framing error");			break;
                            case SerialPort::EErrorIOE:			Log(lError) <<("IO device error");			break;
                            case SerialPort::EErrorMode:		Log(lError) <<("Unsupported mode");			break;
                            case SerialPort::EErrorOverrun:		Log(lError) <<("Buffer overrun");			break;
                            case SerialPort::EErrorRxOver:		Log(lError) <<("Input buffer overflow");	break;
                            case SerialPort::EErrorParity:		Log(lError) <<("Input parity error");		break;
                            case SerialPort::EErrorTxFull:		Log(lError) <<("Output buffer full");		break;
                            default:							Log(lError) <<("Unknown Error");					break;
                        }
                    }

                    // Handle ring event
                    if (eEvent & SerialPort::EEventRing)
                    {
                        printf("\n### RING ###\n");
                    }

                    // Handle RLSD/CD event
                    if (eEvent & SerialPort::EEventRLSD)
                    {
                        printf("\n### RLSD/CD %s ###\n", mSP.GetRLSD()?"on":"off");
                    }

                    // Handle data receive event
                    if (eEvent & SerialPort::EEventRecv)
                    {
                        // Read data, until there is nothing left
                        DWORD dwBytesRead = 0;
                        do
                        {
                            char szBuffer[4096];

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
                                processReceiveBuffer(szBuffer, dwBytesRead);
                            }
                        }while (dwBytesRead > 0);
                	}
            }
            break;

            case WAIT_OBJECT_0+1:
                    // Set the continue bit to false, so we'll exit
                    mIsTimeToDie = true;
            break;

            default:
                    // Something went wrong
                    string errorMsg = getLastWin32Error();
                    Log(lError) <<"Something went wrong";
                    Log(lError) <<"Error was: "<<errorMsg;
                    //return;
            break;
        }
    }

    mIsRunning  = false;
    mIsFinished = true;
}

//This is the heart of the serial worker class.. it posts incoming messages
//to the hosts message list.
//Also, if incoming message callbacks are assigned, they are executed
int SerialWorker::processReceiveBuffer(char* buffer, int bufSize)
{
	int nrOfMessages(0);

	for(int i = 0; i < bufSize; i++)
    {
        mMessageBuilder.build(buffer[i]);
        if(mMessageBuilder.isComplete())
        {
            {
                Poco::ScopedLock<Poco::Mutex> lock(mTheHost.mReceivedMessagesMutex);
                Log(lDebug5) << "Received Serial: " << mMessageBuilder.getMessage();

                //Execute callback if present..
                if(mTheHost.mReceivedCB)
                {
                	//We need to synchronize this with the main UI thread
                	mTheHost.mReceivedCB(mMessageBuilder.getMessage());
                }
            }
            nrOfMessages++;
            mMessageBuilder.reset();
        }
	}

    return nrOfMessages;
}
