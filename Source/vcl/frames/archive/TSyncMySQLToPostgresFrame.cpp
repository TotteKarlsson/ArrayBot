#include <vcl.h>
#pragma hdrstop
#include "TSyncMySQLToPostgresFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"
#pragma resource "*.dfm"
TSyncMySQLToPostgresFrame *SyncMySQLToPostgresFrame;

using namespace dsl;


//---------------------------------------------------------------------------
__fastcall TSyncMySQLToPostgresFrame::TSyncMySQLToPostgresFrame(TComponent* Owner)
	: TFrame(Owner),
    mIniFile(NULL)
{
	mSyncThread.assignCallBacks(onStarted, onProgress, onFinished);
}

bool TSyncMySQLToPostgresFrame::writeParameters()
{
	return mProperties.write();
}

//---------------------------------------------------------------------------
void TSyncMySQLToPostgresFrame::setAppArguments(const string& args)
{
	mSyncThread.setAppArguments(args);
}

bool TSyncMySQLToPostgresFrame::init(IniFile* inifile, const string& iniFileSection)
{
	mIniFile = inifile;
	if(!mIniFile)
    {
    	return false;
    }
    mProperties.setIniFile(mIniFile);

    mProperties.setSection(iniFileSection);
	mProperties.add((BaseProperty*)  &SyncScriptFile->getProperty()->setup( 	    "DB_SYNC_SCRIPT_FILE",        		      	"something.s2p"));

	//Read from file. Create if file do not exist
	mProperties.read();

	//Update
	SyncScriptFile->update();
    return true;
}

bool TSyncMySQLToPostgresFrame::run()
{
	SyncLogMemo->Clear();
	return mSyncThread.start();
}

void TSyncMySQLToPostgresFrame::onStarted(int* a, int* b)
{
	SyncButton->Caption = "Abort";
	SyncLogMemo->Lines->Add("Starting sync...");
}

void TSyncMySQLToPostgresFrame::onProgress(int* a, int* b)
{
	if(a)
    {
    	string* s = (string*) a;
		SyncLogMemo->Lines->Add(vclstr(*s));
    }
}

void TSyncMySQLToPostgresFrame::onFinished(int* a, int* b)
{
	SyncButton->Caption = "Sync";
	SyncLogMemo->Lines->Add("Done...");
}

//---------------------------------------------------------------------------
void __fastcall TSyncMySQLToPostgresFrame::SyncButtonClick(TObject *Sender)
{
	//Populate objects and start thread
    if(mSyncThread.isRunning() && SyncButton->Caption == "Abort")
    {
    	mSyncThread.stop();
    }
    else
    {
        stringstream args;
        string cwd = getCWD();
        args <<"--profile=\""   	<< joinPath(cwd, SyncScriptFile->getValue()) 			<< "\" ";
        setAppArguments(args.str());
        run();
    }
}

