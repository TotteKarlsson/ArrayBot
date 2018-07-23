#include <vcl.h>
#pragma hdrstop
#include "TMoviesFrame.h"
#include "Poco/File.h"
#include "frames/TMovieItemFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "TPGDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
TMoviesFrame *MoviesFrame;
using namespace dsl;


//---------------------------------------------------------------------------
__fastcall TMoviesFrame::TMoviesFrame(TComponent* Owner)
	: TFrame(Owner)
{}

StringList TMoviesFrame::fetchRecords()
{
	StringList records;
    while(!GetMoviesQuery->Eof)
    {
		stringstream rec;
        rec <<stdstr(GetMoviesQuery->FieldByName("created")->AsString) <<"," <<stdstr(GetMoviesQuery->FieldByName("id")->AsString) <<"."<<stdstr(GetMoviesQuery->FieldByName("fileextension")->AsString);
        records.append(rec.str());
        Log(lDebug4) << "Got record: "<< stdstr(GetMoviesQuery->FieldByName("id")->AsString) << " at " << stdstr(GetMoviesQuery->FieldByName("created")->AsString);
        GetMoviesQuery->Next();
    }

	return records;
}


void TMoviesFrame::populate(int blockID, const Poco::Path& mediaPath)
{
	try
    {
	    GetMoviesQuery->SQL->Clear();
		GetMoviesQuery->SQL->Add("SELECT id,created,fileextension from movies where block_id=:bid ORDER by created DESC");

		GetMoviesQuery->Params->ParamByName("bid")->Value = blockID;
		GetMoviesQuery->Open();

	    StringList l = fetchRecords();
		GetMoviesQuery->Close();
        clearMovieFrames();
        if(l.count())
        {
            ScrollBox2->VertScrollBar->Visible = false;
        }

        //Create path
        Poco::Path p(mediaPath);
        p.append(dsl::toString(blockID));
        Log(lDebug) << "Looking for movies in folder: " << p.toString();

        for(int i = 0; i < l.count(); i++)
        {
            StringList item(l[i], ',');
            if(item.count() == 2)
            {
                Poco::File f(Poco::Path(p, item[1]));

                TMovieItemFrame* frame = new TMovieItemFrame(f,this);
                frame->Visible = false;
                frame->MovieLbl->Caption = item[0].c_str();
                mMovies.push_back(frame);
	            frame->Parent = FlowPanel1;
                frame->Visible = true;
            }
            else
            {
                Log(lError) << "Bad movie record..";
            }
        }

        ScrollBox2->VertScrollBar->Visible = true;
        NrOfRecordsLbl->setValue(l.count());
    }
    catch(const Exception& e)
    {
    	Log(lError) << "There was a problem:" << stdstr(e.Message);
        MessageDlg(String("Error: ") + e.Message, mtError, TMsgDlgButtons() << mbOK, 0);
    }
}

void TMoviesFrame::populate(int blockID, const string& ribbonID, const Poco::Path& mediaPath)
{
	try
    {
	    GetMoviesQuery->SQL->Clear();
		GetMoviesQuery->SQL->Add("SELECT id,created,fileextension from movies where block_id=:bid AND ribbon_id=:rid ORDER by created DESC");

		GetMoviesQuery->Params->ParamByName("bid")->Value = blockID;
		GetMoviesQuery->Params->ParamByName("rid")->Value = ribbonID.c_str();
		GetMoviesQuery->Open();
	    StringList l = fetchRecords();
		GetMoviesQuery->Close();
        clearMovieFrames();
        if(l.count())
        {
            ScrollBox2->VertScrollBar->Visible = false;
        }

        //Create path
        Poco::Path p(mediaPath);
        p.append(dsl::toString(blockID));
        Log(lDebug) << "Looking for movies in folder: " << p.toString();

        for(int i = 0; i < l.count(); i++)
        {
            StringList item(l[i], ',');
            if(item.count() == 2)
            {
                Poco::File f(Poco::Path(p, item[1]));

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

        ScrollBox2->VertScrollBar->Visible = true;
        NrOfRecordsLbl->setValue(l.count());
    }
    catch(const Exception& e)
    {
    	Log(lError) << "There was a problem:" << stdstr(e.Message);
        MessageDlg(String("Error: ") + e.Message, mtError, TMsgDlgButtons() << mbOK, 0);
    }
}

void TMoviesFrame::clearMovieFrames()
{
	list<TMovieItemFrame*>::iterator i = mMovies.begin();
    while(i != mMovies.end())
    {
    	delete (*i);
    	mMovies.erase(i++);
    }
}

