#pragma hdrstop
#include "atArduinoUtils.h"
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslIPCMessageEnums.h"

using namespace dsl;

//---------------------------------------------------------------------------
int getArduinoIPCMessageID(const string& cs)
{
    if(compareStrings(cs, "MakeAPuff",   			csCaseInsensitive))    return cMakeAPuff;
    if(compareStrings(cs, "SetPufferPuffDuration",  csCaseInsensitive))    return cSetPufferPuffDuration;
    return getIPCMessageID(cs);
}

string getArduinoIPCMessageName(int cs)
{
    switch (cs)
    {
        case cMakeAPuff:	        	return  "MakeAPuff";
        case cSetPufferPuffDuration:    return  "SetPufferPuffDuration";
        default: return getIPCMessageName(cs);
    }
}


