#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "Forms/TRegisterNewRibbonForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TPGDataModule.h"
#include "ArrayCamUtils.h"
#include "atUtils.h"
using namespace dsl;
using namespace at;
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
                RibbonIDLbl->Caption = rrf->getRibbonID().c_str();
                mUC7.getSectionCounter().reset();
                mUC7.getRibbonOrderCounter().increase(1);
				RibbonOrderCountLabel->update();
                //If the knife move is streaming, turn off and let it register with this ribbon
                if(THDMIStreamerFrame1->getStreamer().isRunning())
                {
					THDMIStreamerFrame1->getStreamer().stopRecording();

                    //Check in misc timer and click start button when ready
                    mAutoStartKnifeCamera = true;
                }
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

void __fastcall TMainForm::mConnectZebraBtnClick(TObject *Sender)
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
    if(b == mBeepBtn)
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
        mACServer.broadcast(acrBarcodeScanSucceded);
    }
    else
    {
    	Log(lError) << "Bad barcode reader memory buffer";
        mACServer.broadcast(acrBarcodeScanFailed);
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::onSSIImage(TMessage& Msg)
{
//	WPARAM w = Msg.WParam;
//    LPARAM l = Msg.LParam;
//    Log(lInfo) << "There was an onSSIImage event..";
//
//	String msg;
//	unsigned char *pData = NULL;   //(unsigned char *) w;
//	DWORD length = (DWORD)l;
//	unsigned char *pImageType = pData;
//	int filetype = IMAGE_TYPE_UNKNOWN;
//	//CMainFrame * pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;  // This is our access to menu related stuff
//
//	if((w & BUFFERSIZE_MASK) == BUFFERSIZE_GOOD)
//	{
//    	msg.Format("Image Complete");	// Main pane of status bar gives status
//		pData = g_pImageData;
//		pImageType = pData;
//	}
//   	else if ((w & BUFFERSIZE_MASK) == BUFFERSIZE_ERROR)
//    {
//    	msg.Format("Image TOO BIG");	// Main pane of status bar gives status
//    }
//   	else
//    {
//    	msg.Format("NO Image BUFFER");	// Main pane of status bar gives status
//    }
//
////	MyMessage = "Received Image";	// Right side tells what message we got from the dll
//	//onSSIxferStatus((WPARAM)l, l);	// Update the transfer status display to show we got all of the expected image data
//
//
//	// Since we are done with the transfer, we'll enable the user to do whatever they want again
//	// ...(as long as it's supported).
//
////	GetDlgItem(IDC_BUTTON_VIDEO)->EnableWindow(1);
////	GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow(1);
////	if(m_bViewFinderSupported)
////		GetDlgItem(IDC_CHECK_VIEWFINDER)->EnableWindow(1);
////	GetDlgItem(IDC_RADIO_BMP)->EnableWindow(1);
////	GetDlgItem(IDC_RADIO_TIFF)->EnableWindow(1);
////	GetDlgItem(IDC_RADIO_JPEG)->EnableWindow(1);
////	GetDlgItem(IDC_CHECK_SWTRIGGER)->EnableWindow(1);
//
//
//	// If the input data begins with "BM" it's a bitmap
//	// Else if it starts with "MM" or "II" its a tiff - note that we expect big endian from the scanner, and ignore
//	// ...the II for indication for byte ordering.
//
//	if(pImageType != NULL)
//   	{
//   		if((*pImageType == 'B') && (*(pImageType +1) == 'M'))
//	   	{
//        	filetype = BITMAP_TYPE;
//		   	SetupBMPforDisplay( pData,  l);			 // Process input and next Paint message will display our data
//		   	pFrame->m_ImgFileExtension = "bmp";  // Let user choose file save from menu, and set file filter to bmp extension.
//	   	}
//	   	else if (((*pImageType == 'M') && (*(pImageType +1) == 'M')) || ((*pImageType == 'I') && (*(pImageType +1) == 'I')))
//	   	{
//        	SetupTIFFforDisplay( pData,  l);			// Process input and next Paint message will display our data
//		   	filetype = TIFF_TYPE;
//		   	pFrame->m_ImgFileExtension = "tif"; // Let user choose file save from menu, and set file filter to tif extension.
//	   	}
//	   	else if((*pImageType == 0xff) && (*(pImageType +1) == 0xd8))
//	   	{
//        	filetype = JPEG_TYPE;
//			SetupJPEGforDisplay(pData,l, FALSE); // False indicates this is not video
//		   							// Process input and next Paint message will display our data
//
//		   	pFrame->m_ImgFileExtension = "jpg";	// Let user choose file save from menu, and set file filter to jpg extension.
//	   	}
//	   	else
//	   	{
//        	MessageBox("Unknown image format received");
////		   	pFrame->m_ImgFileExtension = "";		// This will indicate  file save from menu needs to be disabled.
//	   	}
//
//	   	m_ImgFileExt = 	pFrame->m_ImgFileExtension;	// Our copy, so we stay in sync with the menu.
//
//	   	if(filetype != IMAGE_TYPE_UNKNOWN)
//        {
//		   WriteImgfile((LPTSTR)pData, length, filetype);	// We always write a temp file since we can't hang on to the
//															// ...dll's data to do it later.
//        }
//   }
//	m_WaitingForSnapShot = FALSE;
}

