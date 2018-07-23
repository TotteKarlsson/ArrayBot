#ifndef atJoyStickButtonStateEventDispatcherH
#define atJoyStickButtonStateEventDispatcherH
#include "atATObject.h"
#include "atEnums.h"
#include <utility>
#include "atJoyStickButton.h"
#include "arraybot/atABExporter.h"
using std::pair;

//---------------------------------------------------------------------------
typedef void (__closure *JoyStickEvent)();
typedef pair<JoyStickEvent, JoyStickEvent> ButtonEvents;
namespace at
{
    class JoyStickButton;

    //Helper class
    class AT_AB JoyStickButtonStateEventDispatcher  : public ATObject
    {
    	public:
    				    			JoyStickButtonStateEventDispatcher(JoyStickButton& btn);

                                    //!The buttons state is checked against
                                    //!status value retrieved in a polling loop. If
                                    //!the value changed, the state is updated
                                    //!and the associated Event is fired
    		void					setButtonState(JoyStickButtonState s);
            JoyStickButtonState		getButtonState();

    //		JoyStickButtonState 	mButtonState;
        	ButtonEvents 			mEvents;

            						//!Stting clickEventOnly means that the state
                                    //is only checked for a state change, i.e. going from
                                    //pressed to 'unpressed'.
                                    //If Click eventOnly is false, state is checked continously
                                    //in the event loop
            bool					mClickEventOnly;

            JoyStickButton&			mButton;
    };

}

#endif
