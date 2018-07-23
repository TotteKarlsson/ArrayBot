#ifndef atJoyStickMessageDispatcherH
#define atJoyStickMessageDispatcherH
#include "atJoyStickButtonStateEventDispatcher.h"
#include "atJoyStickAxisStateEventDispatcher.h"
#include "atJoyStickPOVStateEventDispatcher.h"
#include <windows.h>
#include <mmsystem.h>
#include "dslTimer.h"
#include <utility>
#include <deque>

using dsl::Timer;
using std::deque;

namespace at
{
    typedef deque<JoyStickButtonStateEventDispatcher> 	ButtonStateDeque;
    typedef JoyStickAxisStateEventDispatcher 			JSAxis;
    typedef JoyStickPOVStateEventDispatcher 			JSPOV; //!Point of view dispatcher

    class ArrayBotJoyStick;

    /*!The JoyStickMessageDispatcher is tailor made for the ArrayBot. The dispatcher
    uses the right side of a PS3 joystick for the right side of the ArrayBot, and
    the left side designated for the left side of the ArrayBot. The POV buttons are
    used for x-y motions for the left (whisker) side of the Arraybot.
    */
    class AT_AB JoyStickMessageDispatcher : public ATObject
    {
    	public:
                                                    JoyStickMessageDispatcher(ArrayBotJoyStick& js, int nrOfButtons, int& ID);
                                                    ~JoyStickMessageDispatcher();

            void				                    setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down, bool clickOnly = true);
            void				                    setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
            void				                    setAxisEvent(int axis, JoyStickAxisEvent move);

            void 				                    refresh();
            bool				                    isEnabled();
            bool				                    enable(int id);
            void				                    disable();

            unsigned long						    getX1Pos();
            unsigned long						    getY1Pos();
            unsigned long						    getZ1Pos();
            unsigned long						    getX2Pos();
            unsigned long						    getY2Pos();
            unsigned long						    getZ2Pos();

            unsigned long						    getButtonBits();
            unsigned long						    getPOVBits();
            bool									isValid();

    	private:
        											//!The dispatcher is part of the ArrayBotJoystick
                int& 				                mJoyStickID;
    		    ArrayBotJoyStick&			        mJoyStick;
                bool				                mEnabled;

                const int			                mNrOfButtons;
                bool 				                readCapabilities();
    			bool								checkCapabilities(int ID);
    			ButtonStateDeque   	                mButtonStates;

                							        //!Joystick axes X1,Y1 to the left and X2,Y2 to the right.
                JSAxis		        		        mX1Axis;
                JSAxis		        		        mY1Axis;

                JSAxis		        		        mX2Axis;
                JSAxis		        		        mY2Axis;

                									//!The point of view (POV) buttons acts as z and camera angle controller
                                                    //!for the coverslip unit.
                JSPOV						        mPOV;

                									//The  updatedstate timer generates joystick events
                Timer				                mUpdateStateTimer;

                									//!Stuctures communicating hardware information
                                                    //!regarding the joystick
                JOYINFOEX 			                mJoyInfo;
                JOYCAPS 			                mCapabilities;
    };
}
#endif
