#ifndef atJoyStickPOVStateEventDispatcherH
#define atJoyStickPOVStateEventDispatcherH
#include "atATObject.h"
#include "atEnums.h"
#include <utility>
#include "arraybot/atABExporter.h"
//---------------------------------------------------------------------------

using std::pair;

namespace at
{
    typedef void (__closure *JoyStickEvent)(); //Need to research this and make it portable
    typedef pair<JoyStickEvent, JoyStickEvent> ButtonEvents;

    /*! The JoyStickPOVStateEventDispatcher class translate the
    state of the POV into four "simulated" buttons. If the POV is set
    to a 'in between' state, all button states are assumed to be 'up'
    */
    class AT_AB JoyStickPOVStateEventDispatcher  : public ATObject
    {
    	public:
    				    			JoyStickPOVStateEventDispatcher();

                                    //!The buttons state is checked against a
                                    //!status value that is retrieved in a polling loop. If
                                    //!the values are different, the state is updated
                                    //!and the associated Event is fired
                                    //!The POV state is a number between 0 - 65000
                                    //!There are 9 possible numbers
    		unsigned int  			mPOVState;

        	ButtonEvents 			mLeftButtonEvents;
        	ButtonEvents 			mRightButtonEvents;
        	ButtonEvents 			mUpButtonEvents;
        	ButtonEvents 			mDownButtonEvents;

    };

}

#endif
