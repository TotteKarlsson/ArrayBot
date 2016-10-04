#pragma hdrstop
#include "abLightsArduinoClient.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
LightsArduinoClient::LightsArduinoClient()
:
	ArduinoClient()
{}

void LightsArduinoClient::getBoardStatus()
{
	stringstream msg;
    msg <<"GET_LIGHTS_ARDUINO_STATUS";
	request(msg.str());
}

void LightsArduinoClient::toggleLED()
{
	stringstream msg;
    msg <<"TOGGLE_LED_LIGHT";
	request(msg.str());
}

void LightsArduinoClient::toggleCoax()
{
	stringstream msg;
    msg <<"TOGGLE_COAX_LIGHT";
	request(msg.str());
}


