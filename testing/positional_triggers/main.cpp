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

int main()
{
	LogOutput::mLogToConsole = true;

    string appFolder("C:\\Users\\matsk\\AppData\\Local\\ArrayBot");
    IniFile ini(joinPath(appFolder, "ArrayBot.ini"));
    ini.load();

    ArrayBot ab(ini, appFolder);

    ab.initialize();

//    sleep(500);
	APTMotor* blackMotor 	= ab.getMotorWithName("WHISKER UNIT_Z");
	APTMotor* redMotor 		= ab.getMotorWithName("COVERSLIP UNIT_Z");

    lbl1:
    redMotor->setAcceleration(3);
    redMotor->setVelocity(1.5);

    blackMotor->moveAbsolute(1);
	redMotor->moveAbsolute(1);
    while(!blackMotor->isAtDesiredPosition() || !redMotor->isAtDesiredPosition())
    {

    }

    blackMotor->moveAbsolute(8);

    redMotor->setAcceleration(3);
    redMotor->setVelocity(.3);
	redMotor->moveAbsolute(8);

    PositionalTrigger trigger("test", tcLargerThanOrEqual, 4.5, taSetVelocity, redMotor);
	trigger.setNewVelocity(1.1);
	trigger.setNewAcceleration(3);

    while(true)
    {
    	if(trigger.test(blackMotor->getPosition()))
        {
        	trigger.execute();
            break;
        }
    }

    while(!blackMotor->isAtDesiredPosition()  || !redMotor->isAtDesiredPosition())
    {

    }

    goto lbl1;


	while(true)
    {
		sleep(100);
    }

	return 0;
}

#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkMath.lib")
#pragma comment(lib, "poco_foundation-static.lib")

