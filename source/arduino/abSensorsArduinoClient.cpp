#pragma hdrstop
#include "abSensorsArduinoClient.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
SensorsArduinoClient::SensorsArduinoClient()
:
	ArduinoClient()
{}

void SensorsArduinoClient::getBoardStatus()
{
	stringstream msg;
    msg <<"GET_SENSORS_ARDUINO_STATUS";
	request(msg.str());
}

