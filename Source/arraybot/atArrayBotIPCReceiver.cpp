#pragma hdrstop
#include "atArrayBotIPCReceiver.h"
#include "dslIPCServer.h"
#include "dslLogger.h"
#include "dslIPCMessageBuilder.h"
//#include "ArrayBotUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;

SocketWorker* createArrayBotIPCReceiver(int portNr, int socketHandle, void* server)
{
    SocketWorker* sWkr = new ArrayBotIPCReceiver(portNr, socketHandle, (IPCServer*) server);
    if(sWkr)
    {
        Log(lInfo)<<"Created an IPCReceiver. Socket Handle ID is : "<<socketHandle<<"\n";
        sWkr->send("[Connection was created!]");
    }
    return sWkr;
}

ArrayBotIPCReceiver::ArrayBotIPCReceiver(int portNr, int socket_handle, IPCServer* server)
:
IPCReceiver(portNr, socket_handle, server)
{}

ArrayBotIPCReceiver::~ArrayBotIPCReceiver()
{}

void ArrayBotIPCReceiver::Worker()
{
    IPCMessageBuilder aMessage('[',']');
    while( !isTimeToDie() )
    {
        //Check for messages
        int nBytes = receive();
        if(nBytes != -1)
        {
            //When a message is ready, post message to list
            while(mMessageBuffer.size())
            {
                char ch = mMessageBuffer.front();
                mMessageBuffer.pop_front();

                if(!aMessage.build(ch))
                {
                    Log(lDebug)<<"Character was discarded in Arduino Server IPCReceiver: \'"<<ch<<"\'"<<endl;
                }

                if(aMessage.isComplete() )
                {
//                    int msgID          = getArrayBotIPCMessageID(aMessage.getMessage());
//                    IPCMessage msg     = IPCMessage(msgID, aMessage.getMessage(), this->getSocketHandle());
//                    if(mServer)
//                    {
//                        mServer->postRequest(msg);
//                    }

                    aMessage.reset();
                }
            }
        }
        else
        {
            stop();
        }
    }
    mSocketHandle = -1;
}


