#ifndef abJoyStickButtonH
#define abJoyStickButtonH
#include "abExporter.h"
#include "abABObject.h"
//#include <Winapi.Messages.hpp>
//---------------------------------------------------------------------------

class APTMotor;
///The joystick Axis class encapsulate needed functionality in the ArrayBot API
///In short, a joystick axis have an associated motor to control, as well as a
///function that is called from the UI controlling the motor
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


