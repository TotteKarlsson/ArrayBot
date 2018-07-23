#ifndef atSerialWorkerH
#define atSerialWorkerH
#include "dslIPCMessageBuilder.h"
#include "dslThread.h"
#include "atSerialPort.h"
#include "atATObject.h"
//---------------------------------------------------------------------------

namespace at
{
    class Serial;
    class AT_SERIAL SerialWorker : public dsl::Thread, public ATObject
    {
    	public:
                                            SerialWorker(Serial& h, SerialPort& s, char ld = '[', char rd = ']') : mTheHost(h), mSP(s), mMessageBuilder(ld, rd){}
            void			                run();
            Serial&			                mTheHost;
            SerialPort&	 	                mSP;

    	private:
        	dsl::IPCMessageBuilder		  	mMessageBuilder;
            int								processReceiveBuffer(char* buffer, int size);
    };
}

#endif
