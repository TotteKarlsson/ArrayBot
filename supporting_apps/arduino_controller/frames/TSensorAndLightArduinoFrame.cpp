#include <vcl.h>
#pragma hdrstop
#include "TSensorAndLightArduinoFrame.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArduinoBoardFrame"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSensorAndLightArduinoFrame *SensorAndLightArduinoFrame;
//---------------------------------------------------------------------------

using std::stringstream;

__fastcall TSensorAndLightArduinoFrame::TSensorAndLightArduinoFrame(ArduinoDevice& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(dev, ini, Owner)
{
//	mProperties.add((BaseProperty*)  &mPufferDurationE->getProperty()->setup(  	   "PUFFER_DURATION",    	 50));
//	mProperties.add((BaseProperty*)  &mPufferValveSpeedE->getProperty()->setup(    "PUFFER_VALVE_SPEED", 	 255));
//	mProperties.add((BaseProperty*)  &mSendMSGE->getProperty()->setup(    	       "SEND_TEXT", 	 		 "i"));
    mProperties.read();

//	mPufferDurationE->update();
//	mPufferValveSpeedE->update();
	mSendMSGE->update();
}

__fastcall TSensorAndLightArduinoFrame::~TSensorAndLightArduinoFrame()
{
	mProperties.write();
}

void TSensorAndLightArduinoFrame::init()
{
    stringstream msg;
    mAD.send(msg.str());
}

