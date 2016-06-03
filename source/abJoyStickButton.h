#ifndef abJoyStickButtonH
#define abJoyStickButtonH
#include "abExporter.h"
#include "abABObject.h"
//---------------------------------------------------------------------------

class APTMotor;
///The joystick button class encapsulate functionality in the ArrayBot API for
///what happens when a JS button is pressed.
///A joystick button have an associated motor to control, where
///a pressed button basically means 'go'. and a depressed button stops the motor.
class AB_CORE JoyStickButton : public ABObject
{
    public:
							JoyStickButton();
							~JoyStickButton();
		void 				assignMotor(APTMotor* motor);

		void				enable();
   		void				disable();
        void				setForward();
        void				setReverse();

                            //These functions are called by the UI
                            //as joystick messages are flowing in
		void 				down();
		void 				up();

    protected:
		APTMotor*			mMotor;
        bool				mIsEnabled;
        bool				mIsForward;
};

#endif


