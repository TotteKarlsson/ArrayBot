#ifndef abJoystickH
#define abJoystickH

#include "abExporter.h"
#include "abABObject.h"
#include "abJoyStickAxis.h"
#include "abJoyStickButton.h"
//---------------------------------------------------------------------------

///The joystick class encapsulate needed functionality in the ArrayBot API
class AB_CORE JoyStick : public ABObject
{

    public:
							        JoyStick();
							        ~JoyStick();

		bool				        enable();
        bool				        disable();

        bool				        isEnabled();
    	JoyStickAxis&		        getX1Axis();
    	JoyStickAxis&		        getX2Axis();
    	JoyStickAxis&		        getY1Axis();
    	JoyStickAxis&		        getY2Axis();

		JoyStickButton&		        getButton(int nr);
		JoyStickButton&		        getPOVButton(int nr);

    protected:

        							//Approximate in ms
        bool				        mEnabled;

    	JoyStickAxis		        mX1Axis;
    	JoyStickAxis		        mX2Axis;
    	JoyStickAxis		        mY1Axis;
    	JoyStickAxis		        mY2Axis;


        JoyStickButton		        mButton1;
        JoyStickButton		        mButton2;
        JoyStickButton		        mButton3;
        JoyStickButton		        mButton4;

        JoyStickButton		        mPOVButton1;
        JoyStickButton		        mPOVButton2;
        JoyStickButton		        mPOVButton3;
        JoyStickButton		        mPOVButton4;

        JoyStickButton		        mButton9;
        JoyStickButton		        mButton10;
};

#endif
