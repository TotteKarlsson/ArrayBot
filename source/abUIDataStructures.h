#ifndef amlDataStructuresH
#define amlDataStructuresH
#include <windows.h>

enum ApplicationMessageEnum
{
    abSplashWasClosed = WM_USER,
    abSequencerUpdate
};

struct AppMessageStruct;

struct mlxStructMessage
{
	unsigned int         Msg;
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
