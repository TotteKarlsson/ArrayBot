#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TSpecimenForm.h"
#include "TSlicesForm.h"
#include "TBlockForm.h"
using namespace dsl;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
extern bool gAppIsStartingUp;
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{

    bool connected = false;
	gAppIsStartingUp = false;
    try
    {
	    connected = atdbDM->connect("127.0.0.1", "atdb_client", "atdb123", "atdb");
	    atdbDM->afterConnect();
    }
    catch (const TDBXError &e)
	{
    	Log(lInfo) << "There was a database connection issue: "<<stdstr(e.Message);
	}

	UserCB->KeyValue = 27;
	SpecieRGClick(Sender);
}

TDateTime __fastcall NowUTC()
{
  SYSTEMTIME SystemTime;
  ::GetSystemTime(&SystemTime);
  return EncodeDate(SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay) + EncodeTime(SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, SystemTime.wMilliseconds);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	TDBNavigator* n = dynamic_cast<TDBNavigator*>(Sender);
    if( n == SpecimenNavigator)
    {
        switch(Button)
        {
            case nbInsert:
            {
                    atdbDM->specimenCDS->FieldByName("animal_id")->Value = "XXXX-XX";
                    atdbDM->specimenCDS->FieldByName("entered_by")->Value = UserCB->KeyValue;

                    if(SpecieRG->ItemIndex != -1)
                    {
                        string specie = stdstr(SpecieRG->Items->Strings[SpecieRG->ItemIndex]);
                        atdbDM->specimenCDS->FieldByName("specie")->Value = atdbDM->getIDForSpecie(specie);
                    }

                    TDateTime dt;
                    dt = Now();
                    atdbDM->specimenCDS->FieldByName("intake_date")->Value = dt.CurrentDate();

                    //Open new specimen form
                    openSpecimenForm();

            }
            break;
        }
    }
    else if( n == SlicesNavigator)
    {
        switch(Button)
        {
            case nbInsert:
            {
                    atdbDM->slicesCDS->FieldByName("specimen_id")->Value = atdbDM->specimenCDS->FieldByName("id")->Value;
                    atdbDM->slicesCDS->FieldByName("entered_by")->Value = UserCB->KeyValue;

                    if(SpecieRG->ItemIndex != -1)
                    {
                        string specie = stdstr(SpecieRG->Items->Strings[SpecieRG->ItemIndex]);
                        //atdbDM->slices->FieldByName("specie")->Value = atdbDM->getIDForSpecie(specie);
                    }

                    TDateTime dt;
                    dt = Now();
                    //atdbDM->slices->FieldByName("intake_date")->Value = dt.CurrentDate();

                    //Open new specimen form
                    openSlicesForm();

            }
            break;
        }
    }
    else if( n == BlocksNavigator)
    {
        switch(Button)
        {
            case nbInsert:
            {
                    TDateTime dt;
                    dt = Now();

                    atdbDM->blocksCDS->FieldByName("entered_by")->Value             = UserCB->KeyValue;
                    atdbDM->blocksCDS->FieldByName("entered_on")->Value             = dt.CurrentDate();
		        	atdbDM->blocksCDS->FieldValues["slice_id"] 			            = atdbDM->slicesCDS->FieldByName("id")->AsInteger;
		        	atdbDM->blocksCDS->FieldValues["serial"] 	 		            = atdbDM->blocksCDS->RecordCount + 1;
		        	atdbDM->blocksCDS->FieldByName("date_embedded")->Value 			= dt.CurrentDate();
		        	atdbDM->blocksCDS->FieldValues["status"] 	 					= 0;
		        	atdbDM->blocksCDS->FieldValues["cryoprotection_protocol"]  		= 0;
		        	atdbDM->blocksCDS->FieldValues["freezing_protocol"] 	 		= 0;
		        	atdbDM->blocksCDS->FieldValues["substitution_protocol"]    		= 0;
		        	atdbDM->blocksCDS->FieldValues["infiltration_protocol"]    		= 0;
		        	atdbDM->blocksCDS->FieldValues["embedding_protocol"]    		= 0;

                    //Open form
                    openBlocksForm();
            }
            break;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBGrid_DblClick(TObject *Sender)
{
    TDBGrid* g = dynamic_cast<TDBGrid*>(Sender);
    if(g == DBGrid1)
    {
    	openSpecimenForm();
    }
    else if(g == DBGrid2)
    {
    	openSlicesForm();
    }
    else if(g == BlocksGrid)
    {
    	openBlocksForm();
    }
}

void __fastcall TMainForm::openSpecimenForm()
{
	//Open the currently seleceted record in the form
    TSpecimenForm* f = new TSpecimenForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
        atdbDM->specimenCDS->Post();
        atdbDM->specimenCDS->First();
    }
    else
    {
		atdbDM->specimenCDS->Cancel();
    }
}

void __fastcall TMainForm::openSlicesForm()
{
	//Open the currently seleceted record in the form
    TSlicesForm* f = new TSlicesForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
        atdbDM->slicesCDS->Post();
        atdbDM->slicesCDS->First();
    }
    else
    {
		atdbDM->slicesCDS->Cancel();
    }
}

void __fastcall TMainForm::openBlocksForm()
{
	//Open the currently seleceted record in the form
    TBlockForm* f = new TBlockForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
    	// Create block label
        String str = atdbDM->createBlockLabel();
        atdbDM->blocksCDS->FieldValues["label"] = str;
//        atdbDM->blocksCDS->FieldValues["status"] = 0;


        atdbDM->blocksCDS->Post();
        atdbDM->blocksCDS->First();
    }
    else
    {
		atdbDM->blocksCDS->Cancel();
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
void __fastcall TMainForm::SpecieRGClick(TObject *Sender)
{
    //Apply filter to specimen table
   	string specie = stdstr(SpecieRG->Items->Strings[SpecieRG->ItemIndex]);
    int specieID = atdbDM->getIDForSpecie(specie);

	atdbDM->specimenCDS->Filter = "specie = '" + IntToStr(specieID) + "'";
    atdbDM->specimenCDS->Filtered = true;
}


