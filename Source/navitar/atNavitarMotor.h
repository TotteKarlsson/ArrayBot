#ifndef atNavitarMotorH
#define atNavitarMotorH
#include "atATObject.h"
#include "atNavitarExporter.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
namespace at
{
    class NavitarMotorController;

    struct MotorRegisters
    {
            int USER_TARGET;
            int USER_INCREMENT;
            int USER_CURRENT;
            int USER_LIMIT;
            int USER_STATUS;
            int SETUP_ACCEL;
            int SETUP_INITVELOCITY;
            int SETUP_MAXVELOCITY;
            int SETUP_REVBACKLASH;
            int SETUP_FWDBACKLASH;
            int SETUP_SENSORTYPE;
            int SETUP_CONFIG;
            int SETUP_LIMIT;
    };

    class AT_NAVITAR NavitarMotor : public ATObject
    {
    	public:
    								            NavitarMotor(NavitarMotorController& parent, int motorID);

            						            //!Drive motor to home
    		void					            home();

            						            //!Drive motor to the limit
    		void					            limit();

            									//!Set the motors current position
            int									setPosition(int pos);

            									//!Add to current position
            int									addToPosition(int pos);

            									//!Get the motors current position
            int									getPosition();

            									//!Get the motors current position
            int									getMaxPosition();

            									//!Get the motors label
            string								getLabel();

        protected:
    		NavitarMotorController& 	        mMotorController;

            									//!When calling registers, the motor ID indicates which motor to
                                                //!communicate with
            int						            mID;

            									//!The label holds a "name" for the motor, Zoom or Focus
            string								mLabel;


            //Registers
            MotorRegisters						mRegisters;
    };

}
#endif
