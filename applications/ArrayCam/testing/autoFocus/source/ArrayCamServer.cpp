#pragma hdrstop
#include "TMainForm.h"
#include "ArrayCamServer.h"
#include "dslLogger.h"
#include "dslSocketWorker.h"
#include "dslStringUtils.h"
#include "core/atArrayCamProtocol.h"
//---------------------------------------------------------------------------
using namespace dsl;

ArrayCamServer::ArrayCamServer(TMainForm& mf, int portNumber)
:
IPCServer(portNumber, "ARRAYCAM_SERVER", createArrayCamIPCReceiver),
mMainForm(mf)
{


}

ArrayCamServer::~ArrayCamServer()
{}

void ArrayCamServer::assignOnUpdateCallBack(OnMessageUpdateCB cb)
{
	onMessageUpdateCB = cb;
}

bool ArrayCamServer::shutDown()
{
    IPCServer::shutDown();
    return true;
}

void ArrayCamServer::broadcast(ACMessageID id, const string& arg1, const string& arg2, const string& arg3)
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

void ArrayCamServer::broadcastStatus()
{
//    stringstream msg;
////    msg << "IS_RECORDING="<<dsl::toString(mMainForm.mCaptureVideoTimer->Enabled);
//   	notifyClients(msg.str());
}

void ArrayCamServer::notifyClients(const string& msg)
{
	if(!msg.size())
    {
    	return;
    }

    if(onMessageUpdateCB)
    {
    	//This one is synchronized
        onMessageUpdateCB(msg);
    }

    IPCServer::broadcast(msg);
}

//Handle incoming client requests over the socket
//These messages are handled in a thread
//Depending on the message, a response may be sent using the
//notifyClients function
bool ArrayCamServer::processRequest(IPCMessage& msg)
{
    stringstream clientMessage;
    if(msg.isPacked())
    {
        msg.unPack();
    }

	ArrayCamProtocol ap;
    //INCOMING MESSAGES ******************************************

    StringList msgList(msg, ',');

    /* CAMERA */
    if(compareStrings(ap[acrTakeSnapShot], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Take snapshot";
        TThread::Synchronize(NULL, mMainForm.takeSnapShot);
    }

	/* Navitar controller */
    else if(compareStrings(ap[acrSetZoomAndFocus], msgList[0], csCaseInsensitive))
    {

    	Log(lInfo) << "Setting Navitar zoom and focus";

        struct TLocalArgs
	    {
    	    int focus;
            int zoom;
	        TMainForm*	MainForm;
        	void __fastcall setZoomAndFocus()
	        {
    	        MainForm->setFocusAndZoom(focus, zoom);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 3)
        {
	    	Args.focus = toInt(msgList[1]);
	        Args.zoom = toInt(msgList[2]);
        }

        Args.MainForm = &mMainForm;

        TThread::Synchronize(NULL, Args.setZoomAndFocus);
    }

	/* Navitar controller */
    else if(compareStrings(ap[acrFocusIn], msgList[0], csCaseInsensitive))
    {

    	Log(lInfo) << "Focus in";

        struct TLocalArgs
	    {
            int f;
	        TMainForm*	MainForm;
        	void __fastcall focusIn()
	        {
    	        MainForm->focusIn(f);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 2)
        {
	        Args.f = toInt(msgList[1]);
        }

        Args.MainForm = &mMainForm;
        TThread::Synchronize(NULL, Args.focusIn);
    }

	/* Navitar controller */
    else if(compareStrings(ap[acrFocusOut], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Focus out";
        struct TLocalArgs
	    {
            int f;
	        TMainForm*	MainForm;
        	void __fastcall focusOut()
	        {
    	        MainForm->focusOut(f);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 2)
        {
	        Args.f = toInt(msgList[1]);
        }

        Args.MainForm = &mMainForm;

        TThread::Synchronize(NULL, Args.focusOut);
    }

	/* Navitar controller */
    else if(compareStrings(ap[acrZoomIn], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Zoom in";
        struct TLocalArgs
	    {
            int zoom;
	        TMainForm*	MainForm;
        	void __fastcall zoomIn()
	        {
    	        MainForm->zoomIn(zoom);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 2)
        {
	        Args.zoom = toInt(msgList[1]);
        }

        Args.MainForm = &mMainForm;
        TThread::Synchronize(NULL, Args.zoomIn);
    }

	/* Navitar controller */
    else if(compareStrings(ap[acrZoomOut], msgList[0], csCaseInsensitive))
    {

    	Log(lInfo) << "Zoom out";

        struct TLocalArgs
	    {
            int zoom;
	        TMainForm*	MainForm;
        	void __fastcall zoomOut()
	        {
    	        MainForm->zoomOut(zoom);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 2)
        {
	        Args.zoom = toInt(msgList[1]);
        }

        Args.MainForm = &mMainForm;

        TThread::Synchronize(NULL, Args.zoomOut);
    }


    else if(compareStrings("GET_SERVER_STATUS", msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Broadcast status";
		broadcastStatus();
    }

    else
    {
    	Log(lError) << "UNHANDLED SERVER MESSAGE: "<<msgList[0];
    }

    if(clientMessage.str().size())
    {
   		notifyClients(clientMessage.str());
    }
    return msg.IsProcessed();
}
