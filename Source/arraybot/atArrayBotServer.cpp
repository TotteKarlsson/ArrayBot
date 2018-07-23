#pragma hdrstop
#include "arraybot/atArrayBot.h"
#include "atArrayBotServer.h"
#include "dslLogger.h"
#include "dslSocketWorker.h"
#include "dslStringUtils.h"
#include "core/atArrayBotProtocol.h"
//---------------------------------------------------------------------------
using namespace dsl;

ArrayBotServer::ArrayBotServer(ArrayBot& ab, int portNumber)
:
IPCServer(portNumber, "ArrayBot_SERVER", createArrayBotIPCReceiver),
mArrayBot(ab)
{
}

ArrayBotServer::~ArrayBotServer()
{}

//void ArrayBotServer::assignOnUpdateCallBack(OnMessageUpdateCB cb)
//{
//	onMessageUpdateCB = cb;
//}

bool ArrayBotServer::shutDown()
{
    IPCServer::shutDown();
    return true;
}

//string ArrayBotServer::IPCCommand(ABMessageID id)
//{
//	return mProtocol[id];
//}

void ArrayBotServer::broadcast(ABMessageID id, const string& arg1, const string& arg2, const string& arg3)
{
    stringstream msg;
    msg << mProtocol[id];

    if(arg1.size())
    {
    	msg << "," << arg1;
    }

    if(arg2.size())
    {
    	msg << "," << arg2;
    }

    if(arg3.size())
    {
    	msg << "," << arg3;
    }

    notifyClients(msg.str());
}

void ArrayBotServer::broadcastStatus()
{
    stringstream msg;
//    msg << "IS_RECORDING="<<dsl::toString(mMainForm.mCaptureVideoTimer->Enabled);
   	notifyClients(msg.str());
}

void ArrayBotServer::notifyClients(const string& msg)
{
	if(!msg.size())
    {
    	return;
    }

//    if(onMessageUpdateCB)
//    {
//    	//This one is synchronized
//        onMessageUpdateCB(msg);
//    }

    IPCServer::broadcast(msg);
}

//Handle incoming client requests over the socket
//These messages are handled in a thread
//Depending on the message, a response may be sent using the
//notifyClients function
bool ArrayBotServer::processRequest(IPCMessage& msg)
{
    stringstream clientMessage;
    if(msg.isPacked())
    {
        msg.unPack();
    }

	ArrayBotProtocol ap;
    //INCOMING MESSAGES ******************************************

    StringList msgList(msg, ',');

    /* CAMERA */
//    if(compareStrings(ap[acrStartVideoRecorder], msgList[0], csCaseInsensitive))
//    {
//    	Log(lInfo) << "Starting recording video";
//        TThread::Synchronize(NULL, mMainForm.startRecordingMovie);
//
//    }
//    else if(compareStrings(ap[acrStopVideoRecorder], msgList[0], csCaseInsensitive))
//    {
//    	Log(lInfo) << "Stop recording video";
//       	TThread::Synchronize(NULL, mMainForm.stopRecordingMovie);
//
//    }
//
//    else if(compareStrings(ap[acrTakeSnapShot], msgList[0], csCaseInsensitive))
//    {
//    	Log(lInfo) << "Take snapshot";
//        TThread::Synchronize(NULL, mMainForm.takeSnapShot);
//    }


    if(clientMessage.str().size())
    {
   		notifyClients(clientMessage.str());
    }
    return msg.IsProcessed();
}
