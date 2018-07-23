#ifndef atArrayBotJoystickH
#define atArrayBotJoystickH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atJoyStickAxis.h"
#include "atJoyStickButton.h"
#include "atJoyStickMessageDispatcher.h"
//---------------------------------------------------------------------------

/*!The joystick class is designed for the ArrayBot hardware. Joystick buttons and
axes are named to reflect the ArrayBot setup. The mechanism for reacting to
physical JoyStick events are mediated by the JoyStickMessageDispatcher classes.
*/
typedef void (__closure *JoyStickEvent)();

namespace at
{
    class AT_AB ArrayBotJoyStick : public ATObject
    {
    	friend JoyStickMessageDispatcher;
        public:
    							                        ArrayBotJoyStick(int& id);
    							                        ~ArrayBotJoyStick();

    		bool				                        enable();
    		bool										enableJoyStickWithID(int id);
            bool				                        disable();

            bool						                enableCoverSlipAxes();
            bool						                enableWhiskerAxes();
            bool						                disableCoverSlipAxes();
            bool						                disableWhiskerAxes();

            bool						                enableCoverSlipZButtons();
            bool						                enableWhiskerZButtons();
            bool						                disableCoverSlipZButtons();
            bool						                disableWhiskerZButtons();

            bool				                        isEnabled();


        	JoyStickAxis&		                        getX1Axis();
        	JoyStickAxis&		                        getY1Axis();

        	JoyStickAxis&		                        getX2Axis();
        	JoyStickAxis&		                        getY2Axis();
            bool						                setAxesMaxVelocity(double maxV);

            unsigned long				                getX1Pos();
            unsigned long				                getY1Pos();
            unsigned long				                getZ1Pos();

            unsigned long				                getX2Pos();
            unsigned long				                getY2Pos();
            unsigned long				                getZ2Pos();

            unsigned long				                getButtonBits();
            unsigned long				                getPOVBits();

    		JoyStickButton&		                        getButton(int nr);
    		JoyStickButton&		                        getPOVButton(int nr);
            void						                setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent jse, bool clickOnly = true);
            void						                setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent jse);
            void				                        setAxisEvent(int axis, JoyStickAxisEvent move);

            bool										isValid();
            int											getID(){return mJoyStickID;}

        protected:
            bool				                        mEnabled;
     		bool						                mCoverSlipAxesEnabled;
     		bool						                mWhiskerAxesEnabled;

     		bool						                mCoverSlipZButtonsEnabled;
     		bool						                mWhiskerZButtonsEnabled;

                        								//!The JoyStick ID is referenced
                                                        //from ArrayBot
            int&	   									mJoyStickID;

    		JoyStickMessageDispatcher 	                mJSMessageDispatcher;

            							                //!Coverslip XY axes
        	JoyStickAxis		                        mX1Axis;
        	JoyStickAxis		                        mY1Axis;

    									                //!Whisker XY axes
        	JoyStickAxis		                        mX2Axis;
        	JoyStickAxis		                        mY2Axis;

            JoyStickButton		                        mButton1;
            JoyStickButton		                        mButton2;
            JoyStickButton		                        mButton3;
            JoyStickButton		                        mButton4;

            JoyStickButton		                        mButton5;
            JoyStickButton		                        mButton6;

            JoyStickButton		                        mButton7;
            JoyStickButton		                        mButton8;

            JoyStickButton		                        mPOVButton1;
            JoyStickButton		                        mPOVButton2;
            JoyStickButton		                        mPOVButton3;
            JoyStickButton		                        mPOVButton4;

            JoyStickButton		                        mButton9;
            JoyStickButton		                        mButton10;

    													//These are not used..
            JoyStickButton		                        mButton11;
            JoyStickButton		                        mButton12;
            JoyStickButton		                        mButton13;
            JoyStickButton		                        mButton14;
    };

}
#endif
