//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\source\vcl\datamodules\TPGCoverSlipDataModule.cpp", csPGDM); /* TDataModule: File Type */
USEFORM("..\..\source\vcl\datamodules\TSensorsDataModule.cpp", SensorsDataModule); /* TDataModule: File Type */
USEFORM("..\..\source\vcl\datamodules\TPGImagesAndMoviesDataModule.cpp", PGImagesAndMoviesDM); /* TDataModule: File Type */
USEFORM("..\..\source\vcl\datamodules\TPGDataModule.cpp", pgDM); /* TDataModule: File Type */
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

#pragma comment(lib, "atFoundation.lib")
//#pragma comment(lib, "atDataBase.lib")
#pragma comment(lib, "DBXDevartPostgreSQLDriver250.bpi")


//Simple dataset
#pragma comment(lib, "dbxcds.bpi") //TSimpleDataset

