#pragma hdrstop
#include "abPufferArduinoClient.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
PufferArduinoClient::PufferArduinoClient()
:
ArduinoClient()
{
}

void PufferArduinoClient::resetSectionCounter()
{
	request("RESET_SECTION_COUNT");
}

void PufferArduinoClient::setPuffAfterSectionCount(int count)
{
	stringstream msg;
    msg <<"SET_DESIRED_RIBBON_LENGTH="<<count;
	request(msg.str());
}

void PufferArduinoClient::enableAutoPuff()
{
	stringstream msg;
    msg <<"ENABLE_AUTO_PUFF";
	request(msg.str());
}

void PufferArduinoClient::enablePuffer()
{
	stringstream msg;
    msg <<"ENABLE_PUFFER";
	request(msg.str());
}

void PufferArduinoClient::puff()
{
	stringstream msg;
    msg <<"PUFF";
	request(msg.str());
}

void PufferArduinoClient::disableAutoPuff()
{
	stringstream msg;
    msg <<"DISABLE_AUTO_PUFF";
	request(msg.str());
}

