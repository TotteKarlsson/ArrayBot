#pragma hdrstop
#include "atNavitarMotor.h"
#include "atNavitarMotorController.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;

namespace at
{
    NavitarMotor::NavitarMotor(NavitarMotorController& mc, int ID)
    :
    mMotorController(mc),
    mID(ID),
    mLabel(ID == 2 ? "Focus" : "Zoom")
    {
    	//Setup registers
    	mRegisters.USER_TARGET 			= mID == 1 ? REG_USER_TARGET_1 		  :  REG_USER_TARGET_2;
        mRegisters.USER_INCREMENT       = mID == 1 ? REG_USER_INCREMENT_1 	  :  REG_USER_INCREMENT_2;
        mRegisters.USER_CURRENT         = mID == 1 ? REG_USER_CURRENT_1 	  :  REG_USER_CURRENT_2;
        mRegisters.USER_LIMIT           = mID == 1 ? REG_USER_LIMIT_1 		  :  REG_USER_LIMIT_2;
        mRegisters.USER_STATUS          = mID == 1 ? REG_USER_STATUS_1        :  REG_USER_STATUS_2;
        mRegisters.SETUP_ACCEL          = mID == 1 ? REG_SETUP_ACCEL_1        :  REG_SETUP_ACCEL_2;
        mRegisters.SETUP_INITVELOCITY   = mID == 1 ? REG_SETUP_INITVELOCITY_1 :  REG_SETUP_INITVELOCITY_2;
        mRegisters.SETUP_MAXVELOCITY    = mID == 1 ? REG_SETUP_MAXVELOCITY_1  :  REG_SETUP_MAXVELOCITY_2;
        mRegisters.SETUP_REVBACKLASH    = mID == 1 ? REG_SETUP_REVBACKLASH_1  :  REG_SETUP_REVBACKLASH_2;
        mRegisters.SETUP_FWDBACKLASH    = mID == 1 ? REG_SETUP_FWDBACKLASH_1  :  REG_SETUP_FWDBACKLASH_2;
        mRegisters.SETUP_SENSORTYPE     = mID == 1 ? REG_SETUP_SENSORTYPE_1   :  REG_SETUP_SENSORTYPE_2;
        mRegisters.SETUP_CONFIG         = mID == 1 ? REG_SETUP_CONFIG_1 	  :  REG_SETUP_CONFIG_2;
        mRegisters.SETUP_LIMIT          = mID == 1 ? REG_SETUP_LIMIT_1 		  :  REG_SETUP_LIMIT_2;
    }

    string NavitarMotor::getLabel()
    {
    	return mLabel;
    }

    void NavitarMotor::home()
    {
    	long temp = 0;
    	mMotorController.write(mRegisters.USER_LIMIT, temp);
    }

    void NavitarMotor::limit()
    {
    	long temp = 1;
    	mMotorController.write(mRegisters.USER_LIMIT, temp);
    }

    int	NavitarMotor::getPosition()
    {
    	long pos;
    	mMotorController.read(mRegisters.USER_CURRENT, pos);
        return pos;
    }

    int	NavitarMotor::setPosition(int pos)
    {
    	long temp = pos;
    	return mMotorController.write(mRegisters.USER_TARGET, temp);
    }

    int	NavitarMotor::addToPosition(int delta)
    {
    	int currentPosition = getPosition();
        int newPos(currentPosition + delta);
        return setPosition(newPos);
    }

    int	NavitarMotor::getMaxPosition()
    {
    	long pos;
    	mMotorController.read(mRegisters.SETUP_LIMIT, pos);
        return pos;
    }


}
