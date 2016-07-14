#ifndef amlDataStructuresH
#define amlDataStructuresH

#include "Poco/DateTime.h"
#include <System.hpp>

enum ApplicationMessageEnum
{
    abSplashWasClosed,
    abSequencerUpdate
};

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
