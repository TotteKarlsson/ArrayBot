//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\source\vcl\uc7Frames\TUC7StagePositionFrame.cpp", UC7StagePositionFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\uc7Forms\THandWheelPositionForm.cpp", HandWheelPositionForm);
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
//#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
//#pragma comment(lib, "atUC7API.lib")

#pragma comment(lib, "poco_foundation.lib")

#pragma comment(lib, "DBXDevartPostgreSQLDriver250.bpi")
#pragma comment(lib, "dbxcds.bpi") //Simple dataset
#pragma comment(lib, "Tee.bpi")

