#include "abSerial.h"
#include "mtkUtils.h"

using namespace mtk;

#define ARDUINO_WAIT_TIME 2000


Serial::Serial(int portNr, int baudRate)
:
mMessageBuilder('[', ']'),
//mMessageBuilder('\n'),
mSerialWorker(*this)
{
	if(connect(portNr, baudRate))
    {
    	//Start serving...
        mSerialWorker.start(true);
    }
}

Serial::~Serial()
{
    //Check if we are mIsConnected before trying to disconnect
    if(mIsConnected)
    {
        //Close the serial handler
        disConnect();
    }
}

void SerialWorker::run()
{
	Log(lInfo) << "Starting reading serial port..";
 	if(!mTheHost.isConnected())
    {
		Log(lInfo) << "Serial port is not connected.";
    }
	while(!mIsTimeToDie)
    {
    	mTheHost.read();
    }

    mIsRunning  = false;
    mIsFinished = true;
}

bool Serial::connect(int portNr, int baudRate)
{
    //We're not yet connected
    mIsConnected = false;

    string port("COM" + toString(portNr));

    //Try to connect to the given port throuh CreateFile
    mSerialHandle = CreateFileA(port.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    //Check if the connection was successfull
    if(mSerialHandle == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        long e = GetLastError();
        if(e == ERROR_FILE_NOT_FOUND)
        {
            //Print Error if neccessary
            Log(lError) << "Handle was not attached. Reason: Port COM" <<portNr<<" not available.";

        }
        else if( e == ERROR_BAD_PATHNAME)
        {
            printf("ERROR: Bad path: %s\n", port);
        }
        else
        {
            printf("ERROR!!!");
        }
        return false;
    }
    else
    {
        //If mIsConnected we try to set the comm parameters
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(mSerialHandle, &dcbSerialParams))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!");
            return false;
        }
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate = baudRate;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;

             //Set the parameters and check for their proper application
             if(!SetCommState(mSerialHandle, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 //If everything went fine we're mIsConnected
                 mIsConnected = true;

                 //We wait 2s as the arduino board will be reseting
                 //Sleep(ARDUINO_WAIT_TIME);
                 return true;
             }
        }
    }
    return false;
}

bool Serial::disConnect()
{
	if(CloseHandle(mSerialHandle) == true)
    {
    	mIsConnected = false;
		return true;
    }

    //There was an error closing the handle...
    //Check last error
    return false;
}


int Serial::read()
{
	//Read the whole buffer and create messages from it
    const int readBytes(1);
    char buf[readBytes];
    int bytesRead = readData(buf, readBytes);

    if(bytesRead != readBytes)
    {
    	Log(lError) << "bad...";
        return -1;
    }
    for(int i = 0; i < bytesRead; i++)
    {
        mMessageBuilder.Build(buf[i]);
        if(mMessageBuilder.IsComplete())
        {
            {
                Poco::ScopedLock<Poco::Mutex> lock(mMessageMutex);
                mMessages.append(mMessageBuilder.GetMessage());
            }

            mMessageBuilder.Reset();
        }

    }
    return bytesRead;
}

int Serial::readData(char *buffer, unsigned int n)
{
    //Number of bytes we'll have read
    DWORD bytesRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(mSerialHandle, &mErrors, &mStatus);

    //Read chars, and return the number of read bytes on success
    //This one is blocking
    if(ReadFile(mSerialHandle, buffer, n, &bytesRead, NULL) && bytesRead != 0)
    {
        return bytesRead;
    }

    //If nothing has been read, or that an error was detected return -1
    return -1;
}


bool Serial::hasMessage()
{
	return mMessages.size() ? true : false;
}

string Serial::popMessage()
{
    {
        Poco::ScopedLock<Poco::Mutex> lock(mMessageMutex);
		return mMessages.size() ? mMessages.popFront() : string("");
    }
}

bool Serial::writeData(char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if(!WriteFile(mSerialHandle, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(mSerialHandle, &mErrors, &mStatus);
        return false;
    }

    return true;
}

bool Serial::isConnected()
{
    //Simply return the connection mStatus
    return mIsConnected;
}