#ifndef abJoyStickMessageDispatcherH
#define abJoyStickMessageDispatcherH
#include "abJoyStickButtonStateEventDispatcher.h"
#include "abJoyStickAxisStateEventDispatcher.h"
#include "abJoyStickPOVStateEventDispatcher.h"

#include <windows.h>
#include <mmsystem.h>
#include "mtkTimer.h"
#include <utility>
#include <deque>

using mtk::Timer;
using std::deque;
typedef deque<JoyStickButtonStateEventDispatcher> ButtonDeque;
typedef JoyStickAxisStateEventDispatcher JSAxis;
typedef JoyStickPOVStateEventDispatcher JSPOV; //!Point of view dispatcher


/*!The JoyStickMessageDispatcher is tailor made for the ArrayBot. The dispatcher
uses the right side of a PS3 joystick for the right side of the ArrayBot, and
the left side designated for the left side of the ArrayBot. The POV buttons are
used for x-y motions for the left (whisker) side of the Arraybot.
*/
class AB_CORE JoyStickMessageDispatcher : public ABObject
{
	public:
                                        JoyStickMessageDispatcher(int nrOfButtons);
					                    ~JoyStickMessageDispatcher();
			void				        setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
			void				        setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
			void				        setAxisEvent(int axis, JoyStickAxisEvent move);

								        //Remove these strucs later on
            JOYINFOEX 			        mJoyInfo;
            JOYCAPS 			        mCapabilities;
            void 				        refresh();
            bool				        isEnabled();
            bool				        enable();
            void				        disable();

	private:
            int 				        mJoyStickID;
            bool				        mEnabled;

            							//!If no joystick is found
                                        //!mCanEnable is false
            bool						mCanEnable;
            int					        mMoveResolution;
            const int			        mNrOfButtons;
            bool 				        readCapabilities();

			ButtonDeque 		        mButtons;

            JSAxis		        		mX1Axis;
            JSAxis		        		mY1Axis;
            JSAxis		        		mX2Axis;
            JSAxis		        		mY2Axis;
            JSPOV						mPOV;

            Timer				        mUpdateStateTimer;
};
#endif
