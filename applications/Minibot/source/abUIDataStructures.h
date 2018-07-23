#ifndef amlDataStructuresH
#define amlDataStructuresH

#include "Poco/DateTime.h"
#include <System.hpp>


enum ApplicationMessageEnum
{
    atSplashWasClosed = 0,
    atUC7Message = 1,
    atMiscMessage = 2,
    atEnableResumeBtn = 3,
    abSequencerUpdate
};

//enum ApplicationMessageEnum
//{
//    abSplashWasClosed,
//    abSequencerUpdate
//};

using Poco::DateTime;

struct AppMessageStruct;

struct mlxStructMessage
{
	Cardinal            Msg;
	int                 wparam;
	AppMessageStruct*   lparam;
	LRESULT             Result;
};

struct AppMessageStruct
{
	ApplicationMessageEnum 	mMessageEnum;
	void*                   mData;

};


#endif
