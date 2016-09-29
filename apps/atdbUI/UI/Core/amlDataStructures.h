#ifndef amlDataStructuresH
#define amlDataStructuresH
#include "Poco/DateTime.h"
#include <System.hpp>

enum ApplicationMessageEnum
{
    amSplashWasClosed,
};

using Poco::DateTime;

struct DBStatistics
{
	int 		mNumberOfRecs;
};

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
