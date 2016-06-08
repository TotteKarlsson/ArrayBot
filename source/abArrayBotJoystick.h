#ifndef abArrayBotJoystickH
#define abArrayBotJoystickH
#include "abExporter.h"
#include "abABObject.h"
#include "abJoyStickAxis.h"
#include "abJoyStickButton.h"
#include "abJoyStickMessageDispatcher.h"
//---------------------------------------------------------------------------

/*!The joystick class is designed for the ArrayBot hardware. Joystick buttons and
axes are named to reflect the ArrayBot setup. The mechanism for reacting to
physical JoyStick events are mediated by the JoyStickMessageDispather classes.
*/

class AB_CORE ArrayBotJoyStick : public ABObject
{
    public:
							        ArrayBotJoyStick();
							        ~ArrayBotJoyStick();
		bool				        enable();
        bool				        disable();

        bool				        isEnabled();
    	JoyStickAxis&		        getX1Axis();
    	JoyStickAxis&		        getX2Axis();
    	JoyStickAxis&		        getY1Axis();
    	JoyStickAxis&		        getY2Axis();

		JoyStickButton&		        getButton(int nr);
		JoyStickButton&		        getPOVButton(int nr);
        void						setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);

    protected:
        bool				        mEnabled;

		JoyStickMessageDispatcher 	mJSMessageDispatcher;

        							//!Coverslip XY axes
    	JoyStickAxis		        mX1Axis;
    	JoyStickAxis		        mY1Axis;

									//!Whisker XY axes
    	JoyStickAxis		        mX2Axis;
    	JoyStickAxis		        mY2Axis;

        JoyStickButton		        mButton1;
        JoyStickButton		        mButton2;
        JoyStickButton		        mButton3;
        JoyStickButton		        mButton4;

        JoyStickButton		        mButton5;
        JoyStickButton		        mButton6;

        JoyStickButton		        mPOVButton1;
        JoyStickButton		        mPOVButton2;
        JoyStickButton		        mPOVButton3;
        JoyStickButton		        mPOVButton4;

        JoyStickButton		        mButton9;
        JoyStickButton		        mButton10;
};

#endif
