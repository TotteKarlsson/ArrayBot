//==========================================================================//
//                                                                          //
//  Copyright (C) 2004 - 2014                                               //
//  OEM uc480                                                               //
//                                                                          //
//  The information in this document is subject to change without           //
//  notice and should not be construed as a commitment.                     //
//  We do not assume any responsibility for any errors                      //
//  that may appear in this document.                                       //
//                                                                          //
//  This document, or source code, is provided solely as an example         //
//  of how to utilize uc480 libraries in a sample application.              //
//  We do not assume any responsibility for the use or                      //
//  reliability of any portion of this document or the described software.  //
//                                                                          //
//  General permission to copy or modify, but not for profit, is hereby     //
//  granted,  provided that the above copyright notice is included and      //
//  reference made to the fact that reproduction privileges were granted.   //
//                                                                          //
//==========================================================================//


// Simple LiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uc480Live.h"
#include "uc480LiveDlg.h"
#include ".\uc480livedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cuc480LiveDlg dialog

Cuc480LiveDlg::Cuc480LiveDlg(CWnd* pParent /*=NULL*/)
    : CDialog(Cuc480LiveDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(Cuc480LiveDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cuc480LiveDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Cuc480LiveDlg)
	DDX_Radio(pDX, IDC_DISP_DIB, m_nDispModeSel);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cuc480LiveDlg, CDialog)
    //{{AFX_MSG_MAP(Cuc480LiveDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
    ON_MESSAGE(IS_UC480_MESSAGE, OnUSBCameraMessage)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_PARAMETER, OnBnClickedButtonLoadParameter)
    ON_BN_CLICKED(IDC_DISP_DIB, OnBnClickedDispModeChange)
    ON_BN_CLICKED(IDC_DISP_DD, OnBnClickedDispModeChange)
    //}}AFX_MSG_MAP
    ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cuc480LiveDlg message handlers

BOOL Cuc480LiveDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    //SetIcon(m_hIcon, FALSE);      // Set small icon

    m_hDisplay = GetDlgItem( IDC_DISPLAY )->m_hWnd; // get handle to display window

    m_pcImageMemory  = NULL;
    m_lMemoryId = 0;
    m_nDispModeSel = e_disp_mode_bitmap;
    UpdateData(FALSE);
    
    OpenCamera();       // open a camera handle

    return true;

}

void Cuc480LiveDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cuc480LiveDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cuc480LiveDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}



///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OnButtonStart() 
//
// DESCRIPTION: start live display and return immediately
//
///////////////////////////////////////////////////////////////////////////////
void Cuc480LiveDlg::OnButtonStart() 
{
    if( !m_camera.IsInit() )
        OpenCamera();

    if( m_camera.IsInit() )
    {
        m_camera.CaptureVideo( IS_WAIT );

        GetDlgItem(IDC_DISP_DIB)->EnableWindow(FALSE);
        GetDlgItem(IDC_DISP_DD)->EnableWindow(FALSE);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OnButtonStop() 
//
// DESCRIPTION: stop live display and return immediately
//
///////////////////////////////////////////////////////////////////////////////
void Cuc480LiveDlg::OnButtonStop() 
{
    if( m_camera.IsInit() )
    {
        // stop live immediately - force stop
        m_camera.StopLiveVideo( IS_FORCE_VIDEO_STOP );    

        GetDlgItem(IDC_DISP_DIB)->EnableWindow(TRUE);
        GetDlgItem(IDC_DISP_DD)->EnableWindow(TRUE);
    }
}



///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OnBnClickedButtonLoadParameter() 
//
// DESCRIPTION: - loads parameters from an ini file
//              - reallocates the memory
//
///////////////////////////////////////////////////////////////////////////////
void Cuc480LiveDlg::OnBnClickedButtonLoadParameter()
{
    if ( !m_camera.IsInit() )
        OpenCamera();

    if ( m_camera.IsInit() )
    {
        if( m_camera.LoadParameters( NULL ) == IS_SUCCESS && m_pcImageMemory != NULL )
        {
            // stop image acquisition
            m_camera.StopLiveVideo(IS_FORCE_VIDEO_STOP);
            // realloc image mem with actual sizes and depth.
            m_camera.FreeImageMem( m_pcImageMemory, m_lMemoryId );
            m_nSizeX = m_camera.SetImageSize( IS_GET_IMAGE_SIZE_X, 0 );
            m_nSizeY = m_camera.SetImageSize( IS_GET_IMAGE_SIZE_Y, 0 );
            switch( m_camera.SetColorMode( IS_GET_COLOR_MODE ) )
            {
                case IS_SET_CM_RGB32:
                    m_nBitsPerPixel = 32;
                    break;
                case IS_SET_CM_RGB24:
                    m_nBitsPerPixel = 24;
                    break;
                case IS_SET_CM_RGB16:
                case IS_SET_CM_RGB15:
                case IS_SET_CM_UYVY:
                    m_nBitsPerPixel = 16;
                    break;
                case IS_SET_CM_Y8:                
                case IS_SET_CM_BAYER:
                default:
                    m_nBitsPerPixel = 8;
                    break;
            }   // end switch( m_camera.SetColorMode( IS_GET_COLOR_MODE ) )

            // memory initialization
            m_camera.AllocImageMem( m_nSizeX,
                                    m_nSizeY,
                                    m_nBitsPerPixel,
                                    &m_pcImageMemory,
                                    &m_lMemoryId);
            m_camera.SetImageMem(m_pcImageMemory, m_lMemoryId );  // set memory active

            // display initialization
            m_camera.SetImageSize(m_nSizeX, m_nSizeY );
            // run live image
            m_camera.CaptureVideo(IS_DONT_WAIT);
        }   // end if( m_camera.LoadParameters( NULL ) ==
    }   // end if ( m_camera.IsInit() )
}




///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OnButtonExit() 
//
// DESCRIPTION: - stop live display
//              - exit the camera
//              - quit application
//
///////////////////////////////////////////////////////////////////////////////
void Cuc480LiveDlg::OnButtonExit() 
{
    ExitCamera();
    PostQuitMessage( 0 );
}



///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OpenCamera() 
//
// DESCRIPTION: - Opens a handle to a connected camera
//
///////////////////////////////////////////////////////////////////////////////
bool Cuc480LiveDlg::OpenCamera()
{
    ExitCamera();

    // init camera
    m_Ret = m_camera.InitCamera(0, m_hDisplay );        // init cam

    // continue when camera is sucessfully initialized
    if( m_Ret == IS_SUCCESS )
    {
        // retrieve original image size
        m_camera.GetSensorInfo(&m_sInfo );

        m_camera.GetMaxImageSize(&m_nSizeX, &m_nSizeY);

        UpdateData(TRUE);
        m_Ret = InitDisplayMode();

        // enable the dialog based error report
        //m_Ret = m_camera.SetErrorReport(IS_DISABLE_ERR_REP);
        if( m_Ret != IS_SUCCESS )
        {
            AfxMessageBox( "ERROR: Can not enable the automatic error report!" , MB_ICONEXCLAMATION, 0 );
            return false;
        }

        // Enable Messages
        m_camera.EnableMessage(IS_DEVICE_REMOVED ,GetSafeHwnd());
        m_camera.EnableMessage(IS_DEVICE_RECONNECTED , GetSafeHwnd());
        m_camera.EnableMessage(IS_FRAME , GetSafeHwnd());

        // start live video
        m_camera.CaptureVideo(IS_WAIT);

        GetDlgItem(IDC_DISP_DIB)->EnableWindow(FALSE);
        GetDlgItem(IDC_DISP_DD)->EnableWindow(FALSE);

        // do the whitebalance once on the first acquisitioned image only on color cameras
        if( m_sInfo.nColorMode == IS_COLORMODE_BAYER )
            m_camera.SetWhiteBalance(IS_SET_WB_AUTO_ENABLE);

        return true;
    }
    else
    {
        AfxMessageBox("No camera could be opened !", MB_ICONWARNING );
    }

    return false;
}


///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::OnUSBCameraMessage() 
//
// DESCRIPTION: - handles the messages from the camera
//              - messages must be enabled using is_EnableMessage()
//
///////////////////////////////////////////////////////////////////////////////
LRESULT Cuc480LiveDlg::OnUSBCameraMessage( WPARAM wParam, LPARAM lParam )
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
    }
    
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::ExitCamera() 
//
// DESCRIPTION: - exits the instance of the camera
//
///////////////////////////////////////////////////////////////////////////////
void Cuc480LiveDlg::ExitCamera()
{
      if( m_camera.IsInit() )
      {
            m_camera.EnableMessage( IS_FRAME, NULL );
            m_camera.StopLiveVideo( IS_WAIT );
            if( m_pcImageMemory != NULL )
                m_camera.FreeImageMem( m_pcImageMemory, m_lMemoryId );

            m_pcImageMemory = NULL;
            m_camera.ExitCamera();
      }     // end if( m_camera.IsInit() )
}


///////////////////////////////////////////////////////////////////////////////
//
// METHOD Cuc480LiveDlg::InitDisplayMode() 
//
// DESCRIPTION: - initializes the display mode
//
///////////////////////////////////////////////////////////////////////////////
int Cuc480LiveDlg::InitDisplayMode()
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
                UpdateData(FALSE);
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
                AfxMessageBox("Memory allocation failed!", MB_ICONWARNING );
            }
            else
                m_camera.SetImageMem( m_pcImageMemory, m_lMemoryId );
            break;
    }   // end switch(m_nDispModeSel)

    if(m_Ret == IS_SUCCESS )
    {
        // set the desired color mode
        m_camera.SetColorMode( m_nColorMode );

        // set the image size to capture
        m_camera.SetImageSize( m_nSizeX, m_nSizeY );

    }   // end if(m_Ret == IS_SUCCESS )

    return m_Ret;
}


void Cuc480LiveDlg::OnBnClickedDispModeChange()
{
    UpdateData(TRUE);
    if(InitDisplayMode() == IS_SUCCESS)
    {
        RedrawWindow();
    }
}

void Cuc480LiveDlg::OnClose()
{
    ExitCamera();

    CDialog::OnClose();
}
