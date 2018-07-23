#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "Forms/TRegisterNewRibbonForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
//#include "ArrayCamUtils.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::RegisterRibbonBtnClick(TObject *Sender)
{
	//Check that we have a valid barcode for the coverslip
    //Block Label
    System::Variant lbl = pgDM->allBlocksCDS->FieldByName("label")->Value;
    if(BarcodeLbl->Caption == "" || lbl.IsNull())
    {
    	MessageDlg("A valid coverslip barcode and a valid block is necesarry for ribbon registration!", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
    else
    {
		//Make sure the barcode exists in the database..
        TSQLQuery* tq = new TSQLQuery(NULL);
        tq->SQLConnection = pgDM->SQLConnection1;
        tq->SQLConnection->AutoClone = false;
        stringstream q;
        q <<"SELECT * FROM coverslips where id = "<<extractCoverSlipID(stdstr(BarcodeLbl->Caption));
        tq->SQL->Add(q.str().c_str());
        int affected = tq->ExecSQL();

        if(tq->RecordCount < 1)
        {
        	MessageDlg("This barcode could not be found in the database.. can't continue registration.\nChange or register a proper barcode!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
        else
        {
            TRegisterNewRibbonForm* rrf = new TRegisterNewRibbonForm(*this);
            rrf->setCoverSlipBarcode(stdstr(BarcodeLbl->Caption));

            if(rrf->ShowModal() == mrOk)
            {
                Log(lInfo) << "Ribbon "<<rrf->getRibbonID() << " was registered";
                mUC7.getSectionCounter().reset();
                mUC7.getRibbonOrderCounter().increase(1);
				RibbonOrderCountLabel->update();
            }
            delete rrf;
        }
        delete tq;
    }
}

//---------------------------------------------------------------------------
int	TMainForm::getZebraCOMPortNumber()
{
	return mZebraCOMPortCB->ItemIndex + 1;
}

void __fastcall TMainForm::ConnectZebraBtnClick(TObject *Sender)
{
	int Comport = getZebraCOMPortNumber();
   	if(mConnectZebraBtn->Caption == "Open")
    {
        if(mZebra.connect(Comport, mZebraBaudRate, this->Handle) != true)
        {
        	Log(lError) << "Failed to connect barcode reader";
        }
    }
    else
    {
    	mZebra.disconnect();
    }

    if(mZebra.isConnected())
    {
	    onConnectedToZebra();
    }
    else
    {
    	onDisConnectedToZebra();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onConnectedToZebra()
{
    mConnectZebraBtn->Caption = "Close";
    enableDisableGroupBox(mImagerSettingsGB, true);
	Log(lInfo) << "Connected to a Zebra barcode scanner";
    mZebra.scanDisable();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onDisConnectedToZebra()
{
    mConnectZebraBtn->Caption = "Open";
    enableDisableGroupBox(mImagerSettingsGB, false);
	Log(lInfo) << "DisConnected from a Zebra barcode scanner";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DecodeBarcodeClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    int status(-1);
    if(b == BeepBtn)
    {
		int status = mZebra.beep(ONESHORTLO);
    }
    else if(b == DecodeSessionBtn)
    {
    	if(b->Caption == "Scan Barcode")
        {
        	//Start session
            BarcodeLbl->Caption = "";
            mZebra.scanEnable();
            sleep(150);
			status = mZebra.startDecodeSession();
			b->Caption = "Stop Scan";
        }
        else
        {
        	//Stop session
			status = mZebra.stopDecodeSession();
            b->Caption = "Scan Barcode";
            Sleep(100);
            mZebra.scanDisable();
        }
    }

    Log(lInfo) << "Command return status: "<<status;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onWMDecode(TMessage& Msg)
{
	WPARAM w = Msg.WParam;
    LPARAM l = Msg.LParam;

	//Time do decode
    Log(lInfo) << "Got a onWMDecode message..";

    // wparam contains the status bits for the data ,
	// lparam is the length of the data in bytes (cast to int).
	unsigned char decodeBuffer[3001];

	// first thing is to copy the contents of the dll's data buffer to our own.
	if((l < 3000) && ((w & BUFFERSIZE_MASK) == BUFFERSIZE_GOOD))
	{
		memcpy(decodeBuffer, mZebra.getMemoryBuffer(), l);
		decodeBuffer[l] = 0;
	}
	else if( l && ((w & BUFFERSIZE_MASK) == BUFFERSIZE_ERROR ))
    {
		strcpy((char *)decodeBuffer, "TOO MUCH DECODE DATA");
    }
	else
   	{
    	strcpy((char *)decodeBuffer, "NO DECODE STORAGE BUFFER");
   	}

	decodeBuffer[3000] = 0;
    if(decodeBuffer[0] == 0x1B)
    {
        decodeBuffer[0] = ' ';
        string data(reinterpret_cast<char const*>(decodeBuffer));
        data = trimWS(data);
    	Log(lInfo) << "A Datamatrix barcode was encoded: "<<data;
        Log(lInfo) << decodeBuffer;
        BarcodeLbl->Caption = vclstr(data);
        ClearBarcodeBtn->Visible = true;
        DecodeSessionBtn->Caption = "Scan Barcode";

        //Stop session
        sleep(50);
		mZebra.scanDisable();
    }
    else
    {
    	Log(lError) << "Bad barcode reader memory buffer";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onSSIEvent(TMessage& Msg)
{
	WPARAM w = Msg.WParam;
    LPARAM l = Msg.LParam;
    Log(lInfo) << "There was an onSSIEvent event..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onSSITimeout(TMessage& Msg)
{
	WPARAM w = Msg.WParam;
    LPARAM l = Msg.LParam;
    Log(lInfo) << "There was an onSSITimeout event..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onSSIError(TMessage& Msg)
{
	WPARAM w = Msg.WParam;
    LPARAM l = Msg.LParam;
    Log(lInfo) << "There was an onSSIError event.."<<w<<" : "<<l;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::onSSICapabilities(TMessage& Msg)
{
	WPARAM w = Msg.WParam;
    LPARAM l = Msg.LParam;
    Log(lInfo) << "There was an onSSICapabilities event..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::scannerSettingsClick(TObject *Sender)
{
	//Check which one was clicked
    TRadioGroup* rg = dynamic_cast<TRadioGroup*>(Sender);

    int status;
    if(rg == mScannerAimRG)
    {
    	status  = (rg->ItemIndex == 0 ) ? mZebra.aimOn() : mZebra.aimOff();
    }
    else if(rg == mScannerEnabledRG)
    {
    	status  = (rg->ItemIndex == 0 ) ? mZebra.scanEnable() : mZebra.scanDisable();
    }

    Log(lInfo) << "Status: "<<status;
}
