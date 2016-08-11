#include <vcl.h>
#pragma hdrstop
#include "TArduinoBoardFrame.h"
#include "mtkBaseProperty.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TArduinoBoardFrame *ArduinoBoardFrame;
//---------------------------------------------------------------------------

using namespace mtk;
__fastcall TArduinoBoardFrame::TArduinoBoardFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TFrame(Owner),
    mArduinoDevice(dev)
{
    mProperties.setSection(dev.getName());
	mProperties.setIniFile(&ini);

	mProperties.add((BaseProperty*)  &mCommPortE->getProperty()->setup(       	"COMM_PORT",    	 0));
	mProperties.add((BaseProperty*)  &mBaudRateE->getProperty()->setup(       	"BAUD_RATE",    	 9600));
    mProperties.read();

    mCommPortE->update();
	mBaudRateE->update();
    GroupBox1->Caption = dev.getName().c_str();

    mArduinoDevice.assignInitFunction(init);
}

__fastcall  TArduinoBoardFrame::~TArduinoBoardFrame()
{
	mProperties.write();
}

void TArduinoBoardFrame::init()
{
	Log(lWarning) << "Implement in decendant";
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::ConnectBtnClick(TObject *Sender)
{
	if(mConnectBtn->Caption == "Disconnect")
    {
    	mArduinoDevice.disConnect();
    }
    else
    {
    	mArduinoDevice.connect(mCommPortE->getValue(), mBaudRateE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::Button1Click(TObject *Sender)
{
	mArduinoDevice.send(mSendMSGE->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::mSendMSGEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn)
    {
  		mArduinoDevice.send(mSendMSGE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TArduinoBoardFrame::Timer1Timer(TObject *Sender)
{
    mConnectBtn->Caption 	=  mArduinoDevice.isConnected()  ? "Disconnect" : "Connect";
    mCommPortE->Enabled 	= !mArduinoDevice.isConnected();
    mBaudRateE->Enabled 	= !mArduinoDevice.isConnected();
    mSendMSGE->Enabled 		=  mArduinoDevice.isConnected();
}

