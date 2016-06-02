#ifndef abJoyStickMessageDispatcherH
#define abJoyStickMessageDispatcherH
#include <dinput.h>
#include <windows.h>
#include <mmsystem.h>
#include "mtkTimer.h"
#include <utility>
#include <deque>
using mtk::Timer;
using std::pair;
using std::deque;


typedef void (__closure *JoyStickEvent)(); //Need to research this and make it portable
typedef void (__closure *JoyStickAxisEvent)(int pos); //Need to research this and make it portable
typedef pair<JoyStickEvent, JoyStickEvent> ButtonEvents;

enum ButtonState {bsUp = 0, bsDown};

//Helper classes
class Button
{
	public:
				    	Button() : mButtonState(bsUp){};
		ButtonState 	mButtonState;
    	ButtonEvents 	mEvents;
};


class JoyStickAxis
{
	public:
				    		JoyStickAxis() : mPosition(0){};
		int					mPosition;
    	JoyStickAxisEvent 	mEvent;
};

class JoyStickMessageDispatcher
{
	public:
                                JoyStickMessageDispatcher();
					            ~JoyStickMessageDispatcher(){}
			void				setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);
			void				setAxisEvent(int axis, JoyStickAxisEvent move);

								//Remove these strucs later on
            JOYINFOEX 			mJoyInfo;
            JOYCAPS 			mCapabilities;

            void 				refresh();
            bool				isEnabled();
            bool				enable();
            void				disable();

	private:
            int 				mJoyStickID;
            int					mMoveResolution;
            const int			mNrOfButtons;
            void 				readCapabilities();

			deque<Button>		mButtons;
            JoyStickAxis		mX1Axis;
            JoyStickAxis		mY1Axis;

            JoyStickAxis		mX2Axis;
            JoyStickAxis		mY2Axis;

            Timer				mUpdateStateTimer;
};


#endif
