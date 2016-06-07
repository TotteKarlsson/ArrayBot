#include <vcl.h>
#pragma hdrstop
#include "unit1.h"
//---------------------------------------------------------------------------
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  :
  TForm(Owner),
  mRunningZAverage(0),
  mValCommand(0)
  {}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	//Check if joystick value have changed more than previous command
    if(!mZAvgPos.size())
    {
    	return;
    }
	double val = mZAvgPos[mZAvgPos.size() -1];
    if(fabs(val - mValCommand) > 1.0)
    {
	    Memo1->Lines->Add("New value ");
	    Memo1->Lines->Add(FloatToStrF(val, ffFixed, 4,2));
	    Memo1->Lines->Add("Old value ");
	    Memo1->Lines->Add(FloatToStrF(mValCommand, ffFixed, 4,2));
        mValCommand = val;
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Connected = false;
    MMRESULT  JoyResult;
    JOYINFO JoyInfo;

    // the joystick could be disconnected even if the driver is
    // loaded. use joyGetPos to detect if a joystick is connected
    // it returns JOYERR_NOERROR if the joystick is plugged in
	// find out how many joysticks the driver supports
  	DriverCount = joyGetNumDevs();

  	if(DriverCount == 0)    // can any joysticks be supported
  	{
		return;
  	}
    // test for joystick1
    JoyResult = joyGetPos(JOYSTICKID1,&JoyInfo);
    if(JoyResult != JOYERR_UNPLUGGED)
    {
      Connected = true;
      JoystickID = JOYSTICKID1;
    }
    else if(JoyResult == MMSYSERR_INVALPARAM)
    {
    	// INVALIDPARAM means something is bad. quit now without
	    // checking for joystick 2
      	Application->MessageBox(L"An error occured while calling joyGetPosEx", L"Error", MB_OK);
    }
    else if((JoyResult=joyGetPos(JOYSTICKID2,&JoyInfo)) == JOYERR_NOERROR)
    {
      // if joystick1 is unconnected, check for joystick2
      Connected = true;
      JoystickID = JOYSTICKID2;
    }

  ShowDeviceInfo(); // initialize the labels.
  ShowStatusInfo();
}

  //---------------------------------------------------------------------------
void TForm1::ShowDeviceInfo(void)
{
    // use joyGetDevCaps to display information from JOYCAPS structure
    // note that not all of the information from joyGetDevCaps is shown
    // here. consult the win32 SDK help file for a full description of
    // joyGetDevCaps
    joyGetDevCaps(JoystickID,&JoyCaps, sizeof(JOYCAPS));

    // Tell Windows we want to receive joystick events.
    // Handle = receiver, JoystickID = joystick we're using
    // 3rd arg = how often MM_JOYMOVE events happen
	if(Connected)
  	{
    	joySetCapture(Handle,JoystickID, 2*JoyCaps.wPeriodMin,FALSE);
  	}
}

void TForm1::ShowStatusInfo(void)
{
    if(!Connected)
    {
        return;
    }

    JOYINFO JoyInfo;
    joyGetPos(JoystickID,&JoyInfo); // get the initial joystick pos
}

void __fastcall TForm1::JMZMove(TMessage &msg)
{
	//Make Z being between 0 - 20.
	double pos = msg.LParamLo * 305e-6;
    mRunningZAverage 			= (mAlpha->getValue() * pos) + (1.0 - mAlpha->getValue()) * mRunningZAverage;
    JoystickZPosition->Caption 	= "Z Position = " + FloatToStrF(pos, ffFixed, 4,2);
    JoystickAvgZPos->Caption 	= "AVG Z Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);

    mZPos.push_back(pos);
    mZAvgPos.push_back(mRunningZAverage);

    int sz = mZPos.size();
    if(sz >= 100)
    {
    	mZPos.pop_front();
		mZAvgPos.pop_front();
    }
}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if(Connected)
    {
  		joyReleaseCapture(JoystickID);
    }
}


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	//Plot Z positions
    Series1->Clear();
    Series2->Clear();
    for(int i = 0; i < mZPos.size(); i++)
    {
	    Series1->AddXY(i, mZPos[i]);
    }

    for(int i = 0; i < mZAvgPos.size(); i++)
    {
	    Series2->AddXY(i, mZAvgPos[i]);
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


