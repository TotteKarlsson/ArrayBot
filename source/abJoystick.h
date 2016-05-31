#ifndef abJoystickH
#define abJoystickH

#include "abExporter.h"
#include "abABObject.h"
#include "abJoyStickAxis.h"
#include "abJoyStickButton.h"
//#include <mmsystem.h>
//---------------------------------------------------------------------------

//struct JOYCAPS;
///The joystick class encapsulate needed functionality in the ArrayBot API
class AB_CORE JoyStick : public ABObject
{

    public:
							        JoyStick(int Handle = 0);
							        ~JoyStick();
		bool				        connect();
		bool				        enable();
        bool				        disable();

        bool				        isEnabled();
    	JoyStickAxis&		        getXAxis();
    	JoyStickAxis&		        getYAxis();
    	JoyStickAxis&		        getZAxis();
		JoyStickButton&		        getButton(int nr);

        bool						setMessageRate(int rate);
        int 						getMessageRate();
		void						setWindowHandle(int handle);

    protected:
    						        //To get joystick messages, we need a handle
                                    //to the window
	    int  				        mHandle;
        int 				        mJoystickID;

        							//Approximate in ms
        int							mMessageRate;
        bool				        mEnabled;
        bool 				        mJoyStickConnected;
        int 				        mJoyStickDriverCount;

    	JoyStickAxis		        mXAxis;
    	JoyStickAxis		        mYAxis;
    	JoyStickAxis		        mZAxis;

        JoyStickButton		        mButton1;
        JoyStickButton		        mButton2;
        JoyStickButton		        mButton3;
        JoyStickButton		        mButton4;

        JoyStickButton		        mButton5;
        JoyStickButton		        mButton6;
        JoyStickButton		        mButton7;
        JoyStickButton		        mButton8;

        JoyStickButton		        mButton9;
        JoyStickButton		        mButton10;

};

#endif
