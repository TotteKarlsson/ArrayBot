#pragma hdrstop
#include "atSensorsArduino.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;


SensorsArduino::SensorsArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate)
{}

bool SensorsArduino::getStatus()
{
	Log(lInfo) << "Requesting sensor arduino status";
	return send("i");
}
