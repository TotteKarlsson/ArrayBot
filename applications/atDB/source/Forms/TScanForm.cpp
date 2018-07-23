//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "TScanForm.h"
#include "dslLogger.h"
#include "TCoverSlipScanFrame.h"
#include "dslVCLUtils.h"
#include <DB.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScanForm *ScanForm;

using namespace dsl;


//---------------------------------------------------------------------------
__fastcall TScanForm::TScanForm(Poco::Path p, TComponent* Owner)
	: TForm(Owner),
    CSFrame(NULL),
    mMediaPath(p)
{
}
//---------------------------------------------------------------------------
void __fastcall TScanForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void TScanForm::populate(const string& barcode)
{
	mBCBuilder.setBarCode(barcode);
	onCSBarcode(mBCBuilder.getBarCodeValue());
	mBCBuilder.reset();
}

//---------------------------------------------------------------------------
void __fastcall TScanForm::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	//Intercept string sent from barcode reader
	Log(lInfo) << "Got key.." << (char) Key;
	mBCBuilder.build((char) Key);

    if(Key == '\r')
    {
    	Log(lInfo) << "Got new line.";
        //Check character buffer
        if(mBCBuilder.hasBarCode())
        {
            //Check what we scanned..
            onCSBarcode(mBCBuilder.getBarCodeValue());
        }
		mBCBuilder.reset();
    }
}

void TScanForm::onCSBarcode(int csID)
{
	try
    {
        if(!CSFrame)
        {
            CSFrame = new TCoverSlipScanFrame(this);
            CSFrame->Parent = this;
            CSFrame->Align = alClient;
        }

        CSFrame->GroupBox1->Caption = "Information for coverslip with ID: " + IntToStr(csID);
        CSFrame->populate(csID, mMediaPath);
    }
	catch(const EDatabaseError& e)
    {
    	Log(lWarning) << "There was a database error: "<<stdstr(e.Message);
    }
	catch(const TDBXError& e)
    {
    	Log(lWarning) << stdstr(e.Message);
    }
}
