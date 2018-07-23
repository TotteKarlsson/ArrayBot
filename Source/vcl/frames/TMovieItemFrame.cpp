#include <vcl.h>
#pragma hdrstop
#include "TMovieItemFrame.h"
#include "dslLogger.h"
#include <JPEG.hpp>
#include "dslVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMovieItemFrame *MovieItemFrame;

using namespace dsl;
static int frameNr = 0;

//---------------------------------------------------------------------------
__fastcall TMovieItemFrame::TMovieItemFrame(const File& file, TComponent* Owner)
	:
    TFrame(Owner),
    mMovieFile(file),
    mThumbNail("")
{
    this->Name = this->Name + "_" + IntToStr(frameNr++);
   	WarningImage->Visible 	= !mMovieFile.exists();
    PlayBtn->Visible  		= mMovieFile.exists();

    //Create thumbnail if not exist
    Path tnp(mMovieFile.path());

    tnp.setExtension("jpg");
    mThumbNail = tnp;
    if(mThumbNail.exists())
    {
    	//load thumbnail to image
        Log(lDebug5) << "Movie thumbnail exists";
        string imgP = mThumbNail.path();
        WarningImage->Picture->LoadFromFile(imgP.c_str());
		WarningImage->Visible = true;
    }
    else
    {
    	if(mMovieFile.exists())
        {
            //create thumbnail
            Log(lDebug5) << "Creating movie thumbnail";
            mTNThread.assignCallBacks(NULL, NULL, populateTNImage);
            mTNThread.setInputFile(mMovieFile.path());
            mTNThread.run();
        }
        else
        {
        	Log(lError) << "The Movie file: "<<mMovieFile.path()<<" don't exist";
        }
    }
}

void TMovieItemFrame::setItemName(const string& name)
{
	mItemName = name;
}

//---------------------------------------------------------------------------
void __fastcall TMovieItemFrame::PlayBtnClick(TObject *Sender)
{
	if(mMovieFile.exists())
    {
		Log(lInfo) << "Playing file: "<<mMovieFile.path();
		ShellExecuteA(NULL, "open", mMovieFile.path().c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    else
    {
		Log(lWarning) << "The file: "<<mMovieFile.path()<<" don't exist!";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMovieItemFrame::WarningImageClick(TObject *Sender)
{
	Log(lWarning) << "The file: "<<mMovieFile.path()<<" don't exist!";
}

void TMovieItemFrame::populateTNImage(int, int)
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
