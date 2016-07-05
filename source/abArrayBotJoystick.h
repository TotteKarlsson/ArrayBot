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
typedef void (__closure *JoyStickEvent)();

class AB_CORE ArrayBotJoyStick : public ABObject
{
	friend JoyStickMessageDispatcher;
    public:
							        ArrayBotJoyStick();
							        ~ArrayBotJoyStick();

		bool				        enable();
        bool				        disable();

        bool						disableCoverSlipAxes();
        bool						enableCoverSlipAxes();

        bool						disableWhiskerAxes();
        bool						enableWhiskerAxes();

        bool				        isEnabled();
    	JoyStickAxis&		        getX1Axis();
    	JoyStickAxis&		        getX2Axis();
    	JoyStickAxis&		        getY1Axis();
    	JoyStickAxis&		        getY2Axis();
        bool						setAxesMaxVelocity(double maxV);

        unsigned long				getX1Pos();
        unsigned long				getY1Pos();
        unsigned long				getZ1Pos();

        unsigned long				getX2Pos();
        unsigned long				getY2Pos();
        unsigned long				getZ2Pos();

        unsigned long				getButtonBits();
        unsigned long				getPOVBits();

		JoyStickButton&		        getButton(int nr);
		JoyStickButton&		        getPOVButton(int nr);
        void						setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
        void						setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
        void				        setAxisEvent(int axis, JoyStickAxisEvent move);
        void						switchJoyStickDevice();

    protected:
        bool				        mEnabled;
 		bool						mCoverSlipAxesEnabled;
 		bool						mWhiskerAxesEnabled;

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
