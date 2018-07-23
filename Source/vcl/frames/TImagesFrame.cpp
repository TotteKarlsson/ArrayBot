#include <vcl.h>
#pragma hdrstop
#include "TImagesFrame.h"
#include "Poco/File.h"
#include "frames/TImageItemFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "TPGDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
TImagesFrame *ImagesFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TImagesFrame::TImagesFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TImagesFrame::populate(int blockID, Poco::Path& mediaPath)
{
	try
    {
		GetImagesQuery->Open();
	    StringList l = fetchRecords();
		GetImagesQuery->Close();
        clearItemFrames();
        if(l.count())
        {
            ScrollBox2->VertScrollBar->Visible = false;
        }

        //Create path
        Poco::Path p(mediaPath);
        p.append(dsl::toString(blockID));
        Log(lDebug) << "Looking for images in folder: " << p.toString();

        for(int i = 0; i < l.count(); i++)
        {
            StringList item(l[i], ',');
            if(item.count() == 2)
            {
	            Poco::Path itemPath(p, item[1]);
                itemPath.setExtension("jpg");
                Poco::File f(itemPath);
                TImageItemFrame* frame = new TImageItemFrame(f,this);
                frame->Visible = false;
                frame->MovieLbl->Caption = item[0].c_str();
                mItems.push_back(frame);
            }
            else
            {
                Log(lError) << "Bad image item record..";
            }
        }

        list<TImageItemFrame*>::iterator i = mItems.begin();
        while(i != mItems.end())
        {
            (*i)->Parent = FlowPanel1;;
            (*i)->Visible = true;
            i++;
        }

        ScrollBox2->VertScrollBar->Visible = true;
        NrOfRecordsLbl->setValue(l.count());
    }
    catch(...)
    {
    	Log(lError) << "There was a problem...";
    }
}

StringList TImagesFrame::fetchRecords()
{
	StringList records;
    while(!GetImagesQuery->Eof)
    {
		stringstream rec;
        rec <<stdstr(GetImagesQuery->FieldByName("created")->AsString) <<"," <<stdstr(GetImagesQuery->FieldByName("id")->AsString);
        records.append(rec.str());
        Log(lDebug4) << "Got record: "<< stdstr(GetImagesQuery->FieldByName("id")->AsString) << " at " << stdstr(GetImagesQuery->FieldByName("created")->AsString);
        GetImagesQuery->Next();
    }

	return records;
}

void TImagesFrame::clearItemFrames()
{
	list<TImageItemFrame*>::iterator i = mItems.begin();
    while(i != mItems.end())
    {
    	delete (*i);
    	mItems.erase(i++);
    }
}

