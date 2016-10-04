#include <vcl.h>
#pragma hdrstop
#include "TLightsArduinoFrame.h"
#include <sstream>
#include "mtkBaseProperty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TLightsArduinoFrame *LightsArduinoFrame;
//---------------------------------------------------------------------------

using std::stringstream;
using namespace mtk;

__fastcall TLightsArduinoFrame::TLightsArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(server, dev, ini, Owner)
{
	mProperties.add((BaseProperty*)  &mSendMSGE->getProperty()->setup(    	       "SEND_TEXT", 	 		 "i"));
    mProperties.read();
	mSendMSGE->update();
}

__fastcall TLightsArduinoFrame::~TLightsArduinoFrame()
{
	mProperties.write();
}

void TLightsArduinoFrame::init()
{
    stringstream msg;
    mArduinoDevice.send(msg.str());
}

//---------------------------------------------------------------------------
void __fastcall TLightsArduinoFrame::mSendMSGEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
    if(Key == vkReturn)
    {
		string msg = mSendMSGE->getValue();
        stringstream customMsg;
 		customMsg << "LIGHTS_CUSTOM_MESSAGE="<<msg;
	    mServer.request(customMsg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TLightsArduinoFrame::mSendBtnClick(TObject *Sender)
{
    string msg = mSendMSGE->getValue();
    stringstream customMsg;
    customMsg << "LIGHTS_CUSTOM_MESSAGE="<<msg;
    mServer.request(customMsg.str());
}


