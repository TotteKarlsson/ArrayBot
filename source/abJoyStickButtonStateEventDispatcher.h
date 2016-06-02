#ifndef abJoyStickButtonStateEventDispatcherH
#define abJoyStickButtonStateEventDispatcherH
#include <utility>

using std::pair;
//---------------------------------------------------------------------------
enum ButtonState {bsUp = 0, bsDown};
typedef void (__closure *JoyStickEvent)(); //Need to research this and make it portable
typedef pair<JoyStickEvent, JoyStickEvent> ButtonEvents;

//Helper classes
class JoyStickButtonStateEventDispatcher
{
	public:
				    	JoyStickButtonStateEventDispatcher() : mButtonState(bsUp){};

                        //!The buttons state is checked against
                        //!status value retrieved in a polling loop. If
                        //!the value changed, the state is updated
                        //!and the associated Event is fired
		ButtonState 	mButtonState;
    	ButtonEvents 	mEvents;
};


#endif
