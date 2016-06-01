#ifndef abJoyStickExH
#define abJoyStickExH
#include <dinput.h>
#include <windows.h>
#include <mmsystem.h>


const int gMaxNrOfJoySticks = 16;

typedef void (__closure *JoyStickEvent)(); //Need to research this and make it portable

class JoyStickEx
{
	public:
                                JoyStickEx();
					            ~JoyStickEx(){}


            JOYINFOEX 			mJoyInfo;
            JOYCAPS 			mCapabilities;
            void 				refresh();


            JoyStickEvent		OnButton1Down;
            JoyStickEvent		OnButton1Up;


	private:
            int 				mJoyStickID;
            void 				readCapabilities();
};





#endif
