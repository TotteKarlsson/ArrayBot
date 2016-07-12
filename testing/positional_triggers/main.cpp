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
    blackMotor->moveAbsolute3(	0, 	1.5, 3);
	redMotor->moveAbsolute3(	0, 	1.5, 3);

    while(!blackMotor->isAtDesiredPosition() || !redMotor->isAtDesiredPosition())
    {
    	sleep(10);
    }

	//Move black motor to 2
    blackMotor->moveAbsolute3(2, 	2.5, 2);

    //When black motor is at position '2', trigger movement of the red motor
    PositionalTrigger trigger1("test1", tcLargerThanOrEqual, 2, blackMotor->getPosition);
	trigger1.addFireFunction(bind(&APTMotor::moveAbsolute2, redMotor,   2, 		1.1));

	//When red motor is at 2, trigger black motor to continue
    PositionalTrigger trigger2("test2", tcLargerThanOrEqual, 1.95, redMotor->getPosition);
	trigger2.addFireFunction(bind(&APTMotor::moveAbsolute2, blackMotor,   4,   	1.1));
    trigger1.load();
    trigger2.load();

    //The triggers should trigger
    while(!trigger1.isTriggered() || !trigger2.isTriggered())
    {
    	sleep(50);
    }

    while(!blackMotor->isAtDesiredPosition())
    {
       	sleep(50);
    }

    goto lbl1;
	return 0;
}

#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "poco_foundation-static.lib")

