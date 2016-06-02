#include <vcl.h>
#pragma hdrstop
#include "unit1.h"
#include "TMemoLogger.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  TMemoLogger::mMemoIsEnabled = true;
}

//---------------------------------------------------------------------------
void TForm1::ShowDeviceInfo(void)
{
    // use joyGetDevCaps to display information from JOYCAPS structure
    // note that not all of the information from joyGetDevCaps is shown
    // here. consult the win32 SDK help file for a full description of
    // joyGetDevCaps
    joyGetDevCaps(JoystickID,&JoyCaps, sizeof(JOYCAPS));
    JoystickCount->Caption 		= "Number of joysticks supported by driver = " + IntToStr(DriverCount);
    JoysticksConnected->Caption = (Connected) ? "Joystick connected" : "Joystick not plugged in";
    CurrentJoystick->Caption 	= "Current Joystick ID = " +  IntToStr(JoystickID);
    JoystickMid->Caption 		= "Manufacturer ID = " + IntToStr(JoyCaps.wMid);
    JoystickPid->Caption        = "Product ID = " + IntToStr(JoyCaps.wPid);
    JoystickName->Caption       = "Name = " + AnsiString(JoyCaps.szPname);
    JoystickXMin->Caption       = "Xmin = " + IntToStr((int)JoyCaps.wXmin);
    JoystickXMax->Caption       = "Xmax = " + IntToStr((int)JoyCaps.wXmax);
    JoystickYMin->Caption       = "Ymin = " + IntToStr((int)JoyCaps.wYmin);
    JoystickYMax->Caption       = "Ymax = " + IntToStr((int)JoyCaps.wYmax);
    JoystickNumButtons->Caption = "Number of buttons = " + IntToStr((int)JoyCaps.wNumButtons);
    JoystickMinPoll->Caption 	= "Min polling period (ms)= " + IntToStr((int)JoyCaps.wPeriodMin);
    JoystickMaxPoll->Caption 	= "Max polling period (ms)= " + IntToStr((int)JoyCaps.wPeriodMax);

    // Tell Windows we want to receive joystick events.
    // Handle = receiver, JoystickID = joystick we're using
    // 3rd arg = how often MM_JOYMOVE events happen
	if(Connected)
  	{
    	joySetCapture(Handle,JoystickID, 20*JoyCaps.wPeriodMin,FALSE);
  	}

    // calculate ratios to divide down the joystick value to a
    // screen value
    XDivider = (JoyCaps.wXmax - JoyCaps.wXmin)/ TargetPanel->Width;
    YDivider = (JoyCaps.wYmax - JoyCaps.wYmin)/ TargetPanel->Height;
}


void __fastcall TForm1::JMMove(TMessage &msg)
{
    // find where the gunsight used to be and fill in that
    // region with the background color of the form.
    Canvas->Brush->Color = Color;

    // calculate screen points from joystick points. First half of equation does
    // the converson. The subtraction centers the gunsights on the
    // joystick location.
    int ScreenX = (Position.x-JoyCaps.wXmin)/XDivider - ImageList1->Width/2  +    TargetPanel->Left;
    int ScreenY = (Position.y-JoyCaps.wYmin)/YDivider - ImageList1->Height/2 +     TargetPanel->Top;

    Canvas->FillRect(Rect(ScreenX,ScreenY, ImageList1->Width+ScreenX,  ImageList1->Height+ScreenY));

    // save new position values. joystick coordinates are passed to us
    // in the high and low words of LPARAM. values are 16 bit ints.
    Position.x = msg.LParamLo;
    Position.y = msg.LParamHi;

    // calculate new screen coordinates
    ScreenX = (Position.x-JoyCaps.wXmin)/XDivider - ImageList1->Width/2 +    TargetPanel->Left;
    ScreenY = (Position.y-JoyCaps.wYmin)/YDivider - ImageList1->Height/2+     TargetPanel->Top;

    JoystickXPosition->Caption = "X Position = " + IntToStr((int)Position.x);
    JoystickYPosition->Caption = "Y Position = " + IntToStr((int)Position.y);
    ImageList1->Draw(Canvas, ScreenX,ScreenY, 0);

//    mXPos.push_back(Position.x);
//    MLog() << "Test: "<<Position.X;
//    int sx = mXPos.size();
//    if(sx >= 100)
//    {
//    	mXPos.pop_front();
//
//    }

//    mZPos.push_back(pos);
//    int sz = mZPos.size();
//    if(sz >= 100)
//    {
//    	mZPos.pop_front();
//    }

}

void __fastcall TForm1::JMZMove(TMessage &msg)
{
	double pos = msg.LParamLo;// * 305e-6 - 10.0;
    JoystickZPosition->Caption = "Z Position = " + IntToStr(msg.LParamLo);
//
//    mZPos.push_back(pos);
//    int sz = mZPos.size();
//    if(sz >= 100)
//    {
//    	mZPos.pop_front();
//    }
}

void __fastcall TForm1::JMButtonUpdate(TMessage &msg)
{
    // Windows us both sends both JM_BUTTONDOWN an
    // JM_BUTTONUP messages. Both trigger this function
    // This event only happens when a button changes state/
    // you can find out which button was toggled by anding
    // with JOY_BUTTONXCHG where X is the button number

    JoystickButton1->Caption = (msg.WParam & JOY_BUTTON1) ?
    "Button 1 = Pressed" : "Button 1 = Not Pressed";

    JoystickButton2->Caption = (msg.WParam & JOY_BUTTON2) ?
    "Button 2 = Pressed" : "Button 2 = Not Pressed";

    JoystickButton3->Caption = (msg.WParam & JOY_BUTTON3) ?
    "Button 3 = Pressed" : "Button 3 = Not Pressed";

    JoystickButton4->Caption = (msg.WParam & JOY_BUTTON4) ?
    "Button 4 = Pressed" : "Button 4 = Not Pressed";

    JoystickButton5->Caption = (msg.WParam & JOY_BUTTON5) ?
    "Button 5 = Pressed" : "Button 5 = Not Pressed";

}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if(Connected)
    {
  		joyReleaseCapture(JoystickID);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
//	for (int j=0; j< ControlCount;j++)
//    {
//  		Controls[j]->Refresh();
//    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Connected = false;
    MMRESULT  JoyResult;
    JOYINFOEX JoyInfo;

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
    JoyResult = joyGetPosEx(JOYSTICKID1, &JoyInfo);
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
    else if((JoyResult=joyGetPosEx(JOYSTICKID2, &JoyInfo)) == JOYERR_NOERROR)
    {
      // if joystick1 is unconnected, check for joystick2
      Connected = true;
      JoystickID = JOYSTICKID2;
    }

  ShowDeviceInfo(); // initialize the labels.
  ShowStatusInfo();
}


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
//	//Plot Z positions
//    Series1->Clear();
//    Series2->Clear();
//    for(int i = 0; i < mXPos.size(); i++)
//    {
//	    //Series1->AddXY(i, mZPos[i]);
//	    Series2->AddXY(i, mXPos[i]);
////	    Series3->AddXY(i, mYPos[i]);
//    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


void TForm1::ShowStatusInfo(void)
{
    if(!Connected)
    {
        JoystickXPosition->Visible = false;
        JoystickYPosition->Visible = false;
        JoystickButton1->Visible   = false;
        JoystickButton2->Visible   = false;
        JoystickButton3->Visible   = false;
        JoystickButton4->Visible   = false;
        JoystickButton5->Visible   = false;
        return;
    }

    JOYINFOEX JoyInfo;

	JoyInfo.dwSize = sizeof(JOYINFOEX);
	JoyInfo.dwFlags = JOY_RETURNALL;
    joyGetPosEx(JoystickID, &JoyInfo); // get the initial joystick pos

    Position.x = JoyInfo.dwXpos;     // save values
    Position.y = JoyInfo.dwYpos;     // and update each caption

    JoystickXPosition->Caption = "X Position = " + IntToStr((int)Position.x);
    JoystickYPosition->Caption = "Y Position = " + IntToStr((int)Position.y);

  	// The bits of wButtons tell which buttons have been pressed. bitwise
  	// and with JOY_BUTTONX to determine if a button X is pressed. buttons
  	// that are not connected are reported as not pressed.
    JoystickButton1->Caption = (JoyInfo.dwButtons & JOY_BUTTON1) ?
    "Button 1 = Pressed" : "Button 1 = Not Pressed";

    JoystickButton2->Caption = (JoyInfo.dwButtons & JOY_BUTTON2) ?
    "Button 2 = Pressed" : "Button 2 = Not Pressed";

    JoystickButton3->Caption = (JoyInfo.dwButtons & JOY_BUTTON3) ?
    "Button 3 = Pressed" : "Button 3 = Not Pressed";

    JoystickButton4->Caption = (JoyInfo.dwButtons & JOY_BUTTON4) ?
    "Button 4 = Pressed" : "Button 4 = Not Pressed";

    JoystickButton5->Caption = (JoyInfo.dwButtons & JOY_BUTTON5) ?
    "Button 5 = Pressed" : "Button 5 = Not Pressed";
}

