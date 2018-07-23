#include <vcl.h>
#pragma hdrstop
#include "TZebraScannerFrame.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

#pragma package(smart_init)
#pragma resource "*.dfm"
TZebraScannerFrame *ZebraScannerFrame;
//---------------------------------------------------------------------------
__fastcall TZebraScannerFrame::TZebraScannerFrame(TComponent* Owner)
	: TFrame(Owner),
    mZebraCOMPort(17),
    mZebraBaudRate(9600),
    mZebra()
{
}

//---------------------------------------------------------------------------
int	TZebraScannerFrame::getZebraCOMPortNumber()
{
	return mComportCB->ItemIndex + 1;
}

void __fastcall TZebraScannerFrame::onConnectedToZebra()
{
    mConnectZebraBtn->Caption = "Close";
//    enableDisableGroupBox(mImagerSettingsGB, true);
    //Turn into a 'known' state
//	mZebra.beep(ONESHORTLO);
}

//---------------------------------------------------------------------------
void __fastcall TZebraScannerFrame::onDisConnectedToZebra()
{
    mConnectZebraBtn->Caption = "Open";
//    enableDisableGroupBox(mImagerSettingsGB, false);
}

//---------------------------------------------------------------------------
void __fastcall TZebraScannerFrame::BtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);
    int status(-1);
    if(b == mBeepBtn)
    {
		int status = mZebra.beep(ONESHORTLO);
    }
    else if(b == mDecodeSessionBtn)
    {
    	if(b->Caption == "Start")
        {
        	//Start session
			status = mZebra.startDecodeSession();
			b->Caption = "Stop";
        }
        else
        {
        	//Stop session
			status = mZebra.stopDecodeSession();
            b->Caption = "Start";
            Sleep(100);
            mZebra.illuminationOff();
        }
    }

    Log(lInfo) << "Command return status: "<<status;
}

//---------------------------------------------------------------------------
void __fastcall TZebraScannerFrame::SettingsRGClick(TObject *Sender)
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
    else if(rg == mScannerIllumRG)
    {
    	status  = (rg->ItemIndex == 0 ) ? mZebra.illuminationOn() : mZebra.illuminationOff();
    }

    Log(lInfo) << "Status: "<<status;
}

//---------------------------------------------------------------------------
void __fastcall TZebraScannerFrame::mConnectZebraBtnClick(TObject *Sender)
{
	int Comport = getZebraCOMPortNumber();
   	if(mConnectZebraBtn->Caption == "Open")
    {
        if(mZebra.connect(Comport, mZebraBaudRate) != true)
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

