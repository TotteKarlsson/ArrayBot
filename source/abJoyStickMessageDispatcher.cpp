#pragma hdrstop
#include "abJoyStickMessageDispatcher.h"
#include <bitset>
#include "mtkLogger.h"
#include "abExceptions.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace mtk;

JoyStickMessageDispatcher::JoyStickMessageDispatcher(int nrOfButtons)
:
mEnabled(false),
mCanEnable(false),
mMoveResolution(100),
mNrOfButtons(nrOfButtons)
{
    mJoyStickID = JOYSTICKID1; //Support only one for now
    mUpdateStateTimer.setInterval(30);
	mUpdateStateTimer.OnTimerC = refresh;

   	mEnabled = readCapabilities();
	mCanEnable = mEnabled;
    //Setup buttons
    for(int i = 0; i < mNrOfButtons; i++)
    {
    	mButtons.push_back(JoyStickButtonStateEventDispatcher());
    }
}

JoyStickMessageDispatcher::~JoyStickMessageDispatcher()
{}

bool JoyStickMessageDispatcher::isEnabled()
{
	return mUpdateStateTimer.isRunning();
}

bool JoyStickMessageDispatcher::enable()
{
    mUpdateStateTimer.start();
    return mCanEnable ?  true : false;
}

void JoyStickMessageDispatcher::disable()
{
	mUpdateStateTimer.stop();
}

bool JoyStickMessageDispatcher::readCapabilities()
{
    if(mJoyStickID == -1)
    {
		Log(lError) << "Invalid JoyStickID.";
    	return false;
    }

    int res = joyGetDevCaps(mJoyStickID, &mCapabilities, sizeof(JOYCAPS));
    if(res != JOYERR_NOERROR)
    {
    	if(res == MMSYSERR_NODRIVER)
        {
			Log(lError) << "There is no valid driver for the joystick.";
        }
        else if(res == MMSYSERR_INVALPARAM)
        {
			Log(lError) << "Invalid joystick parameter.";
        }

		//throw(ABException("Failed getting joystick capablities"));
        Log(lError) <<"Failed getting joystick capablities";
        return false;
    }
	return true;
}

void JoyStickMessageDispatcher::setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down)
{
	mButtons[btnNr  - 1].mEvents = ButtonEvents(up, down);
}

void JoyStickMessageDispatcher::setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down)
{
	switch(btnNr)
    {
		case 1: mPOV.mLeftButtonEvents 	= ButtonEvents(up, down); break;
		case 2: mPOV.mDownButtonEvents 	= ButtonEvents(up, down); break;
		case 3: mPOV.mRightButtonEvents = ButtonEvents(up, down); break;
		case 4: mPOV.mUpButtonEvents 	= ButtonEvents(up, down); break;
    }
}

void JoyStickMessageDispatcher::setAxisEvent(int axis, JoyStickAxisEvent event)
{
    switch(axis)
    {
    	case 1:	mX1Axis.mEvent = event;		break;
        case 2:	mY1Axis.mEvent = event;		break;
    	case 3:	mX2Axis.mEvent = event;		break;
        case 4:	mY2Axis.mEvent = event;		break;
    }
}

//---------------------------------------------------------------------------
void JoyStickMessageDispatcher::refresh()
{
    if (mJoyStickID == -1 || mEnabled == false)
    {
	    return;
    }

    mJoyInfo.dwSize  =  sizeof(JOYINFOEX);
    mJoyInfo.dwFlags = JOY_RETURNALL;
    int res = joyGetPosEx(mJoyStickID, &mJoyInfo);
    if(res != JOYERR_NOERROR)
    {
   	    mJoyStickID = -1;
    	mEnabled = false;
		throw("Failed getting joystick status");
    }

    //Check X1 Axis
//    if(abs((int) (mX1Axis.mPosition - mJoyInfo.dwXpos)) > mMoveResolution)
    {
    	if(mX1Axis.mEvent)
        {
            mX1Axis.mEvent(mJoyInfo.dwXpos);
        }
        mX1Axis.mPosition = mJoyInfo.dwXpos;
    }

    //Check Y1 Axis
//    if(abs((int) (mY1Axis.mPosition - mJoyInfo.dwYpos)) > mMoveResolution)
    {
    	if(mY1Axis.mEvent)
        {
            mY1Axis.mEvent(mJoyInfo.dwYpos);
        }
        mY1Axis.mPosition = mJoyInfo.dwYpos;
    }

    //Check X2 Axis  (Z - axis in API struc)
//    if(abs((int) (mX2Axis.mPosition - mJoyInfo.dwZpos)) > mMoveResolution)
    {
    	if(mX2Axis.mEvent)
        {
            mX2Axis.mEvent(mJoyInfo.dwZpos);
        }
        mX2Axis.mPosition = mJoyInfo.dwZpos;
    }

    //Check Y2 Axis
//    if(abs((int) (mY2Axis.mPosition - mJoyInfo.dwRpos)) > mMoveResolution)
    {
    	if(mY2Axis.mEvent)
        {
            mY2Axis.mEvent(mJoyInfo.dwRpos);
        }
        mY2Axis.mPosition = mJoyInfo.dwRpos;
    }

    //Process retrieved buttons states
    bitset<32> buttonStates(mJoyInfo.dwButtons);
    for(int i = 0; i < mNrOfButtons; i++)
    {
        if(buttonStates.at(i) && mButtons[i].mButtonState == bsUp)
        {
            if(mButtons[i].mEvents.first)
            {
                Log(lDebug5) << "Calling OnButton"<<i + 1<<"Down";
                mButtons[i].mEvents.first();
            }
            mButtons[i].mButtonState = bsDown;
        }

        else if(!buttonStates.at(i) && mButtons[i].mButtonState == bsDown)
        {
            if(mButtons[i].mEvents.second)
            {
                Log(lDebug5) << "Calling OnButton"<<i + 1<<"Up";
                mButtons[i].mEvents.second();
            }
            mButtons[i].mButtonState = bsUp;
        }
    }

    //Process POV event
    if(mJoyInfo.dwPOV != mPOV.mPOVState)
    {
        Log(lDebug5) << "POV State changed";


        //Get out of old state
    	switch(mPOV.mPOVState)
        {
        	case pvUp:
            	if(mPOV.mUpButtonEvents.second)
                {
            		mPOV.mUpButtonEvents.second();
                }
			break;

        	case pvRight:
            	if(mPOV.mRightButtonEvents.second)
                {
            		mPOV.mRightButtonEvents.second();
                }
			break;

        	case pvDown:
            	if(mPOV.mDownButtonEvents.second)
                {
            		mPOV.mDownButtonEvents.second();
                }
			break;
        	case pvLeft:
            	if(mPOV.mLeftButtonEvents.second)
                {
            		mPOV.mLeftButtonEvents.second();
                }
			break;
        }

        //Employ new state
        switch(mJoyInfo.dwPOV)
        {
        	case pvUp:
            	if(mPOV.mUpButtonEvents.first)
                {
            		mPOV.mUpButtonEvents.first();
                }
			break;

        	case pvRight:
            	if(mPOV.mRightButtonEvents.first)
                {
            		mPOV.mRightButtonEvents.first();
                }
			break;

        	case pvDown:
            	if(mPOV.mDownButtonEvents.first)
                {
            		mPOV.mDownButtonEvents.first();
                }
			break;
        	case pvLeft:
            	if(mPOV.mLeftButtonEvents.first)
                {
            		mPOV.mLeftButtonEvents.first();
                }
			break;
            case pvNotEngaged:
	           	Log(lInfo) <<"POV not engaged anymore.";
            break;

            default:
            	Log(lInfo) <<"User presssed two POV buttons at the same time.";
			break;
        }

        mPOV.mPOVState = mJoyInfo.dwPOV;
    }
}

