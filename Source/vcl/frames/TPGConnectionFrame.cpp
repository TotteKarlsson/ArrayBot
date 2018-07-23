#include <vcl.h>
#pragma hdrstop
#include "TPGConnectionFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TDataModulesUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"

TPGConnectionFrame *PGConnectionFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TPGConnectionFrame::TPGConnectionFrame(TComponent* Owner)
	: TFrame(Owner),
    mIniFile(NULL),
    mDBConnection(NULL)
{
	ConnectA->Caption = "Connect";
}

bool TPGConnectionFrame::init(IniFile* inifile, const string& iniFileSection, TSQLConnection* dbConnection)
{
	mIniFile = inifile;
	if(!mIniFile)
    {
    	return false;
    }
    mProperties.setIniFile(mIniFile);
    mDBConnection = dbConnection;

    mProperties.setSection(iniFileSection);
	mProperties.add((BaseProperty*)  &mServerIPE->getProperty()->setup( 	    "SERVER_IP",        		      	"127.0.0.1"));
	mProperties.add((BaseProperty*)  &mDBUserE->getProperty()->setup( 	    	"DB_USER_NAME",                   "none"));
	mProperties.add((BaseProperty*)  &mPasswordE->getProperty()->setup( 	    "DB_USER_PASSWORD",               "none"));
	mProperties.add((BaseProperty*)  &mDatabaseE->getProperty()->setup( 	    "DB_DB_NAME",    			        "none"));

	//Read from file. Create if file do not exist
	mProperties.read();

	//Update
    updateUI();
    return true;
}

DBCredentials TPGConnectionFrame::getCredentials()
{
	return DBCredentials(mServerIPE->getValue(), mDatabaseE->getValue(), mDBUserE->getValue(), mPasswordE->getValue());
}

bool TPGConnectionFrame::writeParameters()
{
	return mProperties.write();
}

void TPGConnectionFrame::updateUI()
{
    mDBUserE->update();
    mPasswordE->update();
    mDatabaseE->update();
	mServerIPE->update();
}

void TPGConnectionFrame::afterConnect()
{
    mDBUserE->Enabled 	= false;
    mPasswordE->Enabled = false;
    mDatabaseE->Enabled = false;
	mServerIPE->Enabled = false;
    updateUI();
	ConnectA->Caption = "Disconnect";
}

void TPGConnectionFrame::afterDisconnect()
{
    mDBUserE->Enabled = true;
    mPasswordE->Enabled = true;
    mDatabaseE->Enabled = true;
	mServerIPE->Enabled = true;

	ConnectA->Caption = "Connect";
}

//---------------------------------------------------------------------------
void __fastcall TPGConnectionFrame::ConnectAExecute(TObject *Sender)
{
	if(!mDBConnection)
    {
    	Log(lWarning) << "Datamodule not allocated";
        return;
    }

	if(mDBConnection && mDBConnection->Connected)
    {
    	//Remove runtime indices
//    	TClientDataSet* cds = pgDM->specimenCDS;
//        if(cds && cds->IndexDefs)
//        {
//            cds->IndexDefs->Update();
////            for(int i = 0; i < cds->IndexDefs->Count; i++)
//			int count = 2;
//            for(int i = 0; i < count; i++)
//            {
//                String idxName = cds->IndexDefs->operator [](i)->Name;
//                Log(lDebug) <<"Removing index: "<< stdstr(idxName);
//                if(idxName != "DEFAULT_ORDER" && idxName != "CHANGEINDEX")
//                {
//                    try
//                    {
//                        Log(lDebug) <<"Removing index: "<< stdstr(idxName);
//                        //Something bizare is happening here on startup.
//                        cds->DeleteIndex(idxName);
//                    }
//                    catch(...)
//                    {
//                    }
//                }
//            }
//        }
	    mDBConnection->Connected = false;
	    mDBConnection->Close();
    }
    else
    {
	    connect(mServerIPE->getValue(), mDatabaseE->getValue(), mDBUserE->getValue(), mPasswordE->getValue(), mDBConnection);
    }
}

//---------------------------------------------------------------------------
void __fastcall TPGConnectionFrame::GBox1Click(TObject *Sender)
{
    mDBUserE->update();
    mPasswordE->update();
    mDatabaseE->update();
	mServerIPE->update();
}


