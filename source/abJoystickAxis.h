#ifndef abJoystickAxisH
#define abJoystickAxisH
#include "CoreExporter.h"
#include "abABObject.h"
#include <Winapi.Messages.hpp>
//---------------------------------------------------------------------------

class APTMotor;
///The joystick Axis class encapsulate needed functionality in the ArrayBot API
///In short, a joystick axis have an associated motor to control, as well as a
///function that is called from the UI controlling the motor
class AB_CORE JoyStickAxis : public ABObject
{

    public:
							JoyStickAxis();
							~JoyStickAxis();
		void				enable();
   		void				disable();

        void				assignMotor(APTMotor* motor);
		void				setNumberOfGears(int g);
		int  				getNumberOfGears();
        void				setMaxVelocity(double vel);
		double				getMaxVelocity();
                            //This function is called by the UI
                            //as joystick messages are flowing in
		void 				Move(double newPosition);


    protected:
        bool				mIsEnabled;
        bool				mZeroInMiddle;
		APTMotor*			mMotor;
		int					mMaxPosition;
        int					mNumberOfGears;
        double 				mMaxVelocity;


        double 				mRunningZAverage;
        double 				mValCommand;
        double 				mAlpha;

};

#endif
