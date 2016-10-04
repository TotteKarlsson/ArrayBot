#pragma hdrstop
#include "abSensorsArduino.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;


SensorsArduino::SensorsArduino(int portNr, int baudRate)
:
ArduinoDevice(portNr, baudRate)
{}

bool SensorsArduino::getStatus()
{
	Log(lInfo) << "Requesting sensor arduino status";
	return send("i");
}
