#pragma hdrstop
#include "atUC7Component.h"
#include "dslIniFile.h"
#include "dslLogger.h"
#include "dslStringUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;

namespace at
{

    UC7::UC7(HWND__ *h)
    :
    	mINIFileSection("UC7"),
        mCOMPort(-1),
        mSerial(-1, 19200, '!', '\r', SerialPort::EHandshake::EHandshakeOff),
        mFeedRate(0),
        mPrepareForNewRibbon(false),
        mPrepareToCutRibbon(false),
        mPresetFeedRate(70),
    	mUC7MessageReceiver(*this, h),
        mUC7MessageSender(*this),
        mIsActive(false),
        mSetNumberOfZeroStrokes(0),
        mNumberOfZeroStrokes(0),
        mNorthLimitPosition(0),
    	mKnifeStageJogPreset(0),
        mKnifeStageResumeDelta(0),
    	mCuttingSpeed(0),
    	mReturnSpeed(0),
        mStopMode(smDirect)

    {
    	mSerial.assignMessageReceivedCallBack(onSerialMessage);
        mCustomTimer.setInterval(5);
        mRibbonOrderCounter.enable();
    }

    UC7::~UC7()
    {
    	disConnect();
    }

    bool UC7::connect(int com)
    {
    	Log(lInfo) << "Connecting UC7 client on COM"<<com;


        if(!mSerial.connect(com, 19200))
        {
    		return false;
        }

        //Only start these on succesfull connection
        mUC7MessageReceiver.start();
        mUC7MessageSender.start();
        return true;
    }

    bool UC7::disConnect()
    {
        mUC7MessageSender.stop();
        mUC7MessageReceiver.stop();
    	return mSerial.disConnect();
    }

    bool UC7::isConnected()
    {
    	return mSerial.isConnected();
    }

    bool UC7::prepareForNewRibbon()
    {
    	return mPrepareForNewRibbon;
    }

    void UC7::prepareForNewRibbon(bool what)
    {
    	mPrepareForNewRibbon = what;
    }

    bool UC7::prepareToCutRibbon()
    {
    	return mPrepareToCutRibbon;
    }

    void UC7::prepareToCutRibbon(bool what)
    {
    	mPrepareToCutRibbon = what;
    }

    bool UC7::setStrokeState(UC7StrokeState state)
    {
    	mStrokeState = state;
        mUC7StatusHistory.insert(UC7StatusPoint(mStrokeState));
        switch(mStrokeState)
        {
        	case UC7StrokeState::ssBeforeCutting:
            	if(mStopMode == CutterStopMode::smBeforeCutting)
                {
                	stopCutter();
                }

            break;
        	case UC7StrokeState::ssCutting:        		break;
        	case UC7StrokeState::ssAfterCutting:
               	if(mStopMode == CutterStopMode::smAfterCutting)
                {
                	stopCutter();
                }
            break;
        	case UC7StrokeState::ssRetracting:
            	if(mStopMode == CutterStopMode::smBeforeRetracting)
                {
                	stopCutter();
                }
            break;

            default:
            break;

        }

        if(state == ssCutting && mFeedRate == 0)
        {
        	mNumberOfZeroStrokes++;
        }

        if(mFeedRate != 0)
        {
    		mNumberOfZeroStrokes = 0;
        }

        //When the state changes, certain events may take place
        if(mPrepareToCutRibbon)
        {
            if(mStrokeState == ssAfterCutting)
            {
                if(mFeedRate != 0)
                {
    	            Log(lInfo) << "Setting feedrate to 0 nm";
                	setFeedRate(0);
                }
                else
                {
    	            Log(lInfo) << "Executing ZERO stroke";
                }
            }
            else if(mStrokeState == ssRetracting && mFeedRate == 0)
            {
            	if(mNumberOfZeroStrokes >= mSetNumberOfZeroStrokes)
                {
                	mCustomTimer.assignTimerFunction(onPrepareToCutRibbon);
                	mCustomTimer.start();
                	Log(lInfo) << "Started Custom Timer";
                	prepareToCutRibbon(false);
                }
            }
        }
        else if(mPrepareForNewRibbon)
        {
    //        if(mPrepareForNewRibbon == true && mStrokeState == ssAfterCutting)
    //        {
    //            //Log(lInfo) << "Preparing NEW Ribbon: (1) Setting feedrate to: "<<mPresetFeedRate<<" nm";
    //            //setFeedRate(mPresetFeedRate);
    //        }
            if (mStrokeState == ssRetracting)// && mFeedRate == mPresetFeedRate)
            {
            	//This will move the stage
                mCustomTimer.assignTimerFunction(onPrepareForNewRibbon);
                mCustomTimer.start();
                Log(lInfo) << "Started Custom Timer in order to move KNIFE STAGE";
                prepareForNewRibbon(false);
            }
        }
        return true;
    }

    bool UC7::setStageMoveDelay(int ms)
    {
    	return mCustomTimer.setInterval(ms);
    }

    bool UC7::setNorthLimitPosition(uint limit)
    {
    	mNorthLimitPosition = limit;
        return true;
    }

    void UC7::onPrepareToCutRibbon()
    {
        mCustomTimer.stop();
    //	Log(lInfo) << "Moving Knife stage ============ SOUTH "<<mKnifeStageJogPreset<<" (nm) ==================";
    //    jogKnifeStageSouth(mKnifeStageJogPreset);
        mRibbonOrderCounter.increase();
    }

    void UC7::onPrepareForNewRibbon()
    {
        mCustomTimer.stop();
    //    uint distance(mKnifeStageJogPreset - mKnifeStageResumeDelta);
    //	Log(lInfo) << "Moving Knife stage ============ NORTH "<<distance<<" (nm) ==================";
    //    jogKnifeStageNorth(distance);
    }

    bool UC7::getStatus()
    {
    	//Query HW status
        if(!getCutterMotorStatus())
        {
        	Log(lError) << "Failed query: Cutter Status";
        }

    	//Query HW status
        if(!getCurrentFeedRate())
        {
        	Log(lError) << "Failed query: FeedRate";
        }

    	if(!getKnifeStagePosition())
        {
        	Log(lError) << "Failed query: Feed, Absolute position";
        }
        return true;
    }

    bool UC7::getVersion()
    {
    	return false;
    }

    bool UC7::hasMessage()
    {
    	return mIncomingMessagesBuffer.size() ? true : false;
    }

    UC7Message UC7::getLastSentMessage()
    {
    	return mUC7Message;
    }

    //This one is called from serial port listening thread
    void UC7::onSerialMessage(const string& msg)
    {
    	Log(lDebug) << "Decoding UC7 message: "<<msg;
        UC7Message cmd(msg, true, true);
        if(cmd.check())
        {
    		//Get mutex using a scoped lock
            {
            	Poco::ScopedLock<Poco::Mutex> lock(mReceiveBufferMutex);
    	        mIncomingMessagesBuffer.push_back(cmd);
            }

            //Send a signal
            mNewReceivedMessageCondition.signal();
        }
        else
        {
       		Log(lError) << "Bad checksum for message: "<<msg<<" Message discarded";
        }
    }

    bool UC7::sendRawMessage(const string& msg)
    {
    	//Put the message on the utgoing queue
        {
            Poco::ScopedLock<Poco::Mutex> lock(mSendBufferMutex);
        	mOutgoingMessagesBuffer.push_back(msg);
        }

        //Send a signal
        mNewMessageToSendCondition.signal();
    	return true;
    }

    bool UC7::startCutter()
    {
    	return sendUC7Message(CUTTING_MOTOR_CONTROL, "01");
    }

    bool UC7::stopCutter(UC7::CutterStopMode sm)
    {
    	mStopMode = sm;
    	if(mStopMode == smDirect)
        {
        	return sendUC7Message(CUTTING_MOTOR_CONTROL, "00");
        }
        return true;
    }

    bool UC7::getKnifeStagePosition()
    {
    	return sendUC7Message(NORTH_SOUTH_MOTOR_MOVEMENT, "FF");
    }

    bool UC7::moveKnifeStageNSAbsolute(unsigned int pos, bool isRequest)
    {
    	string dataStr(zeroPadString(6, toHex(pos)));
    	sendUC7Message(NORTH_SOUTH_MOTOR_MOVEMENT, "01", dataStr);
        return true;
    }

    bool UC7::jogKnifeStageSouth(uint step, bool useAbsolutePos, bool isRequest)
    {
    	if(useAbsolutePos)
        {
    		int pos = mNorthSouthStagePosition - step;

    		pos = pos < 0 ? 0 : pos;
            return moveKnifeStageNSAbsolute(pos, isRequest);
        }
        else
        {
    		string dataStr(zeroPadString(4, toHex(step)));
    		return sendUC7Message(NORTH_SOUTH_MOTOR_MOVEMENT, "06", dataStr);
        }
    }

    bool UC7::jogKnifeStageNorth(uint step, bool useAbsolutePos, bool isRequest)
    {
    	if((step + mNorthSouthStagePosition) > mNorthLimitPosition)
        {
        	Log(lError) << "Can't move stage past NORTH limit: "<< mNorthLimitPosition;
            return false;
        }

        if(useAbsolutePos)
        {
    		int pos = mNorthSouthStagePosition + step;
            return moveKnifeStageNSAbsolute(pos, isRequest);
        }
        else
        {
    		string dataStr(zeroPadString(4, toHex(step)));
    		return sendUC7Message(NORTH_SOUTH_MOTOR_MOVEMENT, "07", dataStr);
        }
    }

    bool UC7::stopKnifeStageNSMotion()
    {
    	Log(lInfo) << "Stopping KnifeStage Motion";
    	return sendUC7Message(NORTH_SOUTH_MOTOR_MOVEMENT, "00");
    }

    void UC7::disableCounter()
    {
    	mSectionCounter.disable();
    }

    void UC7::enableCounter()
    {
    	mSectionCounter.enable();
    }

    bool UC7::setFeedRatePreset(uint rate)
    {
    	mPresetFeedRate = rate;
        return setFeedRate(mPresetFeedRate);
    }

    bool UC7::setKnifeStageJogStepPreset(uint preset)
    {
    	mKnifeStageJogPreset = preset;
        return true;
    }

    bool UC7::setKnifeStageResumeDelta(uint delta)
    {
    	mKnifeStageResumeDelta = delta;
        return true;
    }

    bool UC7::setCuttingSpeed(uint speed, bool isRequest)
    {
    	if(isRequest)
        {
    		string dataStr(zeroPadString(4, toHex(speed)));
    		return sendUC7Message(CUTTING_SPEED, "01", dataStr);
        }

        mCuttingSpeed = speed;
        return true;
    }

    bool UC7::setReturnSpeed(uint speed, bool isRequest)
    {
    	if(isRequest)
        {
    		string dataStr(zeroPadString(4, toHex(speed)));
    		return sendUC7Message(RETURN_SPEED, "01", dataStr);
    		return false;
        }

        mReturnSpeed = speed;
        return true;
    }

    bool UC7::setFeedRate(uint feedRate, bool isRequest)
    {
    	if(isRequest)
        {
    		string dataStr(zeroPadString(4, toHex(feedRate)));
    		return sendUC7Message(FEED, "01", dataStr);
        }

        mFeedRate = feedRate;
    	(mFeedRate > 0) ?  mSectionCounter.enable() : mSectionCounter.disable();
        return true;
    }

    bool UC7::setNorthSouthStageAbsolutePosition(uint pos, bool isRequest)
    {
    	if(isRequest)
        {
        	Log(lWarning) << "Not implemented";
     		return false;
        }

        mNorthSouthStagePosition = pos;
        return true;
    }

    bool UC7::getCutterMotorStatus()
    {
    	return sendUC7Message(CUTTING_MOTOR_CONTROL, "FF");
    }

    int UC7::getCurrentFeedRate(bool isRequest)
    {
    	if(isRequest)
        {
    		return sendUC7Message(FEED, "FF");
        }
       	return mFeedRate;
    }

    bool UC7::sendUC7Message(const UC7MessageEnum& msgName, const string& data1, const string& data2)
    {
    	stringstream cmd;
    	string sender("1");

    	//This function constructs a proper command to send to the UC7
        switch(msgName)
        {
            case SOFTWARE_RESET:   				                    Log(lInfo) << "Not implemented!"; 		break;
            case GET_PART_ID:  					                    Log(lInfo) << "Not implemented!"; 		break;
            case LOGIN:  						                    Log(lInfo) << "Not implemented!"; 		break;
            case COMMAND_TRANSMISSION_ERROR:  	                    Log(lInfo) << "Not implemented!"; 		break;
            case GET_VERSION:		  			                    Log(lInfo) << "Not implemented!"; 		break;

            case FEEDRATE_MOTOR_CONTROL:
            	cmd <<gStepperControllerAddress<<sender<<20<<data1;
    	        mUC7Message.init(cmd.str());
     		break;

            case SEND_POSITION_AT_MOTION:  	    					Log(lInfo) << "Not implemented!"; 		break;

            case FEED:
           		cmd <<gStepperControllerAddress<<sender<<23<<data1<<data2;
    	        mUC7Message.init(cmd.str());
     		break;

            case NORTH_SOUTH_MOTOR_MOVEMENT:
           		cmd <<gStepperControllerAddress<<sender<<30<<data1<<data2;
    	        mUC7Message.init(cmd.str());
     		break;

            case SEND_POSITION_AT_MOVEMENT_NORTH_SOUTH:  			Log(lInfo) << "Not implemented!";   	break;
            case EAST_WEST_MOTOR_MOVEMENT:  						Log(lInfo) << "Not implemented!"; 		break;
            case SEND_POSITION_AT_MOVEMENT_EAST_WEST:  				Log(lInfo) << "Not implemented!"; 		break;

            case CUTTING_MOTOR_CONTROL:
           		cmd <<gMotorControllerAddress<<sender<<20<<data1;
    	        mUC7Message.init(cmd.str());
     		break;

            case CUTTING_SPEED:
    			cmd <<gMotorControllerAddress<<sender<<30<<data1<<data2;
    	        mUC7Message.init(cmd.str());
     		break;

            case RETURN_SPEED:
    			cmd <<gMotorControllerAddress<<sender<<31<<data1<<data2;
    	        mUC7Message.init(cmd.str());
     		break;

            case HANDWHEEL_POSITION:  				                Log(lInfo) << "Not implemented!"; 		break;
            default:        						                Log(lInfo) << "Unhandled Message!";     break;
        }

        Log(lInfo) << "Sending UC7 command: "<<mUC7Message.getMessageNameAsString() <<"\t\t("<<mUC7Message.getFullMessage()<<")";
    	sendRawMessage(mUC7Message.getFullMessage());
        return true;
    }

}
