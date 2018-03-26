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
#pragma comment(lib, "atArrayBotCore.lib")
#pragma comment(lib, "atVCLCore.bpi")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

#pragma comment(lib, "ArrayBotPackage.bpi")
#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.bpi")
