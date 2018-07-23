#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TFFMPEGOutputFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "TFFMPEGFrame"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTSTDStringEdit"
#pragma resource "*.dfm"

TMainForm *MainForm;
extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern string 			gApplicationRegistryRoot;
extern string			gAppExeName;
extern bool             gAppIsStartingUp;
using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppExeName, gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "VideoCompressor.ini"), true, true),
    mLogLevel(lAny)
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);
    FileListBox1->Directory = MovieFolder->Text;
}

//---------------------------------------------------------------------------
//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
	string& msg = mLogFileReader.getData();

    if(infoMemo->Lines->Count > 1000)
    {
		infoMemo->Clear();
    }

    if(msg.size())
    {
    	infoMemo->Lines->Insert(0, vclstr(msg));
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TMainForm::CompressBtnClick(TObject *Sender)
{
	//Compress all selected files..

	for(int i = 0; i < FileListBox1->Count; i++)
    {
	    if(FileListBox1->Selected[i])
        {
			string fName = stdstr(FileListBox1->Items->Strings[i]);

            //Make sure this file is not already being compressed
            if(isThisFileBeingCompressed(fName))
            {
            	Log(lWarning) << "This file is already undergoing compression.";
            }
			else
            {
                Log(lInfo) << "Starting compressing file: " << joinPath(MovieFolder->getValue(), fName);
                TFFMPEGOutputFrame* f = new TFFMPEGOutputFrame(this);
                f->Parent = MPEGPanel;
                f->onDone = onCompressionFinished;
                f->setInputFile(fName);
                f->setCompressionOptions(TFFMPEGFrame1->getOutFileArguments(), TFFMPEGFrame1->DeleteSourceFileCB->Checked, TFFMPEGFrame1->RenameSourceFileCB->Checked);
                f->startCompression();
                mCompressionFrames.push_back(f);
            }
        }
    }
}

bool TMainForm::isThisFileBeingCompressed(const string& fName)
{
	//Check for frames to delete
    list<TFFMPEGOutputFrame*>::iterator i;
    string name = getFileNameNoPath(fName);
	for(i = mCompressionFrames.begin(); i != mCompressionFrames.end();)
    {
    	if((*i))
        {
        	if((*i)->getInputFileName() == fName)
            {
            	return true;
            }
            i++;
        }
	}
    return false;
}

void __fastcall TMainForm::onCompressionFinished(TFFMPEGOutputFrame* f)
{
	//Start deleteFrameTimer
	CleanupTimer->Enabled = true;
    FileListBox1->Update();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CleanupTimerTimer(TObject *Sender)
{
	CleanupTimer->Enabled = false;

	//Check for frames to delete
    list<TFFMPEGOutputFrame*>::iterator i;
	for(i = mCompressionFrames.begin(); i != mCompressionFrames.end();)
    {
    	if((*i) && (*i) ->isDone())
        {
        	delete (*i);
            i = mCompressionFrames.erase(i);
        }
        else
        {
        	i++;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolder1Accept(TObject *Sender)
{
	MovieFolder->setValue(stdstr(BrowseForFolder1->Folder));
    FileListBox1->Directory = MovieFolder->Text;
}


