#pragma hdrstop
#include "TPGImagesAndMoviesDataModule.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TPGDataModule.h"
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TPGImagesAndMoviesDM *PGImagesAndMoviesDM;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TPGImagesAndMoviesDM::TPGImagesAndMoviesDM(TComponent* Owner)
	: TDataModule(Owner)
{}

void TPGImagesAndMoviesDM::afterConnect()
{
    if(!MoviesByBlockIDDS->SQLConnection)
    {
	    MoviesByBlockIDDS->SQLConnection = pgDM->SQLConnection1;
    }

	MoviesByBlockIDCDS->Active = true;
}

void __fastcall TPGImagesAndMoviesDM::MoviesByBlockIDCDSAfterScroll(TDataSet *DataSet)

{
	if(!pgDM->SQLConnection1->Connected)
    {
    	return;
    }

   	if(DataSet == pgDM->blockIDSCDS)
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
void __fastcall TPGImagesAndMoviesDM::MoviesByBlockIDDSBeforeOpen(TDataSet *DataSet)

{
	//Make sure we have a connection
}


//---------------------------------------------------------------------------
void __fastcall TPGImagesAndMoviesDM::MoviesByBlockIDCDSAfterRefresh(TDataSet *DataSet)

{
	Log(lInfo) << "Data was refreshed";

}


