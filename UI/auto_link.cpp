//---------------------------------------------------------------------------
#if defined DSL_STATIC
	#pragma comment(lib, "mtkCommon-static.lib")
	#pragma comment(lib, "mtkMath-static.lib")
	#pragma comment(lib, "mtkIPC-static.lib")
#else
	#pragma comment(lib, "mtkCommon.lib")
	#pragma comment(lib, "mtkMath.lib")
	#pragma comment(lib, "mtkIPC.lib")
#endif

#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "abVCLCore.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

#pragma comment(lib, "VCLCommon.bpi")
#pragma comment(lib, "DuneForms.lib")
