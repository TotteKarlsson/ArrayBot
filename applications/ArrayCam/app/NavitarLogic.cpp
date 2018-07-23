#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;

//---------------------------------------------------------------------------
void  TMainForm::onNavitarConnected()
{
	NavitarControllerConnectBtn->Caption         = "Disconnect";
    ProdIdLbl->Caption 	        = vclstr(mNavitarMotorController.getProductID());
	HWVerLbl->Caption           = vclstr(mNavitarMotorController.getHardwareVersion());
   	SWVerLbl->Caption           = vclstr(mNavitarMotorController.getSoftwareVersion());
    FirmWareDateLbl->Caption   	= vclstr(mNavitarMotorController.getDriverSoftwareBuildDate());

    TNavitarMotorFrame1->populate(mNavitarMotorController.getFocus());
    TNavitarMotorFrame2->populate(mNavitarMotorController.getZoom());
    enableDisableGroupBox(ControllerInfoGB, true);
}

//---------------------------------------------------------------------------
void  TMainForm::onNavitarDisconnected()
{
	NavitarControllerConnectBtn->Caption = "Connect";
    ProdIdLbl->Caption 	        = "N/A";
	HWVerLbl->Caption           = "N/A";
   	SWVerLbl->Caption           = "N/A";
    FirmWareDateLbl->Caption   	= "N/A";

    enableDisableGroupBox(ControllerInfoGB, false);

    TNavitarMotorFrame1->dePopulate();
    TNavitarMotorFrame2->dePopulate();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NavitarControllerConnectBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == NavitarControllerConnectBtn)
    {
        if(!mNavitarMotorController.isConnected())
        {
            if(mNavitarMotorController.connect())
            {
            	onNavitarConnected();
            }
        }
        else
        {
            if(mNavitarMotorController.disConnect())
            {
            	onNavitarDisconnected();
            }
        }
    }
}

void __fastcall	TMainForm::setFocus(int f)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set focus. Navitar controller is not connected";
    }

    mNavitarMotorController.setFocus(f);
}

void __fastcall	TMainForm::focusIn(int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set focus. Navitar controller is not connected";
    }
    mNavitarMotorController.focusIn(z);
}

void __fastcall	TMainForm::focusOut(int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set focus. Navitar controller is not connected";
    }
    mNavitarMotorController.focusOut(z);
}

void __fastcall	TMainForm::setZoom(int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set zoom. Navitar controller is not connected";
    }
    mNavitarMotorController.setZoom(z);
}

void __fastcall	TMainForm::zoomIn(int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set zoom. Navitar controller is not connected";
    }
    mNavitarMotorController.zoomIn(z);
}

void __fastcall	TMainForm::zoomOut(int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set zoom. Navitar controller is not connected";
    }
    mNavitarMotorController.zoomOut(z);
}

void __fastcall	TMainForm::setFocusAndZoom(int f, int z)
{
	if(!mNavitarMotorController.isConnected())
    {
    	Log(lError) <<"Can't set focus. Navitar controller is not connected";
        return;
    }

    mNavitarMotorController.setFocusAndZoom(f, z);
    mACServer.broadcast(acrFocusAndZoomSet);
}

