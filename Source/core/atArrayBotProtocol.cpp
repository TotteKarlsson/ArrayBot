#pragma hdrstop
#include "atArrayBotProtocol.h"
//---------------------------------------------------------------------------


map<ABMessageID, string> ArrayBotProtocol::mIPCMessage = createProtocol();

ArrayBotProtocol::ArrayBotProtocol()
{}


map<ABMessageID, string> ArrayBotProtocol::createProtocol()
{
  	map<ABMessageID, string>   	m;
    m[abrSetJoyStickSpeed] 	   	= "Set Joystick Speed";
    m[abrUnknown]			    = "Unknown";
    return m;
}

ABMessageID ArrayBotProtocol::idFromString(const string& r)
{
    map<ABMessageID, string>::const_iterator it;
    ABMessageID key = abrUnknown;

    for (it = mIPCMessage.begin(); it != mIPCMessage.end(); ++it)
    {
	    if (it->second == r)
    	{
		    key = it->first;
			return key;
	    }
    }

   	return abrUnknown;
}

string ArrayBotProtocol::operator[](ABMessageID r)
{
	return mIPCMessage[r];
}
