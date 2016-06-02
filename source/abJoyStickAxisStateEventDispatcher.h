#ifndef abJoyStickAxisStateEventDispatcherH
#define abJoyStickAxisStateEventDispatcherH
//---------------------------------------------------------------------------

typedef void (__closure *JoyStickAxisEvent)(int pos); //Need to research this and make it portable
class JoyStickAxis
{
	public:
				    		JoyStickAxis() : mPosition(0){};
		int					mPosition;
    	JoyStickAxisEvent 	mEvent;
};


#endif
