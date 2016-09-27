#include <vcl.h>
#pragma hdrstop
#include "mtkVCLUtils.h"
#include "MainForm.h"
#include "mtkLogger.h"
#include "forms/TBlockEntryForm.h"
#include "Poco/Data/RecordSet.h"
#include <Poco/Data/MySQL/MySQLException.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern string 			gApplicationRegistryRoot;
extern string 			gApplicationName;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, (gApplicationName + ".ini")), true, true),
    mLogLevel(lAny)

{
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	 lAny));
    mProperties.read();
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject *Sender)
{
	mLogFileReader.start();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void __fastcall TMain::ArrayBotButton1Click(TObject *Sender)
{
	if(!mServerSession.isConnected())
    {
		mServerSession.connect();
    }

    if(mServerSession.isConnected())
    {
    	//Fetch data
        RecordSet *rs =  mServerSession.getUsers();
        if(!rs->rowCount())
        {
        	Log(lInfo) << "There is no data in this table";
        }
        else
        {
        	try
            {
                bool more = rs->moveFirst();
                int cols = rs->columnCount();
                int rows = rs->rowCount();

	            // print all column names
                stringstream cs;
    	        for (std::size_t col = 0; col < cols; ++col)
                {
        	        cs << rs->columnName(col);
                    if(col < cols -1)
                    {
                    	cs <<"\t";
                    }
                }

				Log(lInfo) << cs.str();

    	        // iterate over all rows and columns
	            for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
                {
	                Poco::Data::Row& row = *it;
                    for(int col = 0; col < cols; ++col)
                    {
                        Log(lInfo) << row[col].convert<std::string>();
                    }
                }
            }
            catch(...)
            {
		    	Log(lError) << ".....";
            }
        }
    }
    else
    {
    	Log(lError) << "Failed to connect to database server...";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::ArrayBotButton2Click(TObject *Sender)
{
	//Open a Register Block form
    TBlockEntryForm* f = new TBlockEntryForm(mServerSession, this);

    try
    {
    	int mr = f->ShowModal();
        if(mr == mrOk)
        {
            //Capture data and submit to database
            Log(lInfo) << "Populating DB";
            mServerSession.insertBlock(7, stdstr(f->mBlockLabel->Text), stdstr(f->mBlockNote->Text));

        }
        else
        {
        	Log(lInfo) << "Canceled Populating DB";
        }

    }
   	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        Log(lError) << e.message() <<endl;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        Log(lError) << e.message() << endl;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        Log(lError) << e.message() << endl;
    }

    catch(...)
    {}

    delete f;

}
//---------------------------------------------------------------------------

