#include <vcl.h>
#pragma hdrstop
#include "TSSHFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ScBridge"
#pragma link "ScSSHChannel"
#pragma link "ScSSHClient"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTStdStringLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSSHFrame *SSHFrame;

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TSSHFrame::TSSHFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ScSSHClientAfterConnect(TObject *Sender)
{
	Log(lInfo) << "Connected..";
    ConnectBtn->Caption = "Disconnect";
    ScSSHShell1->Connect();
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ScSSHClientServerKeyValidate(TObject *Sender, TScKey *NewServerKey,
          bool &Accept)
{
    String fp, msg;
    TScKey *Key = ScFileStorage->Keys->FindKey(ScSSHClient->HostName);
    if ((Key == NULL) || (!Key->Ready))
    {
        NewServerKey->GetFingerprint(haMD5, fp);
        msg = "The authenticity of the server can not be verified.\n";
        msg += "Fingerprint for the key received from server: " + fp + ".\n";
        msg += "Key length: " + IntToStr(NewServerKey->BitCount) + " bits.\n";
        msg += "Are you sure you want to continue connecting?";

        if (MessageDlg(msg, mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
        {
        	Key = new TScKey(NULL);
          	try
          	{
            	Key->Assign(NewServerKey);
            	Key->KeyName = ScSSHClient->HostName;
            	ScFileStorage->Keys->Add(Key);
          	}
          	catch (Exception &exception)
          	{
            	Key->Free();
            	throw;
          	}

          	Accept = true;
        }
	}
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ScSSHClientAfterDisconnect(TObject *Sender)
{
	Log(lInfo) << "Disconnected..";
    ConnectBtn->Caption = "Connect";
    ScSSHShell1->Disconnect();
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ScSSHClientBeforeConnect(TObject *Sender)
{
   	FRandomized = true;
    ScSSHClient->HostName = edSSHHost->Text;
    ScSSHClient->Port = StrToInt(seSSHPort->Text);
    ScSSHClient->User = edSSHUserName->Text;

    ScSSHClient->Authentication = atPassword;
    ScSSHClient->Password = edSSHPassword->Text;
    ScSSHClient->KeyStorage = ScFileStorage;
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ConnectBtnClick(TObject *Sender)
{
    TCursor OldCursor = Screen->Cursor;
    try
    {
    	if(ConnectBtn->Caption == "Connect")
        {
	    	Screen->Cursor = crHourGlass;
    		ScSSHClient->Connect();
        }
        else
        {
	    	Screen->Cursor = crHourGlass;
			ScSSHChannel->Disconnect();
            ScSSHClient->Disconnect();
			ScSSHShell1->Disconnect();
        }
    }
    __finally
    {
    	Screen->Cursor = OldCursor;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSSHFrame::ScSSHShell1AsyncError(TObject *Sender, Exception *E)
{
	Log(lError) << "There was an Error"<<stdstr(E->Message);
}

//---------------------------------------------------------------------------
bool TSSHFrame::isConnected()
{
	return ScSSHChannel->Connected || ScSSHClient->Connected || ScSSHShell1->Connected;
}

//---------------------------------------------------------------------------
void TSSHFrame::disconnect()
{
    if(ScSSHChannel->Connected)
    {
        ScSSHChannel->Disconnect();
    }

    if(ScSSHClient->Connected)
    {
        ScSSHClient->Disconnect();
    }

    if(ScSSHShell1->Connected)
    {
        ScSSHShell1->Disconnect();
    }
}

