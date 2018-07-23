#include <vcl.h>
#pragma hdrstop
#include "TLightsArduinoFrame.h"
#include <sstream>
#include "dslBaseProperty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TLightsArduinoFrame *LightsArduinoFrame;
//---------------------------------------------------------------------------

using std::stringstream;
using namespace dsl;

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
    msg << "i";
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


