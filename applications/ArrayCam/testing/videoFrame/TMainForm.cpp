#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TFFMPEGOutputFrame.h"
#include "database/atDBUtils.h"
#include "TATDBImagesAndMoviesDataModule.h"
#include <ShellAnimations.hpp>
#include "TMovieItemFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma link "TFFMPEGFrame"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTSTDStringEdit"
#pragma link "TATDBConnectionFrame"
#pragma resource "*.dfm"

TMainForm *MainForm;
extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern string 			gApplicationRegistryRoot;
extern string			gAppExeName;
extern bool             gAppIsStartingUp;
using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppExeName, gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, gAppExeName + ".ini"), true, true),
    mLogLevel(lAny)
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolder1Accept(TObject *Sender)
{
	MovieFolder->setValue(stdstr(BrowseForFolder1->Folder));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	try
    {
    	if(!atdbDM)
        {
            throw(string("NULL data module"));
        }
        atdbDM->SQLConnection1->AfterConnect 	= afterDBServerConnect;
        atdbDM->SQLConnection1->AfterDisconnect = afterDBServerDisconnect;
    }
    catch(...)
    {
    	handleMySQLException();
    }
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerConnect(System::TObject* Sender)
{
	Log(lInfo) << "Succesfully connected to DB Server";
	atdbDM->afterConnect();

	//Enable ImagesAndMoviesDM
	TATDBConnectionFrame1->afterConnect();
    ImagesAndMoviesDM->afterConnect();
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerDisconnect(System::TObject* Sender)
{
	Log(lInfo) << "Disconnected from the DB Server";
	atdbDM->afterDisConnect();

	TATDBConnectionFrame1->afterDisconnect();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBLookupListBox1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Log(lInfo) << "Mouse down................................";

    //Refresh Movielist
	SQLQuery1->Open();
}

void __fastcall TMainForm::DBLookupListBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkUp || Key == vkDown || Key == vkLeft|| Key == vkRight)
    {
		SQLQuery1->Open();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBLookupListBox1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkUp || Key == vkDown|| Key == vkLeft|| Key == vkRight)
    {
        //Log(lInfo) << "Key up................................";
        StringList movies = fetchRecords();
        populateMovieFrames(movies);
    }
}

void __fastcall TMainForm::DBLookupListBox1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Log(lInfo) << "Mouse up................................";
    StringList movies = fetchRecords();
	populateMovieFrames(movies);
}


StringList TMainForm::fetchRecords()
{
	StringList movies;

    while(!SQLQuery1->Eof)
    {
		stringstream rec;
        rec <<stdstr(SQLQuery1->FieldByName("created")->AsString) <<"," <<stdstr(SQLQuery1->FieldByName("id")->AsString) <<".mp4";
        movies.append(rec.str());
        Log(lInfo) << "Got record: "<< stdstr(SQLQuery1->FieldByName("id")->AsString) << " at " << stdstr(SQLQuery1->FieldByName("created")->AsString);
        SQLQuery1->Next();
    }

	return movies;
}

void TMainForm::clearMovieFrames()
{
	list<TMovieItemFrame*>::iterator i = mMovies.begin();
    while(i != mMovies.end())
    {
    	delete (*i);
    	mMovies.erase(i++);
    }
}

void TMainForm::populateMovieFrames(const StringList& l)
{
	clearMovieFrames();

    if(l.count())
    {
   		ScrollBox1->VertScrollBar->Visible = false;
    }

    //Create path
    Path p(stdstr(MovieFolder->Text));

    //Current block nr
    int blockID = DBLookupListBox1->KeyValue;

    p.append(dsl::toString(blockID));
	for(int i = 0; i < l.count(); i++)
    {
        StringList item(l[i], ',');
        if(item.count() == 2)
        {
	        File f(Path(p, item[1]));

            TMovieItemFrame* frame = new TMovieItemFrame(f,this);
            frame->Visible = false;
            frame->MovieLbl->Caption = item[0].c_str();
            mMovies.push_back(frame);
        }
        else
        {
        	Log(lError) << "Bad movie record..";
        }
    }

	list<TMovieItemFrame*>::iterator i = mMovies.begin();
    while(i != mMovies.end())
    {
    	(*i)->Parent = FlowPanel1;;
        (*i)->Visible = true;
        i++;
    }

   	ScrollBox1->VertScrollBar->Visible = true;
	NrOfRecordsLbl->setValue(l.count());
}

void __fastcall TMainForm::RefreshUITimerTimer(TObject *Sender)
{
	RefreshUITimer->Enabled = false;
}

