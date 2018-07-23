//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\source\vcl\navitarFrames\TNavitarPresetFrame.cpp", NavitarPresetFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\navitarFrames\TNavitarMotorFrame.cpp", NavitarMotorFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------


#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
//#pragma comment(lib, "dslVCLComponents.bpi")
//#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
//#pragma comment(lib, "atNavitar.lib")
//#pragma comment(lib, "atVCLCommon.lib")
//#pragma comment(lib, "atVCLComponents.bpi")


#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")

//Simple dataset
#pragma comment(lib, "dbxcds.bpi")


