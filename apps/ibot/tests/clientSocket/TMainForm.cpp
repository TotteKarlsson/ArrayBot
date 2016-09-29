#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "TMemoLogger.h"
#include "mtkVCLUtils.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "mtkSTDStringEdit"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TMainForm::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)
{
	MLog() << "Connection was established to server on port: "<<mPortNr->getValue();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	ClientSocket1->Port = mPortNr->getValue();
	ClientSocket1->Open();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)
{
	String msg = Socket->ReceiveText();
    MLog() << "Received :"<<stdstr(msg);
}

void __fastcall TMainForm::ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket)
{
	MLog() << "Connection was dropped.. ";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClientSocket1Connecting(TObject *Sender, TCustomWinSocket *Socket)
{
	MLog() << "Connecting..";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
	MLog() <<"An error occured: "<<ErrorCode;
}

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
	ClientSocket1->Socket->SendText( mSendStr->GetValue().c_str());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClientSocket1Write(TObject *Sender, TCustomWinSocket *Socket)

{
	MLog() <<"Writing..";

}

