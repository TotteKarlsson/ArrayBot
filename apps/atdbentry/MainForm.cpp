#include <vcl.h>
#pragma hdrstop
#include "mtkVCLUtils.h"
#include "MainForm.h"
#include "mtkLogger.h"
#include "forms/TBlockEntryForm.h"
#include "Poco/Data/RecordSet.h"
#include <Poco/Data/MySQL/MySQLException.h>
#include "abDBUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "RzGrids"
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
	mConnectDBBtnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mConnectDBBtnClick(TObject *Sender)
{
	try
    {
        if(!mServerSession.isConnected())
        {
            mServerSession.connect();
        }

        if(mServerSession.isConnected())
        {
            populateUsers();
            mUserIDLbl->Caption = getCurrentUserID();
            syncGrids();
        }
        else
        {
            Log(lError) << "Failed to connect to database server...";
        }
    }
    catch(...)
    {
    	handleMySQLException();
    }
}


void TMain::syncGrids()
{
	try
    {
		mNotesGrid->ColCount = 0;
		mNotesGrid->RowCount = 0;
        mNotesMemo->Clear();

        mBlocksT->ColCount = 0;
        mBlocksT->RowCount = 0;

    	//Fetch data
        RecordSet *rs =  mServerSession.getBlocks(dbDescending);

        if(!rs->rowCount())
        {
        	Log(lInfo) << "There is no data in this table";
        }
        else
        {
            int cols = rs->columnCount();
            int rows = rs->rowCount();

            mBlocksT->ColCount = cols;
            mBlocksT->RowCount = rows + 1;

            // Get column names
            stringstream cs;
            for (std::size_t col = 0; col < cols; ++col)
            {
                mBlocksT->Cells[col][0] = vclstr(rs->columnName(col));
            }

            // iterate over all rows and columns
            int r = 1;
            for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
            {
                Poco::Data::Row& row = *it;
                for(int c = 0; c < cols; ++c)
                {
                    Log(lInfo) << row[c].convert<std::string>();
                    mBlocksT->Cells[c][r] = vclstr(row[c].convert<std::string>());
                }
                r++;
            }
            mBlocksT->Row = 1;
    	}
    }
    catch(...)
    {
        Log(lError) << ".....";
    }
}

int TMain::getCurrentUserID()
{
	int i = mUserCB->ItemIndex;

    if(i > -1)
    {
    	return * ((int*) mUserCB->Items->Objects[i]);
    }

	return  -1;
}

void TMain::populateUsers()
{
    try
    {
        //Fetch data
        mUserCB->Clear();
        RecordSet *rs =  mServerSession.getUsers();
        if(!rs->rowCount())
        {
            Log(lInfo) << "There are no users...";
        }
        else
        {
            int cols = rs->columnCount();
            int rows = rs->rowCount();

            // iterate over all rows and columns
            for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
            {
                Poco::Data::Row& row = *it;
                string user(row[1].convert<std::string>());
                int *userId = new int(row[0].convert<int>());
                mUserCB->Items->AddObject(user.c_str(), (TObject*) userId );
                Log(lInfo) <<user;
            }
            mUserCB->ItemIndex = 0;
        }
    }
    catch(...)
    {
    	handleMySQLException();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mRegisterBlockBtnClick(TObject *Sender)
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
            mServerSession.insertBlock(getCurrentUserID(), stdstr(f->mBlockLabel->Text), stdstr(f->mBlockNote->Text));
			syncGrids();
        }
        else
        {
        	Log(lInfo) << "Canceled Populating DB";
        }

    }
    catch(...)
    {
    	handleMySQLException();
    }
    delete f;
}

int TMain::getCurrentBlockID()
{
    int r =  mBlocksT->Row;
    if(r < 0)
    {
    	return -1;
    }

    int blockID = mBlocksT->Cells[0][r].ToInt();
	return blockID;
}

//---------------------------------------------------------------------------
void __fastcall TMain::mBlocksTClick(TObject *Sender)
{
	//Capture row
    int r =  mBlocksT->Row;
    stringstream s;
    for(int c = 0; c < mBlocksT->ColCount; c++)
    {
    	String v = mBlocksT->Cells[c][r];
    	s << stdstr(v) ;
        s << "\t";
    }

    //Check if there are notes for this block
    int blockID = mBlocksT->Cells[0][r].ToInt();

   	//Fetch data
	try
    {
        RecordSet *notes =  mServerSession.getNotesForBlockWithID(blockID);
        if(notes)
        {
            populateNotes(notes);
        }

        mBlockIDEdit->Text = vclstr(mtk::toString(blockID));
        Log(lInfo) << s.str();
        mDeleteRowB->Enabled = (r > -1) ? true : false;
    }
    catch(...)
    {
    	handleMySQLException();
    }
}

void TMain::populateNotes(RecordSet* rs)
{
     mNotesGrid->ColCount = 0;
     mNotesGrid->RowCount = 0;

    //Fetch data
    if(!rs->rowCount())
    {
        Log(lInfo) << "There is no data in this table";
    }
    else
    {
        int cols = 3;
        int rows = rs->rowCount();

        mNotesGrid->ColCount = cols;
        mNotesGrid->RowCount = rows + 1;

        mNotesGrid->ColWidths[0] = 0;
        mNotesGrid->ColWidths[1] = 0;

        //Use only created on
        mNotesGrid->Cells[0][0] = vclstr(rs->columnName(0));
        mNotesGrid->Cells[1][0] = vclstr(rs->columnName(1));
        mNotesGrid->Cells[2][0] = vclstr(rs->columnName(2));


        // iterate over all rows and columns
        int r = 1;
        for (RecordSet::Iterator it = rs->begin(); it != rs->end(); ++it)
        {
            Poco::Data::Row& row = *it;
            mNotesGrid->Cells[0][r] = vclstr(row[0].convert<std::string>());
            mNotesGrid->Cells[1][r] = vclstr(row[1].convert<std::string>());
            mNotesGrid->Cells[2][r] = vclstr(row[2].convert<std::string>());
            r++;
        }

		//Select first row
        mNotesGrid->Row = 1;
		mNotesGridClick(NULL);
    }
}


void __fastcall TMain::Button2Click(TObject *Sender)
{
	infoMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mDeleteRowBClick(TObject *Sender)
{
	//Get selected row id
   	int r =  mBlocksT->Row;
	int blockId = mBlocksT->Cells[0][r].ToInt();

	try
    {
		mServerSession.deleteBlock(blockId);
    }
    catch(...)
    {
    	handleMySQLException();
    }

   	syncGrids();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mNotesGridClick(TObject *Sender)
{
	//Capture row
    int r =  mNotesGrid->Row;

    //Populate memo with the actual note
    mNotesMemo->Clear();

    string note = stdstr(mNotesGrid->Cells[1][r]);

    StringList l(note,'\n');
    for(int line = 0; line < l.count(); line++)
    {
		mNotesMemo->Lines->Add(l[line].c_str());
    }
}

int	 TMain::getCurrentNoteID()
{
    int r =  mNotesGrid->Row;
    if(r < 0)
    {
    	return -1;
    }

    int id = mNotesGrid->Cells[0][r].ToInt();
	return id;

}

//---------------------------------------------------------------------------
void __fastcall TMain::mAddNoteBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    //Capture row
    int r =  mNotesGrid->Row;
    int  blockID = getCurrentBlockID();

    if(b == mAddNoteBtn)
    {
        mServerSession.addNoteForBlockWithID(blockID, getCurrentUserID());
        mBlocksTClick(Sender);
        //Select last note
		mNotesGrid->Row = mNotesGrid->RowCount - 1;
    }

    if( b == mDeleteNoteBtn )
    {
		int noteID = getCurrentNoteID();
        try
        {
        	mServerSession.deleteNoteWithID(noteID);
            mBlocksTClick(Sender);
            mNotesMemo->Clear();
        }
        catch(...)
        {
            handleMySQLException();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mUpdateNoteBtnClick(TObject *Sender)
{
	//update note field
    //Get not id
    int noteRow = mNotesGrid->Row;
    int noteID = mNotesGrid->Cells[0][noteRow].ToInt();

    StringList l;
    for(int i = 0; i < mNotesMemo->Lines->Count; i++)
    {
    	l.insertAt(0, stdstr(mNotesMemo->Lines->Strings[i]));
    }
    string note = l.asString();
    mServerSession.updateNoteWithID(noteID, note);
}


void __fastcall TMain::mUserCBCloseUp(TObject *Sender)
{
	mUserIDLbl->Caption = getCurrentUserID();
}


