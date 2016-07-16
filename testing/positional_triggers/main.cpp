#pragma hdrstop
#pragma argsused
#include "abPositionalTrigger.h"
#include <iostream>
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "mtkIniFile.h"
#include "abAPTMotor.h"
#include "abTriggerFunction.h"
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

    //When the black motor is at position '2', trigger movement of the red motor
    PositionalTrigger tr1(blackMotor);
    TriggerFunction* tf;
    tf = new MoveAbsolute(redMotor, 6, 1, 1);
    tr1.assignTriggerFunction(tf);

   	tr1.enable();

	//Move black motor to 2
    blackMotor->moveAbsolute(	10, 6.5);
//    redMotor->moveAbsolute(		6,  0.1);

    //The triggers should trigger
    while(!tr1.isTriggered() )
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

