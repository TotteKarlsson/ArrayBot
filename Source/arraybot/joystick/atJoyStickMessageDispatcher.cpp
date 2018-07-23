#pragma hdrstop
#include "atJoyStickMessageDispatcher.h"
#include "atArrayBotJoyStick.h"
#include <bitset>
#include "dslLogger.h"
#include "core/atExceptions.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;

namespace at
{
    JoyStickMessageDispatcher::JoyStickMessageDispatcher(ArrayBotJoyStick& js, int nrOfButtons, int& id)
    :
    mJoyStickID(id),
    mJoyStick(js),
    mEnabled(false),
    mNrOfButtons(nrOfButtons)
    {
        mUpdateStateTimer.setInterval(50);
    	mUpdateStateTimer.OnTimerC = refresh;

       	mEnabled = readCapabilities();

        //Setup buttons
        for(int i = 0; i < mNrOfButtons; i++)
        {
        	//mButtons.push_back(JoyStickButtonStateEventDispatcher());
    		mButtonStates.push_back(JoyStickButtonStateEventDispatcher(js.getButton(i+1)));
        }
    }

    JoyStickMessageDispatcher::~JoyStickMessageDispatcher()
    {}

    bool JoyStickMessageDispatcher::isEnabled()
    {
    	return mUpdateStateTimer.isRunning();
    }

    bool JoyStickMessageDispatcher::isValid()
    {
    	return checkCapabilities(mJoyStickID);
    }

    bool JoyStickMessageDispatcher::enable(int id)
    {
    	mJoyStickID = id;
       	Log(lInfo) << "Enabling Joystick with ID:"<<id;
    	if(checkCapabilities(mJoyStickID))
        {
        	mEnabled = readCapabilities();
            if(mEnabled)
            {
        		mUpdateStateTimer.start();
            }
        }
        else
        {
        	mEnabled = false;
        }

        if(!mEnabled)
        {
        	Log(lWarning) << "Failed to enable JS Message Dispatcher using ID:"<<id;
        }
        return mEnabled;
    }

    void JoyStickMessageDispatcher::disable()
    {
    	mUpdateStateTimer.stop();
    }

    bool JoyStickMessageDispatcher::checkCapabilities(int ID)
    {
        JOYCAPS capabilities;
        if(ID < 0 || ID > 1)
        {
    		Log(lError) << "Invalid JoyStickID: "<<-1;
        	return false;
        }

        int res = joyGetDevCaps(ID, &capabilities, sizeof(JOYCAPS));
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

            return false;
        }
    	return true;
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

            Log(lError) <<"This driver supports "<<joyGetNumDevs()<<" joystick devices";
            Log(lError) <<"Failed getting joystick capabilities";
            return false;
        }
    	return true;
    }

    void JoyStickMessageDispatcher::setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down, bool clickOnly)
    {
    	mButtonStates[btnNr  - 1].mEvents = ButtonEvents(up, down);
    	mButtonStates[btnNr  - 1].mClickEventOnly = clickOnly;
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

        mJoyInfo.dwSize  	=  sizeof(JOYINFOEX);
        mJoyInfo.dwFlags 	= JOY_RETURNALL;

        int res 			= joyGetPosEx(mJoyStickID, &mJoyInfo);
        if(res != JOYERR_NOERROR)
        {
       	    mJoyStickID = -1;
        	mEnabled = false;
            Log(lError) << "Failed getting joystick information";
            return;
        }

        //Coverslip X Axis
        if(mJoyStick.mCoverSlipAxesEnabled && mX1Axis.mEvent)
        {
          	static DWORD val(0);
            if(val != mJoyInfo.dwXpos)
            {
            	val = mJoyInfo.dwXpos;
    	        mX1Axis.mEvent(mJoyInfo.dwXpos);
            }
        }

        //Coverslip Y Axis
        if(mJoyStick.mCoverSlipAxesEnabled && mY1Axis.mEvent)
        {
          	static DWORD val(0);
            if(val != mJoyInfo.dwYpos)
            {
            	val = mJoyInfo.dwYpos;
            	mY1Axis.mEvent(mJoyInfo.dwYpos);
            }
        }

        //Whisker X
        if(mJoyStick.mWhiskerAxesEnabled && mX2Axis.mEvent)
        {
          	static DWORD val(0);
            if(val != mJoyInfo.dwZpos)
            {
            	val = mJoyInfo.dwZpos;
    	        mX2Axis.mEvent(val);
            }
        }

        //Whisker Y
        if(mJoyStick.mWhiskerAxesEnabled && mY2Axis.mEvent)
        {
        	static DWORD val(0);
            if(val != mJoyInfo.dwRpos)
            {
            	val = mJoyInfo.dwRpos;
            	mY2Axis.mEvent(val);
            }
        }

        mX1Axis.mPosition = mJoyInfo.dwXpos;
        mY1Axis.mPosition = mJoyInfo.dwYpos;
        mX2Axis.mPosition = mJoyInfo.dwZpos;
    	mY2Axis.mPosition = mJoyInfo.dwRpos;

        //Process retrieved buttons states
        bitset<32> buttonStates(mJoyInfo.dwButtons);
        int btnPressed = mJoyInfo.dwButtonNumber;

        if(btnPressed)
        {
        	Log(lDebug2) << "There are "<<btnPressed<<" buttons pressed";

            //Print button states
            stringstream states;
            for(int i = 0; i < buttonStates.size(); i++)
            {
    			states << buttonStates[i] <<" ";
            }
            Log(lDebug2) << states.str();
        }

        //First process buttons 1-4 (Z and angle control)
        if(mJoyStick.mWhiskerZButtonsEnabled)
        {
            for(int i = 0; i < 4; i++)
            {
                if(buttonStates.at(i) && mButtonStates[i].getButtonState() == bsUp)
                {
                    if(mButtonStates[i].mEvents.first)
                    {
                        Log(lDebug5) << "Calling OnButton"<<i + 1<<"Down";
                        mButtonStates[i].mEvents.first();
                    }
                    mButtonStates[i].setButtonState(bsDown);
                }

                else if(!buttonStates.at(i) && mButtonStates[i].getButtonState() == bsDown)
                {
                    if(mButtonStates[i].mEvents.second)
                    {
                        Log(lDebug5) << "Calling OnButton"<<i + 1<<"Up";
                        mButtonStates[i].mEvents.second();
                    }
                    mButtonStates[i].setButtonState(bsUp);
                }
            }
        }

        for(int i = 4; i < mNrOfButtons; i++)
        {
            if(buttonStates.at(i))
            {
                if(mButtonStates[i].mClickEventOnly)
                {
                    if(mButtonStates[i].getButtonState() == bsUp)
                    {
                        mButtonStates[i].setButtonState(bsDown);
                        if(mButtonStates[i].mEvents.first)
                        {
    	                    Log(lDebug5) << "Calling OnButton"<<i + 1<<" Down";
                            mButtonStates[i].mEvents.first();
                        }
                    }
                }
                else
                {
                    if(mButtonStates[i].mEvents.first)
                    {
                        Log(lDebug5) << "Calling OnButton"<<i + 1<<" Down";
                        mButtonStates[i].mEvents.first();
                    }
                }
            }
            else
            {
                if(mButtonStates[i].mClickEventOnly)
                {
                    mButtonStates[i].setButtonState(bsUp);
                    if(mButtonStates[i].mEvents.second)
                    {
    	                Log(lDebug5) << "Calling OnButton"<<i + 1<<" Up";
                        mButtonStates[i].mEvents.second();
                    }
                }
                else
                {
                    if(mButtonStates[i].mEvents.second)
                    {
                        Log(lDebug5) << "Calling OnButton"<<i + 1<<" Up";
                        mButtonStates[i].mEvents.second();
                    }
                }
            }
        }

        //Process POV event
        if((mJoyInfo.dwPOV != mPOV.mPOVState) && mJoyStick.mCoverSlipZButtonsEnabled)
        {
            Log(lDebug3) << "POV State changed";

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

                case pvNotEngaged: 	Log(lDebug5) <<"POV not engaged anymore."; break;
                default:	       	Log(lDebug5) <<"User presssed two POV buttons at the same time."; break;
            }

            mPOV.mPOVState = mJoyInfo.dwPOV;
        }
    }

    unsigned long JoyStickMessageDispatcher::getButtonBits()
    {
    	return mJoyInfo.dwButtons;
    }

    unsigned long JoyStickMessageDispatcher::getPOVBits()
    {
    	return mJoyInfo.dwPOV;
    }

    unsigned long JoyStickMessageDispatcher::getX1Pos()
    {
    	return mJoyInfo.dwXpos;
    }

    unsigned long JoyStickMessageDispatcher::getY1Pos()
    {
    	return mJoyInfo.dwYpos;
    }

    unsigned long JoyStickMessageDispatcher::getZ1Pos()
    {
    	return mJoyInfo.dwZpos;
    }

    unsigned long JoyStickMessageDispatcher::getX2Pos()
    {
    	return mJoyInfo.dwRpos;
    }

    unsigned long JoyStickMessageDispatcher::getY2Pos()
    {
    	return mJoyInfo.dwUpos;
    }

    unsigned long JoyStickMessageDispatcher::getZ2Pos()
    {
    	return mJoyInfo.dwVpos;
    }

}

