#ifndef abSerialWorkerH
#define abSerialWorkerH
//---------------------------------------------------------------------------
#include "mtkIPCMessageBuilder.h"
#include "mtkThread.h"
#include "abSerialPort.h"
class Serial;
class AB_CORE SerialWorker : public mtk::Thread
{
	public:
                                        SerialWorker(Serial& h, SerialPort& s) : mTheHost(h), mSP(s), mMessageBuilder('[', ']'){}
        void			                run();
        Serial&			                mTheHost;
        SerialPort&	 	                mSP;

	private:
    	mtk::IPCMessageBuilder		  	mMessageBuilder;
        int								processReceiveBuffer(char* buffer, int size);
};

#endif
