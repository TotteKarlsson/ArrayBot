#include <vcl.h>
#pragma hdrstop
#include "TArduinoBoardFrame.h"
#include "mtkBaseProperty.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkSTDStringEdit"
#pragma link "TIntegerLabeledEdit"
#pragma resource "*.dfm"
TArduinoBoardFrame *ArduinoBoardFrame;
//---------------------------------------------------------------------------

using namespace mtk;
__fastcall TArduinoBoardFrame::TArduinoBoardFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TFrame(Owner),
    mAD(dev)
{
    mProperties.setSection(dev.getName());
	mProperties.setIniFile(&ini);

	mProperties.add((BaseProperty*)  &mCommPortE->getProperty()->setup(       	"COMM_PORT",    	 0));
	mProperties.add((BaseProperty*)  &mBaudRateE->getProperty()->setup(       	"BAUD_RATE",    	 9600));
    mProperties.read();

    mCommPortE->update();
	mBaudRateE->update();
    GroupBox1->Caption = dev.getName().c_str();
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::mArduinoBoard1ConnectClick(TObject *Sender)
{
	if(mArduinoBoard1Connect->Caption == "Disconnect")
    {
    	mAD.disConnect();
    }
    else
    {
    	mAD.connect(mCommPortE->getValue(), mBaudRateE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::Button1Click(TObject *Sender)
{
	mAD.send(mSendMSGE->GetString());
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::mSendMSGEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn)
    {
  		mAD.send(mSendMSGE->GetString());
    }
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::Timer1Timer(TObject *Sender)
{
    mArduinoBoard1Connect->Caption 	= mAD.isConnected()	? "Disconnect" : "Connect";
    mCommPortE->Enabled = !mAD.isConnected();
    mBaudRateE->Enabled = !mAD.isConnected();
    mSendMSGE->Enabled 	= mAD.isConnected();
}

