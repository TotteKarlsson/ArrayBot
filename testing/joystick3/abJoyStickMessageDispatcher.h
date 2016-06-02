#ifndef abJoyStickMessageDispatcherH
#define abJoyStickMessageDispatcherH
#include <windows.h>
#include <mmsystem.h>
#include "mtkTimer.h"
#include <utility>
#include <deque>
#include "abJoyStickButtonStateEventDispatcher.h"
#include "abJoyStickAxisStateEventDispatcher.h"
using mtk::Timer;
using std::deque;
typedef   deque<JoyStickButtonStateEventDispatcher> ButtonDeque;

class JoyStickMessageDispatcher
{
	public:
                                        JoyStickMessageDispatcher(int nrOfButtons);
					                    ~JoyStickMessageDispatcher(){}
			void				        setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
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
            int					        mMoveResolution;
            const int			        mNrOfButtons;
            void 				        readCapabilities();

			ButtonDeque 		        mButtons;

            JoyStickAxis		        mX1Axis;
            JoyStickAxis		        mY1Axis;

            JoyStickAxis		        mX2Axis;
            JoyStickAxis		        mY2Axis;

            Timer				        mUpdateStateTimer;
};


#endif
