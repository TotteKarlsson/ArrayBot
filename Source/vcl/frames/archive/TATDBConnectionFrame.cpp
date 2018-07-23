#include <vcl.h>
#pragma hdrstop
#include "TATDBConnectionFrame.h"
#include "database/atDBUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TATDBDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"

#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

TATDBConnectionFrame *ATDBConnectionFrame;
using namespace dsl;
using namespace at;

//---------------------------------------------------------------------------
__fastcall TATDBConnectionFrame::TATDBConnectionFrame(TComponent* Owner)
	: TFrame(Owner),
    mIniFile(NULL)
{
	ConnectA->Caption = "Connect";
}

bool TATDBConnectionFrame::init(IniFile* inifile, const string& iniFileSection)
{
	mIniFile = inifile;
	if(!mIniFile)
    {
    	return false;
    }
    mProperties.setIniFile(mIniFile);

    mProperties.setSection(iniFileSection);
	mProperties.add((BaseProperty*)  &mServerIPE->getProperty()->setup( 	    "SERVER_IP",        		      	"127.0.0.1"));
	mProperties.add((BaseProperty*)  &mDBUserE->getProperty()->setup( 	    	"DB_USER_NAME",                   "none"));
	mProperties.add((BaseProperty*)  &mPasswordE->getProperty()->setup( 	    "DB_USER_PASSWORD",               "none"));
	mProperties.add((BaseProperty*)  &mDatabaseE->getProperty()->setup( 	    "DB_DB_NAME",    			        "none"));

	//Read from file. Create if file do not exist
	mProperties.read();

	//Update
    mDBUserE->update();
    mPasswordE->update();
    mDatabaseE->update();
	mServerIPE->update();
    return true;
}

bool TATDBConnectionFrame::writeParameters()
{
	return mProperties.write();
}

void TATDBConnectionFrame::afterConnect()
{
	ConnectA->Caption = "Disconnect";
}

void TATDBConnectionFrame::afterDisconnect()
{
	ConnectA->Caption = "Connect";
}

//---------------------------------------------------------------------------
void __fastcall TATDBConnectionFrame::ConnectAExecute(TObject *Sender)
{
	if(!atdbDM)
    {
    	Log(lWarning) << "Datamodule not allocated";
        return;
    }

	if( atdbDM->SQLConnection1 && atdbDM->SQLConnection1->Connected)
    {
    	//Remove runtime indices
//    	TClientDataSet* cds = atdbDM->specimenCDS;
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
	    atdbDM->SQLConnection1->Connected = false;
	    atdbDM->SQLConnection1->Close();
    }
    else
    {
	    atdbDM->connect(mServerIPE->getValue(), mDBUserE->getValue(), mPasswordE->getValue(), mDatabaseE->getValue());
    }
}


