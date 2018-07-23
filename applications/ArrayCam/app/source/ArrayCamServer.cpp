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
{}

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
    stringstream msg;
    msg << "IS_RECORDING="<<dsl::toString(mMainForm.mCaptureVideoTimer->Enabled);
   	notifyClients(msg.str());
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
    if(compareStrings(ap[acrStartVideoRecorder], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Starting recording video";
        TThread::Synchronize(NULL, mMainForm.startRecordingMovie);

    }
    else if(compareStrings(ap[acrStopVideoRecorder], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Stop recording video";
       	TThread::Synchronize(NULL, mMainForm.stopRecordingMovie);
    }

    else if(compareStrings(ap[acrTakeSnapShot], msgList[0], csCaseInsensitive))
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


	/* LED */
    else if(compareStrings(ap[acrSetLEDIntensity], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Setting LED intensity";
        struct TLocalArgs
	    {
    	    int intensity;
	        TMainForm*	MainForm;
        	void __fastcall cb()
	        {
    	        MainForm->setLEDIntensity(intensity);
        	}
    	};

    	TLocalArgs Args;

        if(msgList.count() == 2)
        {
	    	Args.intensity = toInt(msgList[1]);
        }

        Args.MainForm = &mMainForm;

        TThread::Synchronize(NULL, Args.cb);
    }

	/* Barcode Scanner */
    else if(compareStrings(ap[acrEnableBarcodeScanner], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Enabling barcode scanner";
        if(mMainForm.DecodeSessionBtn->Caption == "Stop Scan")
        {
        	Log(lError) << "Scanner already enabled.";
        }
        else
        {
	        TThread::Synchronize(NULL, mMainForm.DecodeSessionBtn->Click);
        }
    }

    else if(compareStrings(ap[acrDisableBarcodeScanner], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Disable Barcode scanner";
        if(mMainForm.DecodeSessionBtn->Caption == "Scan Barcode")
        {
        	Log(lError) << "Scanner already disabled.";
        }
        else
        {
        	TThread::Synchronize(NULL, mMainForm.DecodeSessionBtn->Click);
        }
    }
    /*******    UC7 REQUESTS  *******/
    else if(compareStrings(ap[acrStartUC7], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Starting UC7";
        if(mMainForm.StartStopBtn->Caption == "Stop")
        {
        	Log(lError) << "UC7 already running.";
        }
        else
        {
        	TThread::Synchronize(NULL, mMainForm.StartStopBtn->Click);
        }
    }

    else if(compareStrings(ap[acrStopUC7], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Stopping UC7";
        if(mMainForm.StartStopBtn->Caption == "Start")
        {
        	Log(lError) << "UC7 already stopped.";
        }
        else
        {
        	TThread::Synchronize(NULL, mMainForm.StartStopBtn->Click);
        }
    }

    /* Enable/disable whisker sync logic */
    else if(compareStrings(ap[acrSetMoveWhiskerForwardOn], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Setting Move Whisker forward CB ON";
        TThread::Synchronize(NULL, mMainForm.checkSyncWhiskerCB);
    }

    else if(compareStrings(ap[acrSetMoveWhiskerForwardOff], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Setting Move Whisker forward CB";
        TThread::Synchronize(NULL, mMainForm.unCheckSyncWhiskerCB);
    }

    /* Set off ribbon separator */
    else if(compareStrings(ap[acrTriggerRibbonSeparator], msgList[0], csCaseInsensitive))
    {
    	Log(lInfo) << "Setting off ribbon separator";
        TThread::Synchronize(NULL, mMainForm.fireRibbonSeparator);
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
