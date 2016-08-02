#include <vcl.h>
#pragma hdrstop
#include "MainFrame.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "mtkWin32Utils.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

extern string gLogFileName;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
    	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg)
{
   	mLogFileReader.start(true);
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	Log(lDebug) << "Init camera..";

	//Live
	if( !m_camera.IsInit() )
        openCamera();

    if( m_camera.IsInit() )
    {
        m_camera.CaptureVideo( IS_WAIT );

//        GetDlgItem(IDC_DISP_DIB)->EnableWindow(FALSE);
//        GetDlgItem(IDC_DISP_DD)->EnableWindow(FALSE);
//	Timer1->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
//	TMemoLogger::mMemoIsEnabled = false;

	m_hDisplay = this->Panel1->Handle;//( IDC_DISPLAY )->m_hWnd; // get handle to display window

    m_pcImageMemory  = NULL;
    m_lMemoryId = 0;
    m_nDispModeSel = e_disp_mode_bitmap;

//	openCamera();
}

LRESULT TMainForm::OnUSBCameraMessage( WPARAM wParam)//, LPARAM lParam )
{
    switch ( wParam )
    {
        case IS_DEVICE_REMOVED:
            Beep( 400, 50 );
            break;

        case IS_DEVICE_RECONNECTED:
            Beep( 400, 50 );
            break;

        case IS_FRAME:
            if(m_pcImageMemory != NULL)
                m_camera.RenderBitmap(m_lMemoryId, m_hDisplay, IS_RENDER_FIT_TO_WINDOW);
            break;

		case 1280:
            if(m_pcImageMemory != NULL)
            {
                m_camera.RenderBitmap(m_lMemoryId, m_hDisplay, IS_RENDER_FIT_TO_WINDOW);
            }
            else
            {
            	Log(lError) << "No Image memory";
            }
            break;

    }

//	Log(lDebug) << "Got message: "<<wParam;
    return 0;
}

//---------------------------------------------------------------------------
bool TMainForm::openCamera()
{
    exitCamera();

    // init camera
    m_Ret = m_camera.InitCamera(0, m_hDisplay );        // init cam

    // continue when camera is sucessfully initialized
    if( m_Ret == IS_SUCCESS )
    {
        // retrieve original image size
        m_camera.GetSensorInfo(&m_sInfo );

        m_camera.GetMaxImageSize(&m_nSizeX, &m_nSizeY);

//        UpdateData(TRUE);

        m_Ret = InitDisplayMode();

        // enable the dialog based error report
        //m_Ret = m_camera.SetErrorReport(IS_DISABLE_ERR_REP);
        if( m_Ret != IS_SUCCESS )
        {
//            MessageBox( "ERROR: Can not enable the automatic error report!" , MB_ICONEXCLAMATION, 0 );
            return false;
        }

        // Enable Messages
        m_camera.EnableMessage(IS_DEVICE_REMOVED ,GetSafeHwnd());
        m_camera.EnableMessage(IS_DEVICE_RECONNECTED , GetSafeHwnd());
        m_camera.EnableMessage(IS_FRAME , GetSafeHwnd());

        // start live video
        m_camera.CaptureVideo(IS_WAIT);

        // do the whitebalance once on the first acquisitioned image only on color cameras
        if( m_sInfo.nColorMode == IS_COLORMODE_BAYER )
        {
            m_camera.SetWhiteBalance(IS_SET_WB_AUTO_ENABLE);
        }

        return true;
    }
    else
    {
        MessageDlg("No Camera could be opened", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return false;
    }
}

void TMainForm::exitCamera()
{
    if( m_camera.IsInit() )
    {
        m_camera.EnableMessage( IS_FRAME, NULL );
        m_camera.StopLiveVideo( IS_WAIT );

        if( m_pcImageMemory != NULL )
            m_camera.FreeImageMem( m_pcImageMemory, m_lMemoryId );

        m_pcImageMemory = NULL;
        m_camera.ExitCamera();
    }
}

int TMainForm::InitDisplayMode()
{
    if (!m_camera.IsInit())
    {
        return IS_NO_SUCCESS;
    }

    if (m_pcImageMemory != NULL)
    {
        m_camera.FreeImageMem(m_pcImageMemory, m_lMemoryId);
    }

    m_pcImageMemory = NULL;

    switch (m_nDispModeSel)
    {
        case e_disp_mode_direct3D:
            // if initializiing the direct draw mode succeeded then
            // leave the switch tree else run through to bitmap mode
            m_Ret = m_camera.SetDisplayMode(IS_SET_DM_DIRECT3D);
            m_Ret = m_camera.DirectRenderer(DR_ENABLE_SCALING, NULL, NULL);

            if(m_Ret == IS_SUCCESS )
            {
                // setup the color depth to the current VGA setting
                m_camera.GetColorDepth( &m_nBitsPerPixel, &m_nColorMode );
                break;
            }
            else
            {
                m_nDispModeSel = e_disp_mode_bitmap;
                //UpdateData(FALSE);
            }

        case e_disp_mode_bitmap:
            m_Ret = m_camera.SetDisplayMode(IS_SET_DM_DIB);
            if ((m_sInfo.nColorMode == IS_COLORMODE_BAYER) ||
                (m_sInfo.nColorMode == IS_COLORMODE_CBYCRY))
            {
                // for color camera models use RGB24 mode
                m_nColorMode = IS_SET_CM_RGB24;
                m_nBitsPerPixel = 24;
            }
            else
            {
                // for monochrome camera models use Y8 mode
                m_nColorMode = IS_SET_CM_Y8;
                m_nBitsPerPixel = 8;
            }
            // allocate an image memory.
            if (m_camera.AllocImageMem( m_nSizeX,
                                        m_nSizeY,
                                        m_nBitsPerPixel,
                                        &m_pcImageMemory,
                                        &m_lMemoryId ) != IS_SUCCESS )
            {
//                AfxMessageBox("Memory allocation failed!", MB_ICONWARNING );
            }
            else
                m_camera.SetImageMem( m_pcImageMemory, m_lMemoryId );
            break;
    }

    if(m_Ret == IS_SUCCESS )
    {
        // set the desired color mode
        m_camera.SetColorMode( m_nColorMode );

        // set the image size to capture
        m_camera.SetImageSize( m_nSizeX, m_nSizeY );

    }

    return m_Ret;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
	    exitCamera();
    	Close();
    }
}

HWND TMainForm::GetSafeHwnd()
{
	return this->Handle;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    if(m_pcImageMemory != NULL)
    {
        m_camera.RenderBitmap(m_lMemoryId, m_hDisplay, IS_RENDER_FIT_TO_WINDOW);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(mLogFileReader.isRunning() || m_camera.IsInit())
    {
        CanClose = false;
        mShutDownTimer->Enabled = true;
        return;
    }

    CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShutDownTimerTimer(TObject *Sender)
{
    mShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
    {
		mLogFileReader.stop();
    }

    if( m_camera.IsInit())
    {
    	exitCamera();
    }

    Close();
}


void __fastcall TMainForm::TrackBar1Change(TObject *Sender)
{
	//Set brightness
/* set gamma value to 1.6 */
	INT nGamma = TrackBar1->Position;
    HCAM hCam = m_camera.GetCameraHandle();
	INT nRet = is_Gamma(hCam, IS_GAMMA_CMD_SET, (void*) &nGamma, sizeof(nGamma));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
	double fps(0);
	is_GetFramesPerSecond(m_camera.GetCameraHandle(), &fps);

    Log(lInfo) << "Frames per second: " << fps;
}


void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
    HCAM hCam = m_camera.GetCameraHandle();
    //Enable auto gain control:
    double dEnable = CheckBox1->Checked ? 1 : 0;
    int ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);

    //Set brightness setpoint to 128:
    double nominal = 128;
    ret = is_SetAutoParameter (hCam, IS_SET_AUTO_REFERENCE, &nominal, 0);

    //Return shutter control limit:
    double maxShutter;
    ret = is_SetAutoParameter (hCam, IS_GET_AUTO_SHUTTER_MAX, &maxShutter, 0);
}
//---------------------------------------------------------------------------

