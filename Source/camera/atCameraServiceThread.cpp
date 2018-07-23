#pragma hdrstop
#include "atCameraServiceThread.h"
#include "dslWin32Utils.h"
#include "uc480class.h"
#include "dslLogger.h"

using namespace dsl;


CameraServiceThread::CameraServiceThread(Cuc480& camera, int id, HWND handle)
:
mCamera(camera),
mCameraID(id),
mWindowHandle(handle),
mDoFunction(dfOpen)
{}

void CameraServiceThread::run()
{
	mIsRunning = true;

    if(mDoFunction == dfOpen)
    {
        if(mCamera.openCamera(mWindowHandle, mCameraID))
        {
            Log(lInfo) << "Camera with ID: "<<mCameraID<<" was opened";
        }
        else
        {
            Log(lError) << "Camera with ID: "<<mCameraID<<" was NOT opened";
        }

        if(onCameraOpen)
        {
            //Need to call synchronize
            onCameraOpen((System::TObject*) &(this->mCamera));
        }
    }
    else if(mDoFunction == dfClose)
    {
    	if(mCamera.exitCamera())
        {
            Log(lInfo) << "Camera with ID: "<<mCameraID<<" was closed";
        }
        else
        {
            Log(lError) << "Camera with ID: "<<mCameraID<<" was NOT closed properly";
        }

        if(onCameraClose)
        {
            //Need to call synchronize
            onCameraClose((System::TObject*) &(this->mCamera));
        }
    }

    mIsFinished = true;
    mIsRunning = false;
}

void CameraServiceThread::openCamera()
{
	mDoFunction = dfOpen;
    start(true);
}

void CameraServiceThread::closeCamera()
{
	mDoFunction = dfClose;
    start(true);
}

