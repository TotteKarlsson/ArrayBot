#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkStringList.h"
#include "abUtilities.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "abExceptions.h"
#include "TBlockEntryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TIntLabel"
#pragma link "TPropertyCheckBox"
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
    mLogLevel(lAny),
    mServerSession()
{
	//Setup UI/INI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	 lAny));
    mProperties.read();

//    mLogFileReader.assignOnMessageCallBack(NULL);
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
   	mLogFileReader.start(true);
	setupWindowTitle();
	gAppIsStartingUp = false;


	this->Visible = true;
	gLogger.setLogLevel(mLogLevel);

	LogLevelCB->ItemIndex = mLogLevel.getValue() - 2;


	//Setup frames for the Arduinos
	setupUIFrames();
}

//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
}

//---------------------------------------------------------------------------
void __fastcall TMain::mCheckForServerDataBtnClick(TObject *Sender)
{
	if(!mServerSession.isConnected())
    {
		mServerSession.connect();
    }

    if(mServerSession.isConnected())
    {
    	//Fetch data
        RecordSet rs =  mServerSession.getUsers();
        if(!rs.rowCount())
        {
        	Log(lInfo) << "There is no data in this table";
        }
        else
        {
        	try
            {
                bool more = rs.moveFirst();
                int cols = rs.columnCount();
                int rows = rs.rowCount();

	            // print all column names
                stringstream cs;
    	        for (std::size_t col = 0; col < cols; ++col)
                {
        	        cs << rs.columnName(col);
                    if(col < cols -1)
                    {
                    	cs <<"\t";
                    }
                }


				Log(lInfo) << cs.str();

    	        // iterate over all rows and columns
	            for (RecordSet::Iterator it = rs.begin(); it != rs.end(); ++it)
                {
	                Poco::Data::Row& row = *it;

                    for(int col = 0; col < cols; ++col)
                    {
                        Log(lInfo) << row[col].toString(row[col]);
                    }

//	    	        Log(lInfo) << "Row: " << reader.valuesToString() << std::endl;
                	//Log(lInfo) << *it << " ";
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
void __fastcall TMain::Button3Click(TObject *Sender)
{
	//Open a Register Block form
    TBlockEntryForm* f = new TBlockEntryForm(mServerSession, this);

    try
    {
    	int mr = f->ShowModal();
        if(mr == mrOk)
        {
            //Capture data and submit to database

        }

    }
    catch(...)
    {}



    delete f;

}


