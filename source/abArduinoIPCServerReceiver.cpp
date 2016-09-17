#pragma hdrstop
#include "abArduinoIPCServerReceiver.h"
#include "mtkIPCServer.h"
#include "mtkLogger.h"
#include "mtkIPCMessageBuilder.h"
#include "abArduinoUtils.h"
//---------------------------------------------------------------------------

using namespace mtk;

SocketWorker* createArduinoIPCReceiver(int portNr, int socketHandle, void* server)
{
    SocketWorker* sWkr = new ArduinoServerIPCReceiver(portNr, socketHandle, (IPCServer*) server);
    if(sWkr)
    {
        Log(lInfo)<<"Created an IPCReceiver. Socket Handle ID is : "<<socketHandle<<"\n";
        sWkr->send("[Connection was created!]");
    }
    return sWkr;
}

ArduinoServerIPCReceiver::ArduinoServerIPCReceiver(int portNr, int socket_handle, IPCServer* server)
:
IPCReceiver(portNr, socket_handle, server)
{}

ArduinoServerIPCReceiver::~ArduinoServerIPCReceiver()
{}

void ArduinoServerIPCReceiver::Worker()
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
                    int msgID          = getArduinoIPCMessageID(aMessage.getMessage());
                    IPCMessage msg     = IPCMessage(msgID, aMessage.getMessage(), this->getSocketHandle());
                    if(mServer)
                    {
                        mServer->postIPCMessage(msg);
                    }

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


