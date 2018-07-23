//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\source\vcl\frames\TFFMPEGOutputFrame.cpp", FFMPEGOutputFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\THDMIStreamerFrame.cpp", HDMIStreamerFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TImageItemFrame.cpp", ImageItemFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TApplicationSoundsFrame.cpp", ApplicationSoundsFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TArduinoServerCommandFrame.cpp", ArduinoServerCommandFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TFFMPEGFrame.cpp", FFMPEGFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TPGConnectionFrame.cpp", PGConnectionFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TSoundsFrame.cpp", SoundsFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TImagesFrame.cpp", ImagesFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TMovieItemFrame.cpp", MovieItemFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\frames\TMoviesFrame.cpp", MoviesFrame); /* TFrame: File Type */
USEFORM("..\..\source\vcl\forms\TYesNoForm.cpp", YesNoForm);
USEFORM("..\..\source\vcl\forms\TamFileEditor.cpp", amFileEditor);
USEFORM("..\..\source\vcl\forms\TEditSequenceForm.cpp", EditSequenceForm);
USEFORM("..\..\source\vcl\forms\TShowFileContentForm.cpp", ShowFileContentForm);
USEFORM("..\..\source\vcl\forms\TStringInputDialog.cpp", StringInputDialog);
USEFORM("..\..\source\vcl\forms\TTextInputDialog.cpp", TextInputDialog);
USEFORM("..\..\source\vcl\forms\TSelectIntegerForm.cpp", SelectIntegerForm);
USEFORM("..\..\source\vcl\forms\TSelectProcessTypeDialog.cpp", SelectProcessTypeDialog);
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
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

#pragma comment(lib, "atFoundation.lib")
//#pragma comment(lib, "atSounds.lib")
//#pragma comment(lib, "atDataBase.lib")
//#pragma comment(lib, "atVCLCommon.lib")
#pragma comment(lib, "atVCLComponents.bpi")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "atVCLDataModules.bpi")

#pragma comment(lib, "DBXDevartPostgreSQLDriver250.bpi")
#pragma comment(lib, "dbxcds.bpi") //Simple dataset
#pragma comment(lib, "Tee.bpi")

