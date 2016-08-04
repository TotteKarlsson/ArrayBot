#ifndef abJoyStickAxisStateEventDispatcherH
#define abJoyStickAxisStateEventDispatcherH
#include "abABObject.h"
//---------------------------------------------------------------------------

typedef void (__closure *JoyStickAxisEvent)(int pos);

class JoyStickAxisStateEventDispatcher  : public ABObject
{
	public:
				    		JoyStickAxisStateEventDispatcher() : mPosition(0){};
		int					mPosition;
    	JoyStickAxisEvent 	mEvent;
};


#endif
