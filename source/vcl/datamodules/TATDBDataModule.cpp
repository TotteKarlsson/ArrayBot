#pragma hdrstop
#include "TATDBDataModule.h"
#include "mtkVCLUtils.h"
#include <sstream>
#include "mtkLogger.h"
#include <iomanip>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma link "DbxDevartSQLite"
#pragma resource "*.dfm"
TatDM *atDM;

using namespace mtk;
using namespace std;

extern bool gAppIsStartingUp;

//---------------------------------------------------------------------------
__fastcall TatDM::TatDM(TComponent* Owner)
	: TDataModule(Owner)
{}

bool __fastcall TatDM::Connect(const string& DatabaseFile)
{
	try
    {
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
void __fastcall TatDM::SQLConnection1AfterConnect(TObject *Sender)
{
	Log(lInfo) << "After Connect";
    abImageDS->Active = true;
	mImageClientDS->Active = true;
	usersDS->Active = true;
    blocksDS->Active = true;
    noteDS->Active = true;
}

void __fastcall TatDM::usersClientDataSetuser_nameGetText(TField *Sender,
          UnicodeString &Text, bool DisplayText)
{
	TWideMemoField* f = dynamic_cast<TWideMemoField*>(Sender);
    if(f == usersClientDataSetuser_name)
    {
		Text = f->AsString;
    }
    else if(f == usersClientDataSetcreated)
    {
        Text = f->AsString;
    }
}

void __fastcall TatDM::usersClientDataSetBeforePost(TDataSet *DataSet)
{
	if(usersClientDataSetuser_name->AsString.IsEmpty())
    {
		throw("Bad");
	}
}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetBeforeApplyUpdates(TObject *Sender,
          OleVariant &OwnerData)
{
//	if()
    {
//        if(usersDSuser_name->AsString == "user name")
//        {
//            throw Exception("Bad user Name");
//        }
    }
//
//    if(usersDSuser_name->AsString.IsEmpty())
//    {
//        throw Exception("Name cannot be empty");
//    }
}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetBeforeInsert(TDataSet *DataSet)
{
//    if(usersDSuser_name->AsString.IsEmpty())
//    {
//        throw Exception("Name cannot be empty");
//    }
}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetAfterPost(TDataSet *DataSet)
{
	usersDS->FieldByName("user_name")->OnValidate(usersDS->FieldByName("user_name"));
	usersClientDataSet->ApplyUpdates(0);

}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetAfterDelete(TDataSet *DataSet)
{
	usersClientDataSet->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetuser_nameValidate(TField *Sender)
{
	MessageDlg("Validating", mtWarning, TMsgDlgButtons() << mbOK, 0);
}

void __fastcall TatDM::usersClientDataSetAfterScroll(TDataSet *DataSet)
{
	;
}

//---------------------------------------------------------------------------
void __fastcall TatDM::usersClientDataSetAfterCancel(TDataSet *DataSet)
{
;
}

//---------------------------------------------------------------------------
void __fastcall TatDM::blocksCDSAfterPost(TDataSet *DataSet)
{
	blocksCDS->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TatDM::blocksCDSAfterDelete(TDataSet *DataSet)
{
	blocksCDS->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TatDM::blocksCDSAfterScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)
    {
    	return;
    }

	int bID = blocksCDS->FieldByName("id")->AsInteger;
	blockNotesQ->Params->ParamByName("blockID")->AsInteger = bID;
    blockNotesQ->Open();

    //Get notes
	string note = stdstr(blockNotesQ->FieldByName("note")->AsString);
	Log(lInfo) << "Note is: "<<note;
	blockNotesQ->Close();

	if(gAppIsStartingUp == false && SQLConnection1->Connected)
	{
		//Update customers orders
		mRibbonCDSet->Active = false;
		TField* field = blocksCDS->FieldByName("id");

		if(field)
		{
			String val = field->AsString;
			ribbonsQ->SQL->Text = "SELECT * from ribbon where block_id ='" + val + "'";

//			Log(lDebug) << stdstr((customerOrdersQ->SQL->Text));
		}
		mRibbonCDSet->Active = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TatDM::blockNotesDSetAfterPost(TDataSet *DataSet)
{
//	blockNotesDSet->ApplyUpdates(0);

}

void __fastcall TatDM::usersDSuser_nameValidate(TField *Sender)
{
//	if(Sender == )
//    {
//
//    }
}

//---------------------------------------------------------------------------
void __fastcall TatDM::blocksCDSBeforePost(TDataSet *DataSet)
{
	Log(lInfo) << "Before Posting Block Data";
}

void __fastcall TatDM::mRibbonCDSetAfterPost(TDataSet *DataSet)
{
	mRibbonCDSet->ApplyUpdates(0);
}
//---------------------------------------------------------------------------

void __fastcall TatDM::mRibbonCDSetBeforePost(TDataSet *DataSet)
{
	Log(lInfo) << "Before Posting Ribbon Data";
}

//---------------------------------------------------------------------------
void __fastcall TatDM::mRibbonCDSetAfterDelete(TDataSet *DataSet)
{
	mRibbonCDSet->ApplyUpdates(0);
}

string zeroPadLeft(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::right << nr;
    return s.str();
}

string zeroPadRight(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::left << nr;
    return s.str();
}

void __fastcall TatDM::mRibbonCDSetCalcFields(TDataSet *DataSet)
{
	//Generate barcode as being composed of
	//    	block_id: first 5 digits
    //		ribbon_id: next 7 digits
	TField* field = blocksCDS->FieldByName("id");
	if(field)
	{
		TField* f = mRibbonCDSet->FieldByName("bar_code");
		if(f)
		{
			stringstream s;
			s << zeroPadRight(blocksCDS->FieldByName("id")->AsInteger,   4);
			string str = s.str();
            s << zeroPadLeft(mRibbonCDSet->FieldByName("id")->AsInteger, 5);
            str = s.str();
			f->Value = toLong(str);
		}
	}
}


void __fastcall TatDM::abImageDSBeforeScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)
    {
    	return;
    }

	int imageID = mImageClientDS->FieldByName("id")->AsInteger;
	blockNotesQ->Params->ParamByName("blockID")->AsInteger = imageID;
    blockNotesQ->Open();

    //Get notes
	string note = stdstr(blockNotesQ->FieldByName("note")->AsString);
	Log(lInfo) << "Note is: "<<note;
	blockNotesQ->Close();

	if(gAppIsStartingUp == false && SQLConnection1->Connected)
	{
		//Update customers orders
		mRibbonCDSet->Active = false;
		TField* field = blocksCDS->FieldByName("id");

		if(field)
		{
			String val = field->AsString;
			ribbonsQ->SQL->Text = "SELECT * from ribbon where block_id ='" + val + "'";

//			Log(lDebug) << stdstr((customerOrdersQ->SQL->Text));
		}
		mRibbonCDSet->Active = true;
	}

}
//---------------------------------------------------------------------------

