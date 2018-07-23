#pragma hdrstop
#include "TATDBImagesAndMoviesDataModule.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TATDBDataModule.h"
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TImagesAndMoviesDM *ImagesAndMoviesDM;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TImagesAndMoviesDM::TImagesAndMoviesDM(TComponent* Owner)
	: TDataModule(Owner)
{}

void TImagesAndMoviesDM::afterConnect()
{
    if(!MoviesByBlockIDDS->SQLConnection)
    {
	    MoviesByBlockIDDS->SQLConnection = atdbDM->SQLConnection1;
    }

	MoviesByBlockIDCDS->Active = true;
}

void __fastcall TImagesAndMoviesDM::MoviesByBlockIDCDSAfterScroll(TDataSet *DataSet)

{
	if(!atdbDM->SQLConnection1->Connected)
    {
    	return;
    }

   	if(DataSet == atdbDM->blockIDSCDS)
    {
    	if(MoviesByBlockIDCDS->Active)
        {
        	MoviesByBlockIDCDS->Refresh();
        }
    }

 	if(DataSet == MoviesByBlockIDDS)
    {
    	if(MoviesByBlockIDCDS->Active)
        {
        	MoviesByBlockIDCDS->Refresh();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::MoviesByBlockIDDSBeforeOpen(TDataSet *DataSet)

{
	//Make sure we have a connection
}


//---------------------------------------------------------------------------
void __fastcall TImagesAndMoviesDM::MoviesByBlockIDCDSAfterRefresh(TDataSet *DataSet)

{
	Log(lInfo) << "Data was refreshed";

}


