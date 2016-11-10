#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "apt/atAPTMotor.h"
#include "TSplashForm.h"
#include "forms/TTextInputDialog.h"
#include "frames/TXYZUnitFrame.h"

using namespace mtk;

static HWND gOtherAppWindow = NULL;

extern TSplashForm*  gSplashForm;
//---------------------------------------------------------------------------
void __fastcall TMain::checkForDevicesExecute(TObject *Sender)
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
            APTMotor* m = mAB->getMotorWithSerial(serials[j]);
            if(m)
            {
            	info << "Device ("<<m->getName()<<") of type '"<<::toString((DeviceTypeID) i)<<"' with serial " <<serials[j]<<" is ";

                if(m->isHomed())
                {
                    info <<"homed";
                }
                else
                {
            		info << "NOT HOMED";
                }
            }
            else
            {
               	info << "not part of ArrayBot system";
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

void __fastcall TMain::FrameClosed(TObject *Sender)
{
	;
}

void TMain::enableDisableUI(bool enable)
{
	this->Visible = enable;
}

void __fastcall	TMain::OnException()
{
	Log(lInfo) << "Exception TMain::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception...."<<stdstr(E->Message);
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject *Sender)
{
	this->Height = this->Height - 1;
	this->Height = this->Height + 1;
}

void __fastcall TMain::BitBtn3Click(TObject *Sender)
{
	infoMemo->Clear();
}

//This one is called from the reader thread
void __fastcall TMain::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

void TMain::setupWindowTitle()
{
	string title = createWindowTitle("ArrayBot", Application);
	this->Caption = vclstr(title);
}

int __stdcall FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	int length = ::GetWindowTextLength(hwnd);
	if(!length)
    {
	    return TRUE;
    }

	vector<TCHAR> buffer(length + 1);
	GetWindowText(hwnd, &buffer[0], length + 1);

    string s(stdstr(buffer));
	if(startsWith("ArrayBot", s))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
        SetFocus(hwnd);

        //Stop enumerating..
		return false;
	}

	return true;
}

