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

//int extractCoverSlipID(const string& bc)
//{
//	string temp(bc);
//    //Make sure first char is a 'C'
//    if(!bc.size() || bc[0] != 'C')
//    {
//    	Log(lError) << bc << " is not a valid barcode!";
//        return -1;
//    }
//
//	temp.erase(0,1);
//    int id = toInt(temp);
//    Log(lDebug3) << "Extracted id "<<id<<" from "<<bc;
//    return id;
//}


