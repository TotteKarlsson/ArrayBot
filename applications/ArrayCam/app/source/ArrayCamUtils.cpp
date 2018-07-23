#pragma hdrstop
#include "ArrayCamUtils.h"
#include "dslUtils.h"
#include "dslIPCMessageEnums.h"
#include "dslLogger.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;

//---------------------------------------------------------------------------
int getArrayCamIPCMessageID(const string& cs)
{
    if(compareStrings(cs, "START_RECORDING_VIDEO",  csCaseInsensitive))    return cStartRecordingVideo;
    if(compareStrings(cs, "STOP_RECORDING_VIDEO",   csCaseInsensitive))    return cStopRecordingVideo;
    return getIPCMessageID(cs);
}

//---------------------------------------------------------------------------
string getArrayCamIPCMessageName(int cs)
{
    switch (cs)
    {
        case cStartRecordingVideo:	  				return  "START_RECORDING_VIDEO";
        case cStopRecordingVideo:    				return  "STOP_RECORDING_VIDEO";
        default: return getIPCMessageName(cs);
    }
}


