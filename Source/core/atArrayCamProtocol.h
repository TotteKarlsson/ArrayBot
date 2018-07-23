#ifndef atArrayCamProtocolH
#define atArrayCamProtocolH
#include <map>
#include "atCoreExporter.h"
//---------------------------------------------------------------------------
using std::map;
using std::string;

//Put this in a header to be shared between server/client
//!Valid requests/responses enums
//acr <==> array cam request/response
//acm <==> miscellaneous server message that clients may handle as they wish
//abr <==> arraybot server request. For now mingled here...

enum  ACMessageID
{
	acrStartVideoRecorder = 0,
    acrVideoRecorderStarted,
	acrStopVideoRecorder,
    acrVideoRecorderStopped,
	acrTakeSnapShot,
	acrSnapShotTaken,
    acrEnableBarcodeScanner,
    acrBarcodeScanSucceded,
    acrBarcodeScanFailed,
    acrDisableBarcodeScanner,
    acrBarcodeScannerDisabled,
    acrSetZoomAndFocus,
	acrFocusAndZoomSet,
    acrZoomIn,
    acrZoomInSet,
    acrZoomOut,
    acrZoomOutSet,
    acrFocusIn,
    acrFocusInSet,
    acrFocusOut,
    acrFocusOutSet,
    acrStartUC7,
    acrUC7Started,
	acrUC7IsRunning,
    acrStopUC7,
    acrUC7Stopped,
	acrUC7IsStopped,
    acrSetLEDIntensity,
    acrLEDIntensitySet,

    acmBeforeCutting,
    acmCutting,
    acmAfterCutting,
    acmRetracting,

    acrTriggerRibbonSeparator,
    acrRibbonSeparatorTriggered,

    abrMoveWhiskerForward, 			//!The cmd needs three arguments, distance, speed and acceleration

    acrSetMoveWhiskerForwardOn,
    acrMoveWhiskerForwardOnSet,
    acrSetMoveWhiskerForwardOff,
    acrMoveWhiskerForwardOffSet,
    acrUnknown
};

class AT_CORE ArrayCamProtocol
{
	public:
							        		ArrayCamProtocol();

		ACMessageID			        		idFromString(const string& msg);
		string 	   			        		operator[](ACMessageID r);
    	static map<ACMessageID, string>   	mIPCMessage;

	private:
	    map<ACMessageID, string>::iterator	mIter;
        static map<ACMessageID, string>     createProtocol();

};

#endif
