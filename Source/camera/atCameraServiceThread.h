#ifndef atCameraServiceThreadH
#define atCameraServiceThreadH
#include "dslThread.h"
#include "atATObject.h"
#include "atCameraExporter.h"
class Cuc480;
using dsl::Thread;

namespace System
{
	class TObject;
}
typedef void __fastcall (__closure *ThreadCallBack)(System::TObject*);


//The thread can only execute one function at one time..
enum DoFunction {dfOpen, dfClose};

//!The camera service thread performs camera specific functions that need to be
//!performed in a thread, as suggested by the UC480 API document
//---------------------------------------------------------------------------
class AT_CAMERA CameraServiceThread : public Thread, public at::ATObject
{
	public:
								CameraServiceThread(Cuc480& camera, int id, HWND handle);

		ThreadCallBack			onCameraOpen;
		ThreadCallBack			onCameraClose;

        void					openCamera();
        void					closeCamera();
        void					run();

    private:
    	Cuc480&					mCamera;
        int						mCameraID;
        HWND					mWindowHandle;

        						//!Before executing run, set what the thread should do
        DoFunction				mDoFunction;
};

#endif
