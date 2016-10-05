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

bool __fastcall TImagesAndMoviesDM::Connect(const string& db)
{

//DriverUnit=Data.DBXMySQL
//DriverPackageLoader=TDBXDynalinkDriverLoader,DbxCommonDriver170.bpl
//DriverAssemblyLoader=Borland.Data.TDBXDynalinkDriverLoader,Borland.Data.DbxCommonDriver,Version=17.0.0.0,Culture=neutral,PublicKeyToken=91d62ebb5b0d1b1b
//MetaDataPackageLoader=TDBXMySqlMetaDataCommandFactory,DbxMySQLDriver170.bpl
//MetaDataAssemblyLoader=Borland.Data.TDBXMySqlMetaDataCommandFactory,Borland.Data.DbxMySQLDriver,Version=17.0.0.0,Culture=neutral,PublicKeyToken=91d62ebb5b0d1b1b
//GetDriverFunc=getSQLDriverMYSQL
//LibraryName=dbxmys.dll
//LibraryNameOsx=libsqlmys.dylib
//VendorLib=LIBMYSQL.dll
//VendorLibWin64=libmysql.dll
//VendorLibOsx=libmysqlclient.dylib
//HostName=127.0.0.1
//Database=umlocal
//User_Name=atdb_client
//Password=atdb123
//MaxBlobSize=-1
//LocaleCode=0000
//Compressed=False
//Encrypted=False
//BlobSize=-1
//ErrorResourceFile=


	try
    {
       SQLConnection1->Connected = false;
       SQLConnection1->Params->Values[_D("Database")] = vclstr(db);
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
    TField* field = imagesCDS->FieldByName("id");
    if(field)
    {
        String val = field->AsString;
        imageNote->SQL->Text 	= "SELECT * from umimage_note where image_id ='" + val + "'";
        notesQ->SQL->Text 		= "SELECT * FROM note WHERE id IN (SELECT note_id FROM umimage_note WHERE image_id = '" + val + "')";


            imageNoteCDS->Refresh();
            notesCDS->Refresh();
    }
    imageNote->Active = true;
    notesQ->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::SQLConnection1AfterConnect(TObject *Sender)
{
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
	Log(lDebug3) <<"Note ID:" << notesCDS->FieldByName("id")->AsInteger;
}


