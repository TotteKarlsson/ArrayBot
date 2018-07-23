#include <vcl.h>
#pragma hdrstop
#include "TImageItemFrame.h"
#include "dslLogger.h"
#include <JPEG.hpp>
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TImageItemFrame *ImageItemFrame;

using namespace dsl;
static int frameNr = 0;

//---------------------------------------------------------------------------
__fastcall TImageItemFrame::TImageItemFrame(const File& file, TComponent* Owner)
	:
    TFrame(Owner),
    mItemFile(file),
    mThumbNail("")
{
    this->Name = this->Name + "_" + IntToStr(frameNr++);
   	WarningImage->Visible 	= !mItemFile.exists();

    //Create thumbnail if not exist
    Path tnp(mItemFile.path());

    tnp.setBaseName(tnp.getBaseName() + "_tn");
    tnp.setExtension("jpg");

    mThumbNail = tnp;
    if(mThumbNail.exists())
    {
    	//load thumbnail to image
        Log(lDebug5) << "Item thumbnail exists";
        string imgP = mThumbNail.path();
        WarningImage->Picture->LoadFromFile(imgP.c_str());
		WarningImage->Visible = true;
    }
    else
    {
    	if(mItemFile.exists())
        {
            //create thumbnail
            Log(lDebug5) << "Creating Item thumbnail";
            mTNThread.assignCallBacks(NULL, NULL, populateTNImage);
            mTNThread.setInputFile(mItemFile.path());
            mTNThread.run();
        }
    }
}

void TImageItemFrame::setItemName(const string& name)
{
	mItemName = name;
}

//---------------------------------------------------------------------------
void __fastcall TImageItemFrame::WarningImageClick(TObject *Sender)
{
	if(mItemFile.exists())
    {
		Log(lInfo) << "Opening file: "<<mItemFile.path();
		ShellExecuteA(NULL,"open", mItemFile.path().c_str(),NULL, NULL, SW_SHOWNORMAL);
    }
    else
    {
		Log(lWarning) << "The file: "<<mItemFile.path()<<" don't exist!";
    }
}

void TImageItemFrame::populateTNImage(int, int)
{
	try
    {
        Log(lDebug) << "Loading thumbnail: " << mThumbNail.path();
        string imgP = mThumbNail.path();
        WarningImage->Picture->LoadFromFile(imgP.c_str());
	    WarningImage->Visible = true;
    }
    catch(const EFOpenError& e)
    {
    	Log(lError) << stdstr(e.Message);
    }
    catch(const EInvalidGraphic& e)
    {
    	Log(lError) << stdstr(e.Message);
    }


}
