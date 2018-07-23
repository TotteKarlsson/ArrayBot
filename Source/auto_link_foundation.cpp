#pragma hdrstop
#if defined DSL_STATIC
	#pragma comment(lib, "dslFoundation-static.lib")
#else
	#pragma comment(lib, "dslFoundation.lib")

#endif

#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

//#pragma comment(lib, "atCore.lib")
//#pragma comment(lib, "atArduino.lib")

////Thorlabs
#pragma comment(lib, "Thorlabs.MotionControl.TDIEngineB.lib")

//Motors
#pragma comment(lib, "Thorlabs.MotionControl.Benchtop.StepperMotorB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.StepperMotorB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.IntegratedStepperMotorsB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.DCServoB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.BrushlessMotorB.lib")

//navitar
#pragma comment(lib, "navitarUSBAPI_Borland.lib")


