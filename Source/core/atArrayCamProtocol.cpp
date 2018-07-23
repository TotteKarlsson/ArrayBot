#pragma hdrstop
#include "atArrayCamProtocol.h"
#include <string>
//---------------------------------------------------------------------------

map<ACMessageID, string> ArrayCamProtocol::mIPCMessage = createProtocol();

ArrayCamProtocol::ArrayCamProtocol()
{}

map<ACMessageID, string> ArrayCamProtocol::createProtocol()
{
  	map<ACMessageID, string>   	m;
    m[acrStartVideoRecorder] 	           = "Start Video Recorder";
    m[acrVideoRecorderStarted] 	           = "Video Recorder Started";
    m[acrStopVideoRecorder] 	           = "Stop Video Recorder";
    m[acrVideoRecorderStopped] 	           = "Video Recorder Stoppped";
    m[acrTakeSnapShot] 			           = "Take Snapshot";
    m[acrSnapShotTaken] 		           = "Snapshot Taken";
    m[acrEnableBarcodeScanner] 	           = "Enable Barcode Scanner";
    m[acrBarcodeScanSucceded] 	           = "Barcode Scan Succeded";
    m[acrBarcodeScanFailed] 	           = "Barcode Scan Failed";
    m[acrDisableBarcodeScanner]	           = "Disable Barcode Scanner";
    m[acrBarcodeScannerDisabled]           = "Barcode Scanner Disabled";
    m[acrSetZoomAndFocus]		           = "Set Focus and Zoom";
    m[acrFocusAndZoomSet]		           = "Focus and Zoom Set";
    m[acrZoomIn]				           = "Zoom In";
    m[acrZoomInSet]	  			           = "Zoom In set";
    m[acrZoomOut]				           = "Zoom Out";
    m[acrZoomOutSet]	  		           = "Zoom Out set";

    m[acrFocusIn]				           = "Focus In";
    m[acrFocusInSet]	  		           = "Focus In set";
    m[acrFocusOut]				           = "Focus Out";
    m[acrFocusOutSet]	  		           = "Focus Out set";

    m[acrStartUC7]				           = "Start UC7";
    m[acrStopUC7]				           = "Stop  UC7";
    m[acrSetLEDIntensity]		           = "Set LED Intensity";
    m[acrLEDIntensitySet]	  	           = "LED Intensity set";

    m[acrTriggerRibbonSeparator]           = "Trigger Ribbon Separator";
    m[acrRibbonSeparatorTriggered]         = "Ribbon Separator Triggered";

    m[acmBeforeCutting]	 		           = "Before Cutting";
    m[acmCutting]	 			           = "Cutting";
    m[acmAfterCutting]			           = "After Cutting";
    m[acmRetracting]			           = "Retracting";
    m[abrMoveWhiskerForward]	           = "Move Whisker Forward";

    m[acrSetMoveWhiskerForwardOn]          = "Set Move Whisker Forward ON";
    m[acrMoveWhiskerForwardOnSet]          = "Move Whisker Forward ON set";
    m[acrSetMoveWhiskerForwardOff]         = "Set Move Whisker Forward OFF";
    m[acrMoveWhiskerForwardOffSet]         = "Move Whisker Forward OFF set";

    m[acrUnknown]				           = "Unknown";
    return m;
}

ACMessageID ArrayCamProtocol::idFromString(const string& r)
{
    map<ACMessageID, string>::const_iterator it;
    ACMessageID key = acrUnknown;

    for (it = mIPCMessage.begin(); it != mIPCMessage.end(); ++it)
    {
	    if (it->second == r)
    	{
		    key = it->first;
			return key;
	    }
    }

   	return acrUnknown;
}

string ArrayCamProtocol::operator[](ACMessageID r)
{
	return mIPCMessage[r];
}
