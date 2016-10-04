#include <vcl.h>
#pragma hdrstop
#include "TSensorsArduinoFrame.h"
#include <sstream>
#include "mtkBaseProperty.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSensorsArduinoFrame *SensorsArduinoFrame;
//---------------------------------------------------------------------------

using std::stringstream;
using namespace mtk;

__fastcall TSensorsArduinoFrame::TSensorsArduinoFrame(ArduinoServer& server, ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(server, dev, ini, Owner)
{
	mProperties.add((BaseProperty*)  &mSendMSGE->getProperty()->setup(    	       "SEND_TEXT", 	 		 "i"));
    mProperties.read();
	mSendMSGE->update();
}

__fastcall TSensorsArduinoFrame::~TSensorsArduinoFrame()
{
	mProperties.write();
}

void TSensorsArduinoFrame::init()
{
    stringstream msg;
    mArduinoDevice.send(msg.str());
}

//---------------------------------------------------------------------------
void __fastcall TSensorsArduinoFrame::mSendMSGEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
    if(Key == vkReturn)
    {
		string msg = mSendMSGE->getValue();
        stringstream customMsg;
 		customMsg << "SENSORS_CUSTOM_MESSAGE="<<msg;
	    mServer.request(customMsg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TSensorsArduinoFrame::mSendBtnClick(TObject *Sender)
{
    string msg = mSendMSGE->getValue();
    stringstream customMsg;
    customMsg << "SENSORS_CUSTOM_MESSAGE="<<msg;
    mServer.request(customMsg.str());
}


