#ifndef abSerialH
#define abSerialH
#include "abExporter.h"
#include "mtkStringList.h"
#include "mtkIPCMessageBuilder.h"
#include "Poco/Mutex.h"
#include "Poco/Condition.h"

using Poco::Mutex;
using Poco::Condition;

using mtk::StringList;
using mtk::IPCMessageBuilder;

class Serial;

class SerialWorker : public mtk::Thread
{
	public:
					SerialWorker(Serial& h) : mTheHost(h){}
	void			run();
	Serial&			mTheHost;
};

class AB_CORE Serial
{

    public:
                                            //Initialize Serial communication with the given COM port
                                            Serial(int portNr, int rate = 9600);

                                            //Close the connection
                                            //NOTA: for some reason you can't connect again before exiting
                                            //the program and running it again
                                            ~Serial();

		bool					            hasMessage();
        string					            popMessage();


        						            //The read function reads whats in the current buffer
                                            //and builds messages
        int						            read();

                                            //Read data in a buffer, if nbChar is greater than the
                                            //maximum number of bytes available, it will return only the
                                            //bytes available. The function return -1 when nothing could
                                            //be read, the number of bytes actually read.
        int 				                readData(char *buffer, unsigned int nbChar);

                                            //Writes data from a buffer through the Serial connection
                                            //return true on success.
        bool 				                writeData(char *buffer, unsigned int nbChar);

        					                //Check if we are actually connected
        bool 				                isConnected();
        bool					            connect(int portNr, int baudRate);
        bool					            disConnect();

    private:
        						            //Serial comm handler
        HANDLE 				   	            mSerialHandle;

        						            //Connection status
        bool 					            mIsConnected;

								            //Get various information about the connection
        COMSTAT 				            mStatus;

        						            //Keep track of last error
        DWORD 					            mErrors;

        						            //The message builder builds incoming messages using delimiters
		IPCMessageBuilder		            mMessageBuilder;

        SerialWorker						mSerialWorker;

        						            //Messages from an arduino
		Mutex					            mMessageMutex;
        StringList				            mMessages;
        Poco::Condition                     mGotMessage;

};

#endif