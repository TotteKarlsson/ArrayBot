#pragma hdrstop
#if defined DSL_STATIC
	#pragma comment(lib, "dslCommon-static.lib")
	#pragma comment(lib, "dslMath-static.lib")
	#pragma comment(lib, "dslIPC-static.lib")
#else
	#pragma comment(lib, "dslCommon.lib")
	#pragma comment(lib, "dslMath.lib")
	#pragma comment(lib, "dslIPC.lib")
#endif

#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
//#pragma comment(lib, "poco_data-static.lib")
//#pragma comment(lib, "poco_mysql_connector-static.lib")
//#pragma comment(lib, "poco_sqlite_connector-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")
//#pragma comment(lib, "libmysqlB.lib")

//Thorlabs
#pragma comment(lib, "Thorlabs.MotionControl.TDIEngineB.lib")

//Motors
#pragma comment(lib, "Thorlabs.MotionControl.TCube.StepperMotorB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.IntegratedStepperMotorsB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.DCServoB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.BrushlessMotorB.lib")

//Navitar
#pragma comment(lib, "navusbAPI_B1.lib")

