#include <vcl.h>
#pragma hdrstop
#include "TFFMPEGOutputFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"

using namespace dsl;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TFFMPEGOutputFrame *FFMPEGOutputFrame;
static int frameNr = 0;
//---------------------------------------------------------------------------
__fastcall TFFMPEGOutputFrame::TFFMPEGOutputFrame(TComponent* Owner)
	:
    TFrame(Owner)
{
	mVCThread.assignCallBacks(
    boost::bind(&TFFMPEGOutputFrame::onEnter, 	this, _1, _1),
	boost::bind(&TFFMPEGOutputFrame::onProgress, this, _1, _1),
	boost::bind(&TFFMPEGOutputFrame::onExit, 	this, _1, _1)
    );

    this->Name = this->Name + "_" + IntToStr(frameNr++);
}

bool TFFMPEGOutputFrame::isDone()
{
	return  mVCThread.isFinished();
}

void TFFMPEGOutputFrame::stopCompression()
{
	mVCThread.stop();
}

string TFFMPEGOutputFrame::getInputFileName()
{
	return mVCThread.getInputFileName();
}

void TFFMPEGOutputFrame::setInputFile(const string& fName)
{
	FileNameLbl->Caption = vclstr(getFileNameNoPath(fName));
	mVCThread.setInputFile(fName);
}

void TFFMPEGOutputFrame::setCompressionOptions(const string& o, bool deleteSourceFile, bool renameSourceFile)
{
	mVCThread.setFFMPEGOutFileArguments(o);
	mVCThread.deleteSourceFileAfterCompression(deleteSourceFile);
	mVCThread.renameSourceFileAfterCompression(renameSourceFile);
}

void TFFMPEGOutputFrame::startCompression()
{
	mVCThread.start();
}

void TFFMPEGOutputFrame::onEnter(int i, int j)
{
	struct lclS
    {
        int i, j;
        TFFMPEGOutputFrame* f;
        void __fastcall onEnter()
        {
            Log(lInfo) << "Thread was entered..";
            f->CompressBtn->Caption = "Stop Compressing..";
            f->ProgressBar1->Position = 0;
        }
    };
	lclS lcl;
    lcl.i = i;
    lcl.j = j;
    lcl.f = this;
    TThread::Synchronize(0, &lcl.onEnter);
}

void TFFMPEGOutputFrame::onProgress(int i, int j)
{
	struct lclS
    {
        int i, j;
        TFFMPEGOutputFrame* f;
        void __fastcall onProgress()
        {
            f->ProgressBar1->Position = i;
        }
    };
	lclS lcl;
    lcl.i = i;
    lcl.j = j;
    lcl.f = this;
    TThread::Synchronize(0, &lcl.onProgress);
}

void TFFMPEGOutputFrame::onExit(int i, int j)
{
    if(onDone)
    {
    	onDone(this);
    }
}

void __fastcall TFFMPEGOutputFrame::CompressBtnClick(TObject *Sender)
{
	if(CompressBtn->Caption != "Stop Compressing..")
    {

    }
    else
    {
		mVCThread.stop();
    }

}

