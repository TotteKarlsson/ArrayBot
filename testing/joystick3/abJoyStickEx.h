#ifndef abJoyStickExH
#define abJoyStickExH
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
typedef pair<JoyStickEvent, JoyStickEvent> ButtonEvents;

enum ButtonState {bsUp = 0, bsDown};

//Helper class
class Button
{
	public:
				    	Button() : mButtonState(bsUp){};
		ButtonState 	mButtonState;
    	ButtonEvents 	mEvents;
};

class JoyStickEx
{
	public:
                                JoyStickEx();
					            ~JoyStickEx(){}
			void				setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down);

            JOYINFOEX 			mJoyInfo;
            JOYCAPS 			mCapabilities;
            void 				refresh();

            bool				isEnabled();
            bool				enable();
            void				disable();

	private:
            int 				mJoyStickID;
            const int			mNrOfButtons;
            void 				readCapabilities();


			deque<Button>		mButtons;


            Timer				mUpdateStateTimer;
};





#endif
