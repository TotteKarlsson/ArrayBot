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

__fastcall TPufferArduinoBoardFrame::TPufferArduinoBoardFrame(PufferArduino& dev, IniFile& ini, TComponent* Owner)
	: TArduinoBoardFrame(dev, ini, Owner)
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

void TPufferArduinoBoardFrame::init()
{
    stringstream msg;
    msg<<"d"<<mPufferDurationE->getValue()<<'\n';
    msg<<"v"<<mPufferValveSpeedE->getValue()<<'\n';
    mArduinoDevice.send(msg.str());
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
			msg<<"d"<<mPufferDurationE->getValue()<<'\n';
        }

        if(e == mPufferValveSpeedE)
        {
			msg<<"v"<<mPufferValveSpeedE->getValue()<<'\n';
        }

//       	mArduinoDevice.send("[]");
       	mArduinoDevice.send(msg.str());
    }
}




