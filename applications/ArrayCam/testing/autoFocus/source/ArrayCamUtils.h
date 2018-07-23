#ifndef ArrayCamUtilsH
#define ArrayCamUtilsH
#include <string>
//---------------------------------------------------------------------------
using std::string;

int    PACKAGE 	getArrayCamIPCMessageID(const string& msg);
string PACKAGE	getArrayCamIPCMessageName(int cs);

enum ARRAYCAM_IPC_ID
{
        cStartRecordingVideo   	= 100,
        cStopRecordingVideo   	= 101,
        cTakeSnapShot		 	= 102
};

//int  PACKAGE extractCoverSlipID(const string& bc);
#endif
