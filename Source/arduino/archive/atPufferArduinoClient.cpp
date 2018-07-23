#pragma hdrstop
#include "atPufferArduinoClient.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
PufferArduinoClient::PufferArduinoClient()
:
ArduinoClient()
{}

void PufferArduinoClient::getBoardStatus()
{
	request("GET_PUFFER_ARDUINO_STATUS");
}

void PufferArduinoClient::resetSectionCounter()
{
	request("RESET_SECTION_COUNT");
}

void PufferArduinoClient::setDesiredRibbonLength(int count)
{
	stringstream msg;
    msg <<"SET_DESIRED_RIBBON_LENGTH="<<count;
	request(msg.str());
}

void PufferArduinoClient::enableAutoPuff()
{
	request("ENABLE_AUTO_PUFF");
}

void PufferArduinoClient::disableAutoPuff()
{
	request("DISABLE_AUTO_PUFF");
}

void PufferArduinoClient::enablePuffer()
{
	request("ENABLE_PUFFER");
}

void PufferArduinoClient::puff()
{
	request("PUFF");
}

void PufferArduinoClient::enableAutoZeroCut()
{
	request("ENABLE_AUTO_ZERO_CUT");
}

void PufferArduinoClient::disableAutoZeroCut()
{
	request("DISABLE_AUTO_ZERO_CUT");
}

void PufferArduinoClient::startNewRibbon()
{
	request("START_NEW_RIBBON");
}

void PufferArduinoClient::setCutPreset(int preset)
{
	stringstream msg;
    msg <<"SET_CUT_THICKNESS_PRESET="<<preset;
    request(msg.str());
}
