#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>

#define __AFXWIN_H__

#include "uc480Class.h"

Cuc480   mCamera;
SENSORINFO m_sInfo;     // sensor info struct
INT		m_nSizeX;		// width of video
	INT		m_nSizeY;		// height of video

void   openCamera();
int _tmain(int argc, _TCHAR* argv[])
{

	openCamera();
	return 0;
}

void openCamera()
{
    bool m_Ret = mCamera.InitCamera(0, NULL );        // init cam

    // continue when camera is sucessfully initialized
    if( m_Ret == IS_SUCCESS )
    {
        // retrieve original image size
        mCamera.GetSensorInfo(&m_sInfo );
        mCamera.GetMaxImageSize(&m_nSizeX, &m_nSizeY);

//        UpdateData(TRUE);
        m_Ret = InitDisplayMode();
//
//        // enable the dialog based error report
//        //m_Ret = mCamera.SetErrorReport(IS_DISABLE_ERR_REP);
//        if( m_Ret != IS_SUCCESS )
//        {
//            AfxMessageBox( "ERROR: Can not enable the automatic error report!" , MB_ICONEXCLAMATION, 0 );
//            return false;
//        }
//
//        // Enable Messages
//        mCamera.EnableMessage(IS_DEVICE_REMOVED ,GetSafeHwnd());
//        mCamera.EnableMessage(IS_DEVICE_RECONNECTED , GetSafeHwnd());
//        mCamera.EnableMessage(IS_FRAME , GetSafeHwnd());
//
//        // start live video
        mCamera.CaptureVideo(IS_WAIT);
//
//        GetDlgItem(IDC_DISP_DIB)->EnableWindow(FALSE);
//        GetDlgItem(IDC_DISP_DD)->EnableWindow(FALSE);
//
//        // do the whitebalance once on the first acquisitioned image only on color cameras
        if( m_sInfo.nColorMode == IS_COLORMODE_BAYER )
            mCamera.SetWhiteBalance(IS_SET_WB_AUTO_ENABLE);
//
//        return true;
//    }
//    else
//    {
//        AfxMessageBox("No camera could be opened !", MB_ICONWARNING );
//    }

}
