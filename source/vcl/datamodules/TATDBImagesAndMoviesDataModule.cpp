#pragma hdrstop
#include "TATDBImagesAndMoviesDataModule.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma link "DbxDevartSQLite"
#pragma resource "*.dfm"
TImagesAndMoviesDM *ImagesAndMoviesDM;
extern bool gAppIsStartingUp;
//---------------------------------------------------------------------------
__fastcall TImagesAndMoviesDM::TImagesAndMoviesDM(TComponent* Owner)
	: TDataModule(Owner)
{}

bool __fastcall TImagesAndMoviesDM::connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db)
{
	try
    {
	    mDataBase = db;
        mDataBaseUser = dbUser;
        mDataBaseUserPassword = dbPassword;
        mDBIP = ip;

        SQLConnection1->KeepConnection = true;
    	SQLConnection1->Connected = false;
       	SQLConnection1->Params->Values[_D("HostName")] = vclstr(mDBIP);
       	SQLConnection1->Params->Values[_D("Database")] = vclstr(mDataBase);
       	SQLConnection1->Params->Values[_D("User_Name")] = vclstr(mDataBaseUser);
       	SQLConnection1->Params->Values[_D("Password")] = vclstr(mDataBaseUserPassword);
       	SQLConnection1->Connected= true;
    }
    catch (const Exception &E)
    {
       Application->MessageBox(E.Message.c_str(), _D("Error connecting to database"),  MB_ICONSTOP | MB_OK);
    }

    return SQLConnection1->Connected;
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::SQLConnection1BeforeConnect(TObject *Sender)
{
	Log(lInfo) <<"Trying to connect to SQL server:";
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::SQLConnection1AfterConnect(TObject *Sender)
{
	afterConnect();
}

void __fastcall TImagesAndMoviesDM::afterConnect()
{
	if(gAppIsStartingUp)
    {
    	return;
    }

	Log(lInfo) << "After Connect (Images and Movies)";
    Log(lInfo) << "Connected to database: "<< stdstr(SQLConnection1->Params->Values["Database"]);

    try
    {
//        notesQ->Active 			= true;
//        notesCDS->Active 		= true;
//        imageNoteCDS->Active 	= true;
        imagesCDS->Active 		= true;
//        sensorsCDS->Active 		= true;
    }
    catch(...)
    {
		Log(lError) << "Failed to make active";
    }



	Log(lInfo) << "Connection established to: "<<mDataBase;
}

void __fastcall TImagesAndMoviesDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mDataBase;
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::imagesCDSAfterScroll(TDataSet *DataSet)
{
    TField* field = imagesCDS->FieldByName("id");
    if(field)
    {
        String val = field->AsString;
//        imageNote->SQL->Text 	= "SELECT * from umimage_note where image_id ='" + val + "'";
//        notesQ->SQL->Text 		= "SELECT * FROM note WHERE id IN (SELECT note_id FROM umimage_note WHERE image_id = '" + val + "')";
//
//
//            imageNoteCDS->Refresh();
//            notesCDS->Refresh();
    }
//    imageNote->Active = true;
//    notesQ->Active = true;
}


void __fastcall TImagesAndMoviesDM::imagesCDSdateGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
	Text = FormatDateTime( "yy-mm-dd", Sender->AsDateTime );
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::notesCDScreated_onGetText(TField *Sender,
          UnicodeString &Text, bool DisplayText)
{
	if(!Sender->IsNull)
    {
		Text = FormatDateTime( "yy-mm-dd", Sender->AsDateTime );
    }
    else
    {
    	Text = "";
    }
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::notesCDSAfterScroll(TDataSet *DataSet)
{
	Log(lDebug3) <<"Note ID:" << notesCDS->FieldByName("id")->AsInteger;
}



