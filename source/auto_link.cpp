#pragma hdrstop
#if defined DSL_STATIC
	#pragma comment(lib, "mtkCommon-static.lib")
	#pragma comment(lib, "mtkMath-static.lib")
	#pragma comment(lib, "mtkIPC-static.lib")
#else
	#pragma comment(lib, "mtkCommon.lib")
	#pragma comment(lib, "mtkMath.lib")
	#pragma comment(lib, "mtkIPC.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "poco_data-static.lib")
#pragma comment(lib, "poco_mysql_connector-static.lib")
#pragma comment(lib, "poco_sqlite_connector-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
#pragma comment(lib, "libmysqlB.lib")

//Thorlabs
#pragma comment(lib, "Thorlabs.MotionControl.TDIEngineB.lib")

//Motors
#pragma comment(lib, "Thorlabs.MotionControl.TCube.StepperMotorB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.IntegratedStepperMotorsB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.DCServoB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.BrushlessMotorB.lib")

