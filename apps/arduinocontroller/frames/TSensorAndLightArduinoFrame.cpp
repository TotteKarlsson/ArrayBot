#include <vcl.h>
#pragma hdrstop
#include "TSensorAndLightArduinoFrame.h"
#include <sstream>
#include "mtkBaseProperty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSensorAndLightArduinoFrame *SensorAndLightArduinoFrame;
//---------------------------------------------------------------------------

using std::stringstream;
using namespace mtk;

__fastcall TSensorAndLightArduinoFrame::TSensorAndLightArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(server, dev, ini, Owner)
{
	mProperties.add((BaseProperty*)  &mSendMSGE->getProperty()->setup(    	       "SEND_TEXT", 	 		 "i"));
    mProperties.read();
	mSendMSGE->update();
}

__fastcall TSensorAndLightArduinoFrame::~TSensorAndLightArduinoFrame()
{
	mProperties.write();
}

void TSensorAndLightArduinoFrame::init()
{
    stringstream msg;
    mArduinoDevice.send(msg.str());
}

//---------------------------------------------------------------------------
void __fastcall TSensorAndLightArduinoFrame::mSendMSGEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
    if(Key == vkReturn)
    {
		string msg = mSendMSGE->getValue();
        stringstream customMsg;
 		customMsg << "SENSOR_CUSTOM_MESSAGE="<<msg;
	    mServer.request(customMsg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TSensorAndLightArduinoFrame::mSendBtnClick(TObject *Sender)
{
    string msg = mSendMSGE->getValue();
    stringstream customMsg;
    customMsg << "SENSOR_CUSTOM_MESSAGE="<<msg;
    mServer.request(customMsg.str());
}


