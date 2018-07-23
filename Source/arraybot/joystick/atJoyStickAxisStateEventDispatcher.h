#ifndef atJoyStickAxisStateEventDispatcherH
#define atJoyStickAxisStateEventDispatcherH
#include "atATObject.h"
//---------------------------------------------------------------------------

namespace at
{
    typedef void (__closure *JoyStickAxisEvent)(int pos);

    class JoyStickAxisStateEventDispatcher  : public ATObject
    {
    	public:
    				    		JoyStickAxisStateEventDispatcher() : mPosition(0){};
    		int					mPosition;
        	JoyStickAxisEvent 	mEvent;
    };

}

#endif
