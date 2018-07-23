// ucm1b1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ucm1b1.h"
#include "ucm1b1Dlg.h"

#include "navusbAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int  usbHandle1;
int	 usbHandle3;
long motorType1;
long temp;
char buff[128];



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
// CUcm1b1Dlg dialog

CUcm1b1Dlg::CUcm1b1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUcm1b1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUcm1b1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUcm1b1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUcm1b1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUcm1b1Dlg, CDialog)
	//{{AFX_MSG_MAP(CUcm1b1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_1_HOME1, OnButton1Home1)
	ON_BN_CLICKED(IDC_BUTTON_1_MINUS1, OnButton1Minus1)
	ON_BN_CLICKED(IDC_BUTTON_1_1000G1, OnButton11000g1)
	ON_BN_CLICKED(IDC_BUTTON_1_PLUS1, OnButton1Plus1)
	ON_BN_CLICKED(IDC_BUTTON_1_LIMIT1, OnButton1Limit1)
	ON_BN_CLICKED(IDC_BUTTON_2_HOME1, OnButton2Home1)
	ON_BN_CLICKED(IDC_BUTTON_2_MINUS1, OnButton2Minus1)
	ON_BN_CLICKED(IDC_BUTTON_2_1000G1, OnButton21000g1)
	ON_BN_CLICKED(IDC_BUTTON_2_PLUS1, OnButton2Plus1)
	ON_BN_CLICKED(IDC_BUTTON_2_LIMIT1, OnButton2Limit1)
	ON_BN_CLICKED(IDC_BUTTON_OFF1, OnButtonOff1)
	ON_BN_CLICKED(IDC_BUTTON_MINUS1, OnButtonMinus1)
	ON_BN_CLICKED(IDC_BUTTON_MID1, OnButtonMid1)
	ON_BN_CLICKED(IDC_BUTTON_PLUS1, OnButtonPlus1)
	ON_BN_CLICKED(IDC_BUTTON_FULLON1, OnButtonFullon1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUcm1b1Dlg message handlers

BOOL CUcm1b1Dlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	int error = FALSE;
	do
	{
		USBFindUSBinterfaces();

		usbHandle1 = USBConnectionConnect(1,DEF_MOTOR_CONTROLLER);
		usbHandle3 = USBConnectionConnect(1,DEF_BRIGHTLIGHT);

		char errorString[512] = {0};


		if (usbHandle1 == 0x100)
		{
			strcat(errorString,"Could not connect to motor 1\r");
			error = TRUE;
		}

		if (usbHandle3 == 0x100)
		{
			strcat(errorString,"Could not connect to brightlight 1\r");
			error = TRUE;
		}

		if ( error )
		{
			int resp = 0;

			resp = AfxMessageBox(errorString,MB_ABORTRETRYIGNORE,0);
			if (resp == IDABORT)
			{
				exit(1);
			}
			else if ( resp == IDRETRY )
			{
				continue;
			}
			else // innore
				break;
		}

	
	} while ( error );

	
	USBConnectionRead(usbHandle1,REG_SYS_PRODUCTID_SUBCLASS,&motorType1);
	switch (motorType1)
	{
	default:	// if an unknown value is returned. assume it is subclass 1;
				// the first controller version did not support this and returned 0xffffffd9
	case 1:
		GetDlgItem(IDC_MOTORTYPE1)->SetWindowText("MicroMo Stepper");
		break;
	case 2:
		GetDlgItem(IDC_MOTORTYPE1)->SetWindowText("Vexta 5-Phase");
		break;
	case 3:
		GetDlgItem(IDC_MOTORTYPE1)->SetWindowText("2-Axis DC");
		break;
	}


	if ( usbHandle1 == 0x100 )
		GetDlgItem(IDC_MOTORTYPE1)->SetWindowText("no motor");


	USBConnectionRead(usbHandle1,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE1)->SetWindowText(buff);



	if ( usbHandle3 < 0x100 )
		GetDlgItem(IDC_BRIGHTLIGHT1)->SetWindowText("Brightlight 1");
	else
		GetDlgItem(IDC_BRIGHTLIGHT1)->SetWindowText("no brightlight");


	USBConnectionRead(usbHandle3,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);


	SetTimer(1,250,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUcm1b1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUcm1b1Dlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUcm1b1Dlg::OnPaint() 
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
HCURSOR CUcm1b1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUcm1b1Dlg::OnTimer(UINT nIDEvent) 
{
	USBConnectionRead(usbHandle1,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC1)->SetWindowText(buff);

	USBConnectionRead(usbHandle1,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE1)->SetWindowText(buff);





	USBConnectionRead(usbHandle3,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);
	
	CDialog::OnTimer(nIDEvent);
}

void CUcm1b1Dlg::OnButton1Home1() 
{
	temp = 0;
	USBConnectionWrite(usbHandle1, REG_USER_LIMIT_1, &temp);
}

void CUcm1b1Dlg::OnButton1Minus1() 
{
	temp = -100;
	USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_1, &temp);
}

void CUcm1b1Dlg::OnButton11000g1() 
{
	temp = 1000;
	USBConnectionWrite(usbHandle1, REG_USER_TARGET_1, &temp);
}

void CUcm1b1Dlg::OnButton1Plus1() 
{
	temp = +100;
	USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_1, &temp);
}

void CUcm1b1Dlg::OnButton1Limit1() 
{
	temp = 1;
	USBConnectionWrite(usbHandle1, REG_USER_LIMIT_1, &temp);
}

void CUcm1b1Dlg::OnButton2Home1() 
{
	temp = 0;
	USBConnectionWrite(usbHandle1, REG_USER_LIMIT_2, &temp);
}

void CUcm1b1Dlg::OnButton2Minus1() 
{
	temp = -100;
	USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_2, &temp);
}

void CUcm1b1Dlg::OnButton21000g1() 
{
	temp = 1000;
	USBConnectionWrite(usbHandle1, REG_USER_TARGET_2, &temp);
}

void CUcm1b1Dlg::OnButton2Plus1() 
{
	temp = +100;
	USBConnectionWrite(usbHandle1, REG_USER_INCREMENT_2, &temp);
}

void CUcm1b1Dlg::OnButton2Limit1() 
{
	temp = 1;
	USBConnectionWrite(usbHandle1, REG_USER_LIMIT_2, &temp);
}

void CUcm1b1Dlg::OnButtonOff1() 
{
	temp = 0;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CUcm1b1Dlg::OnButtonMinus1() 
{
	temp = -100;
	USBConnectionWrite(usbHandle3,REG_PWM_INCREMENT,&temp);
}

void CUcm1b1Dlg::OnButtonMid1() 
{
	temp = 500;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CUcm1b1Dlg::OnButtonPlus1() 
{
	temp = +100;
	USBConnectionWrite(usbHandle3,REG_PWM_INCREMENT,&temp);
}

void CUcm1b1Dlg::OnButtonFullon1() 
{
	temp = 1000;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}
