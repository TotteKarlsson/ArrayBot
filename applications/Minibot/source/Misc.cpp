#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslStringUtils.h"
#include "arraybot/apt/atAPTMotor.h"
#include "forms/TSplashForm.h"
#include "forms/TTextInputDialog.h"
#include "TXYZUnitFrame.h"

using namespace dsl;
static HWND gOtherAppWindow = NULL;
extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
void __fastcall TMainForm::checkForDevicesExecute(TObject *Sender)
{
	if(!buildDeviceList())
    {
    	Log(lError) <<"Failed building device list";
        return;
    }

    stringstream info;
    for(int i = 0; i < 90; i++)
    {
		StringList serials = getSerialsForDeviceType((DeviceTypeID) i);
        for(u_int j = 0; j < serials.count(); j++)
        {
            APTMotor* m = mAB.getMotorWithSerial(serials[j]);
            if(m)
            {
            	info << "Device ("<<m->getName()<<") of type '"<<::toString((DeviceTypeID) i)<<"' with serial " <<serials[j];

                if(m->isHomed())
                {
                    info <<" is homed";
                }
                else
                {
            		info << " is NOT HOMED.";
                }

                if(m->isEnabled())
                {
                	info <<" and is enabled.";
                }
                else
                {
                	info <<" and is NOT ENABLED.";
                }
            }
            else
            {
               	info << "Motor with serial: "<<serials[j]<<" is not part of the ArrayBot system";
            }
            info << endl;
        }
    }

	TTextInputDialog* t = new TTextInputDialog(NULL);
    t->Width = 1024;
    t->Caption = "Device Information";
    t->mInfoMemo->ReadOnly = true;
	t->mCancelBtn->Visible = false;
    t->setText(info.str());
    t->ShowModal();
    delete t;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LogLevelCBChange(TObject *Sender)
{
    if(LogLevelCB->ItemIndex == 0)
    {
        mLogLevel = lInfo;
    }
    else if(LogLevelCB->ItemIndex == 1)
    {
        mLogLevel = lAny;
    }

    gLogger.setLogLevel(mLogLevel);
}

void TMainForm::enableDisableUI(bool enable)
{
	this->Visible = enable;
}

void __fastcall	TMainForm::OnException()
{
	Log(lInfo) << "Exception TMainForm::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception: "<<stdstr(E->Message);
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
	if(infoMemo->Lines->Count > 500)
    {
		infoMemo->Clear();
    }

    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
}

void TMainForm::setupWindowTitle()
{
	string title = createWindowTitle("MiniBot", Application);
	this->Caption = vclstr(title);
}

int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	int length = ::GetWindowTextLength(hwnd);
	if(!length)
    {
	    return TRUE;
    }

	TCHAR* buffer = new TCHAR[length + 1];
	GetWindowText(hwnd, &buffer[0], length + 1);
    string s(stdstr(buffer));
	if(startsWith("MiniBot", s))
	{
		gOtherAppWindow = hwnd;
        SetFocus(hwnd);
		return false;
	}
	return true;
}
