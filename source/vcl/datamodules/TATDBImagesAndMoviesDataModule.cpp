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

bool __fastcall TImagesAndMoviesDM::Connect(const string& DatabaseFile)
{
	try
    {
//DriverName=DevartSQLite
//DriverUnit=DbxDevartSQLite
//DriverPackageLoader=TDBXDynalinkDriverLoader,DBXCommonDriver170.bpl
//MetaDataPackageLoader=TDBXDevartSQLiteMetaDataCommandFactory,DbxDevartSQLiteDriver170.bpl
//ProductName=DevartSQLite
//LibraryName=dbexpsqlite40.dll
//VendorLib=sqlite3.dll
//Database=C:\Users\matsk\AppData\Local\ArrayBot\atDB.db
//LocaleCode=0000
//IsolationLevel=ReadCommitted
//ASCIIDataBase=False
//BusyTimeout=0
//EnableSharedCache=False
//MaxBlobSize=-1
//FetchAll=True
//ForceCreateDatabase=False
//ForeignKeys=True
//UseUnicode=True
//EnableLoadExtension=False
//BlobSize=-1
//
//
	   Poco::ScopedLock<Poco::Mutex> lock(ImagesAndMoviesDM->mSQLiteMutex);
       SQLConnection1->Connected = false;
       SQLConnection1->Params->Values[_D("Database")] = vclstr(DatabaseFile);
       SQLConnection1->Connected= true;

    }
    catch (const Exception &E)
    {
       Application->MessageBox(E.Message.c_str(), _D("Error connecting to database"),  MB_ICONSTOP | MB_OK);
    }

    return SQLConnection1->Connected;
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::imagesCDSAfterScroll(TDataSet *DataSet)
{
    Poco::ScopedLock<Poco::Mutex> lock(ImagesAndMoviesDM->mSQLiteMutex);
    TField* field = imagesCDS->FieldByName("id");
    if(field)
    {
        String val = field->AsString;
        imageNote->SQL->Text 	= "SELECT * from abImage_note where image_id ='" + val + "'";
        notesQ->SQL->Text 		= "SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_note WHERE image_id = '" + val + "')";


            imageNoteCDS->Refresh();
            notesCDS->Refresh();
    }
    imageNote->Active = true;
    notesQ->Active = true;

}
//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::SQLConnection1AfterConnect(TObject *Sender)
{
    Poco::ScopedLock<Poco::Mutex> lock(ImagesAndMoviesDM->mSQLiteMutex);
	Log(lInfo) << "After Connect (Images and Movies)";
    Log(lInfo) << "Connected to database: "<< stdstr(SQLConnection1->Params->Values["Database"]);

    try
    {
        notesQ->Active 			= true;
        notesCDS->Active 		= true;
        imageNoteCDS->Active 	= true;
        imagesCDS->Active 		= true;
        sensorsCDS->Active 		= true;
    }
    catch(...)
    {
		Log(lError) << "Failed to make active";
    }
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
    Poco::ScopedLock<Poco::Mutex> lock(ImagesAndMoviesDM->mSQLiteMutex);
	Log(lDebug3) <<"Note ID:" << notesCDS->FieldByName("id")->AsInteger;
}


