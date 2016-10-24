#pragma hdrstop
#include "abTSCLIB.h"
#include "mtkUtils.h"
#include "mtkLogger.h"
using namespace mtk;

//---------------------------------------------------------------------------

TSCLIB::TSCLIB()
{
}

TSCLIB::~TSCLIB()
{
	unload();
}

bool TSCLIB::load(const string& dllPath)
{
	if(fileExists(dllPath))
    {
    	Log(lInfo) << "Loading DLL: " << getFileNameNoPath(dllPath);
	  	mDLLHandle = LoadLibraryA(dllPath.c_str());
    }

    if(!mDLLHandle)
    {
    	Log(lError) << "Failed to load DLL: "<< getFileNameNoPath(dllPath);
        return false;
    }

    //Load functions
    mAboutFunc = (f_void) GetProcAddress(mDLLHandle, "about");
    if(!mAboutFunc)
    {
    	Log(lError) <<"Failed to import function \"about\"";
    }
    return true;
}

bool TSCLIB::unload()
{
	return FreeLibrary(mDLLHandle);
}

void TSCLIB::about()
{
	mAboutFunc();
}

