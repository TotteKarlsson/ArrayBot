#pragma hdrstop
#include "atMoveCoverSlipAtAngleProcess.h"
#include "atArrayBot.h"
#include "dslMathUtils.h"
#include "atAPTMotor.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{

    //---------------------------------------------------------------------------
    MoveCoverSlipAtAngleProcess::MoveCoverSlipAtAngleProcess(const string& lbl)
    :
    Process(lbl),
    mCSZMtr(NULL),
    mCSYMtr(NULL),
    mWHZMtr(NULL),
    mWHYMtr(NULL),
    mLiftVelocity(0),
    mLiftAcceleration(0),
    mLiftAngle(0),
    mLiftHeight(0),
    mLateralVelocity(0),
    mLateralAcceleration(0),
    mMoveWhiskerInParallel(false),
    mLeaveWhiskerByBeach(false),
    mLWBBDeltaZ(0),
    mLWBB_Y_Move(0),
    mStartWhiskerZ(0),
    mFetchAngleFromCSAngleMotor(false),
    mIsWhiskerLogicDone(false)
    {
    	mProcessType = ptMoveCoverSlipAtAngle;
    }

    const string MoveCoverSlipAtAngleProcess::getTypeName() const
    {
    	return ::toString(mProcessType);
    }

    bool MoveCoverSlipAtAngleProcess::assignMotors(APTMotor* csz, APTMotor* csy, APTMotor* wz, APTMotor* wy)
    {
    	//We may wanna do some error checking here
        mCSZMtr = csz;
        mCSYMtr = csy;
        mWHZMtr = wz;
        mWHYMtr = wy;

    	return (mCSZMtr && mCSYMtr && mWHZMtr && mWHYMtr) == true ? true : false;
    }

    double MoveCoverSlipAtAngleProcess::getCurrentCoverSlipZ()
    {
    	if(mCSZMtr)
        {
        	return mCSZMtr->getPosition();
        }

        return -1;
    }

    void MoveCoverSlipAtAngleProcess::setLiftVelocity(double val)
    {
        mLiftVelocity = val;
    }

    double MoveCoverSlipAtAngleProcess::getLiftVelocity()
    {
    	return mLiftVelocity;
    }

    void MoveCoverSlipAtAngleProcess::setLiftAcceleration(double val)
    {
    	mLiftAcceleration = val;
    }

    double MoveCoverSlipAtAngleProcess::getLiftAcceleration()
    {
    	return mLiftAcceleration;
    }

    void MoveCoverSlipAtAngleProcess::setLiftAngle(double val)
    {
    	mLiftAngle = val;
    }

    double MoveCoverSlipAtAngleProcess::getLiftAngle()
    {
    	return mLiftAngle;
    }

    void MoveCoverSlipAtAngleProcess::setLiftHeight(double val)
    {
    	mLiftHeight = val;
    }

    double MoveCoverSlipAtAngleProcess::getLiftHeight()
    {
    	return mLiftHeight;
    }

    void MoveCoverSlipAtAngleProcess::setYMoveScaling(double val)
    {
    	mYMoveScaling = val;
    }

    double MoveCoverSlipAtAngleProcess::getYMoveScaling()
    {
    	return mYMoveScaling;
    }

    bool MoveCoverSlipAtAngleProcess::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    bool MoveCoverSlipAtAngleProcess::isBeingProcessed()
    {
    	if(isDone())
        {
    		mIsBeingProcessed 	= false;
            mIsProcessed 		= true;
           	Timestamp now;
            mEndTime = now;
        }

        return mIsBeingProcessed;
    }

    bool MoveCoverSlipAtAngleProcess::isProcessed()
    {
        if(mIsProcessed == true)
        {
        	return true;
        }

        if(isDone())
        {
            //Consider this process to be "processed"
            mIsProcessed 		= true;
            mIsBeingProcessed 	= false;
            return true;
        }

    	return false;
    }

    //Init is called by the sequencer BEFORE executing the process
    void MoveCoverSlipAtAngleProcess::init(ArrayBot& ab)
    {
        if(assignMotors(ab.getCoverSlipUnit().getZMotor(), ab.getCoverSlipUnit().getYMotor(), ab.getWhiskerUnit().getZMotor(), ab.getWhiskerUnit().getYMotor()))
        {
    	    calculateLift(ab);
        }
        else
        {
        	Log(lError) << "At least one motor is missing for the Move CoverSlip at angle process!";
        }

        mIsWhiskerLogicDone = false;
    	Process::init(ab);
    }


    //The calculate move function uses move velocity and angle to calculate
    //velocities for lateral movement, as well as final positions
    bool MoveCoverSlipAtAngleProcess::calculateLift(ArrayBot& ab)
    {
        if(mFetchAngleFromCSAngleMotor)
        {
            APTMotor* m = ab.getCoverSlipUnit().getAngleMotor();
            if(m)
            {
                mLiftAngle = m->getPosition();
            }
            else
            {
                Log(lError) << "Failed getting CS Angle motor. Liftangle NOT updated";
            }
        }

    	//The knowns are Z velocity and acceleration, and theta
        //Calculate Y velocity and acceleration
        //We get Y velocity as ZVelocity/tan(theta)
        if(mLiftAngle > 0 || mLiftAngle < 90)
        {
        	double tanVal = tan(toRadians(mLiftAngle));
            if(tanVal)
            {
                mLateralVelocity 		= (mLiftVelocity / tanVal) 		* mYMoveScaling;
                mLateralAcceleration 	= (mLiftAcceleration / tanVal)  * mYMoveScaling;
                mTargetCSZ = mLiftHeight;
                mTargetWHZ = mLiftHeight;
                mTargetCSY = mTargetCSZ / tanVal;
                mTargetWHY = mTargetCSZ / tanVal;
            }
            else
            {
            	return false;
            }
        }
        else
        {
        	return false;
        }

    	return true;
    }


    bool MoveCoverSlipAtAngleProcess::start()
    {
    	//Set motor parameters and move them to their position
        if(!mCSZMtr || !mCSYMtr || !mWHZMtr || !mWHYMtr)
        {
    		Log(lError) << "At least one motor in the LiftAtAngle process is NULL. Can't start process";
            return false;
        }

        //Z & Y
        mCSZMtr->setVelocityParameters(mLiftVelocity, 		mLiftAcceleration);
        mCSYMtr->setVelocityParameters(mLateralVelocity, 	mLateralAcceleration);

    	if(mMoveWhiskerInParallel)
        {
    	    mIsWhiskerLogicDone = false;
    		mWHZMtr->setVelocityParameters(mLiftVelocity, 		mLiftAcceleration);
        	mWHYMtr->setVelocityParameters(mLateralVelocity, 	mLateralAcceleration);
        }

        //Calculate goto positions
        //The stages are configured so that z decreases during lift, while
        //Y increases
        mTargetCSZR = getMotorPosition(mCSZMtr) - mTargetCSZ;
        mTargetCSYR = getMotorPosition(mCSYMtr) + mTargetCSY;

        mTargetWHZR = getMotorPosition(mWHZMtr) - mTargetWHZ;
        mTargetWHYR = getMotorPosition(mWHYMtr) + mTargetWHY;

    	mStartWhiskerZ = getMotorPosition(mWHZMtr);

        Log(lInfo) << "Moving motor: "<< mCSZMtr->getName() <<" to position: "<< mTargetCSZR;
        Log(lInfo) << "Moving motor: "<< mCSYMtr->getName() <<" to position: "<< mTargetCSYR;

        mCSZMtr->moveToPosition(mTargetCSZR);
        mCSYMtr->moveToPosition(mTargetCSYR);

    	if(mMoveWhiskerInParallel)
        {
    	    Log(lInfo) << "Moving motor: "<< mWHZMtr->getName() <<" to position: "<< mTargetWHZR;
        	Log(lInfo) << "Moving motor: "<< mWHYMtr->getName() <<" to position: "<< mTargetWHYR;

        	mWHZMtr->moveToPosition(mTargetWHZR);
            mWHYMtr->moveToPosition(mTargetWHYR);
        }

    	return Process::start();
    }

    bool MoveCoverSlipAtAngleProcess::stop()
    {
    	if(mCSZMtr)
    		mCSZMtr->stop();

    	if(mCSYMtr)
    		mCSYMtr->stop();

    	if(mWHZMtr)
    		mWHZMtr->stop();

    	if(mWHYMtr)
    		mWHYMtr->stop();
    	return Process::stop();
    }

    //The process sequencer will call this function periodically
    bool MoveCoverSlipAtAngleProcess::isDone()
    {
    	//Check motor positions
        if(isEqual(getMotorPosition(mCSZMtr), mTargetCSZR, 1.e-3))
        {
        	//The CS Z motor is the 'master'
            mCSYMtr->stop();
    		mWHZMtr->stop();
    		mWHYMtr->stop();

        	return true;
        }

        //When leaving whisker by the beach...
    	if(mMoveWhiskerInParallel && mLeaveWhiskerByBeach)
        {
        	//Check for Delta Z
        	if(fabs(mWHZMtr->getPosition() - mStartWhiskerZ) >= mLWBBDeltaZ)
            {
            	if(!mIsWhiskerLogicDone)
                {
                	mWHZMtr->setVelocityParameters(mLiftVelocity 	* 1.5, 		mLiftAcceleration * 1.5);
    		    	mWHYMtr->setVelocityParameters(mLateralVelocity * 1.5, 		mLateralAcceleration* 1.5);

            		mWHYMtr->moveToPosition(mWHYMtr->getPosition() - mLWBB_Y_Move);
    	            mWHZMtr->moveToPosition(mWHZMtr->getPosition() - mLWBB_Z_Move);
                    mIsWhiskerLogicDone = true;
                }
            }
        }
        return false;
    }

    bool MoveCoverSlipAtAngleProcess::resume()
    {
        return false;
    }

    bool MoveCoverSlipAtAngleProcess::undo()
    {
    	return false;
    }

    XMLElement* MoveCoverSlipAtAngleProcess::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
    {
    	XMLElement* dataval1 = doc.NewElement("lift_velocity");
        dataval1->SetText(dsl::toString(mLiftVelocity).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("lift_acceleration");
        dataval1->SetText(dsl::toString(mLiftAcceleration).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("lift_angle");
        dataval1->SetText(dsl::toString(mLiftAngle).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("lift_height");
        dataval1->SetText(dsl::toString(mLiftHeight).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("y_move_scaling");
        dataval1->SetText(dsl::toString(mYMoveScaling).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("move_whisker_in_parallel");
        dataval1->SetText(dsl::toString(mMoveWhiskerInParallel).c_str());
    	docRoot->InsertEndChild(dataval1);

        //Leave whisker by beach parameters
    	dataval1 = doc.NewElement("leave_whisker_by_beach");
        dataval1->SetText(dsl::toString(mLeaveWhiskerByBeach).c_str());
    	docRoot->InsertEndChild(dataval1);

       	dataval1 = doc.NewElement("leave_whisker_by_beach_delta_z_trigger");
        dataval1->SetText(dsl::toString(mLWBBDeltaZ).c_str());
    	docRoot->InsertEndChild(dataval1);

       	dataval1 = doc.NewElement("leave_whisker_by_beach_y_move");
        dataval1->SetText(dsl::toString(mLWBB_Y_Move).c_str());
    	docRoot->InsertEndChild(dataval1);

       	dataval1 = doc.NewElement("leave_whisker_by_beach_z_move");
        dataval1->SetText(dsl::toString(mLWBB_Z_Move).c_str());
    	docRoot->InsertEndChild(dataval1);

    	dataval1 = doc.NewElement("fetch_angle_from_CS_angle_motor");
        dataval1->SetText(dsl::toString(mFetchAngleFromCSAngleMotor).c_str());
    	docRoot->InsertEndChild(dataval1);

        return dynamic_cast<XMLElement*>(docRoot);
    }

    bool MoveCoverSlipAtAngleProcess::populateFromXML(XMLElement* element)
    {
        //This code belongs in the process class!
        XMLElement* data = element->FirstChildElement("info");
        if(data && data->GetText())
        {
            setInfoText(data->GetText());
        }

        data = element->FirstChildElement("lift_velocity");
        if(data && data->GetText())
        {
            setLiftVelocity(toDouble(data->GetText()));
        }

        data = element->FirstChildElement("lift_acceleration");
        if(data && data->GetText())
        {
            setLiftAcceleration(toDouble(data->GetText()));
        }

        data = element->FirstChildElement("lift_angle");
        if(data && data->GetText())
        {
            setLiftAngle(toDouble(data->GetText()));
        }

        data = element->FirstChildElement("lift_height");
        if(data && data->GetText())
        {
            setLiftHeight(toDouble(data->GetText()));
        }

        data = element->FirstChildElement("y_move_scaling");
        if(data && data->GetText())
        {
            mYMoveScaling = toDouble(data->GetText());
        }

        data = element->FirstChildElement("move_whisker_in_parallel");
        if(data && data->GetText())
        {
            setMoveWhiskerInParallel(toBool(data->GetText()));
        }

        data = element->FirstChildElement("leave_whisker_by_beach");
        if(data && data->GetText())
        {
            mLeaveWhiskerByBeach = toBool(data->GetText());
        }

        data = element->FirstChildElement("leave_whisker_by_beach_delta_z_trigger");
        if(data && data->GetText())
        {
            mLWBBDeltaZ = toDouble(data->GetText());
        }

        data = element->FirstChildElement("leave_whisker_by_beach_y_move");
        if(data && data->GetText())
        {
            mLWBB_Y_Move = toDouble(data->GetText());
        }

        data = element->FirstChildElement("leave_whisker_by_beach_z_move");
        if(data && data->GetText())
        {
            mLWBB_Z_Move = toDouble(data->GetText());
        }

        data = element->FirstChildElement("fetch_angle_from_CS_angle_motor");
        if(data && data->GetText())
        {
            setFetchAngleFromCSAngleMotor(toBool(data->GetText()));
        }


        return true;

    }

}
