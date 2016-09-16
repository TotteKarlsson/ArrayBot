#include <vcl.h>
#pragma hdrstop
#include "TPufferArduinoBoardFrame.h"
#include "mtkBaseProperty.h"
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TPufferArduinoBoardFrame *PufferArduinoBoardFrame;
//---------------------------------------------------------------------------

using namespace mtk;

__fastcall TPufferArduinoBoardFrame::TPufferArduinoBoardFrame(ArduinoServer& server, PufferArduino& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(server, dev, ini, Owner),
    mPufferArduino(dev)
{
	mProperties.add((BaseProperty*)  &mPufferDurationE->getProperty()->setup(  	   "PUFFER_DURATION",    	 50));
	mProperties.add((BaseProperty*)  &mPufferValveSpeedE->getProperty()->setup(    "PUFFER_VALVE_SPEED", 	 255));
	mProperties.add((BaseProperty*)  &mSendMSGE->getProperty()->setup(    	       "SEND_TEXT", 	 		 "i"));
    mProperties.read();

	mPufferDurationE->update();
	mPufferValveSpeedE->update();
	mSendMSGE->update();
}

__fastcall TPufferArduinoBoardFrame::~TPufferArduinoBoardFrame()
{
	mProperties.write();
}

//When the server receives that the arduino was just connected, the following
//init function is called.
void TPufferArduinoBoardFrame::init()
{
//    stringstream msg;
//    msg<<"d"<<mPufferDurationE->getValue()<<'\n';
//    msg<<"v"<<mPufferValveSpeedE->getValue()<<'\n';
//    mServer.request("SET_PUFFER_DURATION=)
//    mPufferArduino.send(msg.str());
}

//---------------------------------------------------------------------------
void __fastcall TPufferArduinoBoardFrame::updateParameter(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
       	stringstream msg;
    	TIntegerLabeledEdit* e = dynamic_cast<TIntegerLabeledEdit*>(Sender);
        if(e == mPufferDurationE)
        {
			msg<<"SET_PUFFER_DURATION="<<mPufferDurationE->getValue()<<'\n';
        }

        if(e == mPufferValveSpeedE)
        {
			msg<<"SET_PUFFER_VALVE_SPEED="<<mPufferValveSpeedE->getValue()<<'\n';
        }

       	mServer.request(msg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TPufferArduinoBoardFrame::mSendMSGEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == vkReturn)
    {
		string msg = mSendMSGE->getValue();
        stringstream customMsg;
 		customMsg << "PUFFER_CUSTOM_MESSAGE="<<msg;
	    mServer.request(customMsg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TPufferArduinoBoardFrame::mSendBtnClick(TObject *Sender)
{
    string msg = mSendMSGE->getValue();
    stringstream customMsg;
    customMsg << "PUFFER_CUSTOM_MESSAGE="<<msg;
    mServer.request(customMsg.str());
}


