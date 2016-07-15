#pragma hdrstop
#pragma argsused
#include "abPositionalTrigger.h"
#include <iostream>
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "mtkIniFile.h"
#include "abAPTMotor.h"

using namespace mtk;
using namespace std;
using namespace std::tr1;

int main()
{
    string appFolder("C:\\Users\\matsk\\AppData\\Local\\ArrayBot");
    IniFile ini(joinPath(appFolder, "ArrayBot.ini"));
    ini.load();

    ArrayBot ab(ini, appFolder);
    ab.initialize();

	//TCubeDSServoMotor
	APTMotor* blackMotor = ab.getMotorWithName("WHISKER UNIT_Z");

    //TCubeStepperMotor
	APTMotor* redMotor 	 = ab.getMotorWithName("COVERSLIP UNIT_Z");

	LogOutput::mLogToConsole = true;
 	gLogger.setLogLevel(lInfo);

    //Looping around
    lbl1:

    //Both motors starts at zero
    blackMotor->moveAbsolute(	0, 	1.5, .5);
	redMotor->moveAbsolute(		0, 	1.0, 3);

    while(!blackMotor->isAtDesiredPosition() || !redMotor->isAtDesiredPosition())
    {
    	sleep(1);
    }

    //When black motor is at position '2', trigger movement of the red motor
    PositionalTrigger trigger1("Trigger 1", blackMotor->getPosition, tcLargerThanOrEqual, 2);

    FireFunction f = bind(&APTMotor::moveAbsolute, redMotor,   6 , 1, 1);
	trigger1.addFireFunction(f);
    trigger1.enable();

	//Move black motor to 2
    blackMotor->moveAbsolute(	10, 6.5);
//    redMotor->moveAbsolute(		6,  0.1);

    //The triggers should trigger
    while(!trigger1.isTriggered() )
    {
    	sleep(10);
    }

    while(!blackMotor->isAtDesiredPosition() || !redMotor->isAtDesiredPosition())
    {
       	sleep(10);
    }

    goto lbl1;
	return 0;
}

#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "poco_foundation-static.lib")

