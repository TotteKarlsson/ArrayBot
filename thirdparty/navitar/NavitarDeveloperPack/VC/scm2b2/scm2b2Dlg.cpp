// scm2b2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "scm2b2.h"
#include "scm2b2Dlg.h"

#include "navserAPI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int  serHandle1;
int	 serHandle2;
int  serHandle3;
int	 serHandle4;
long motorType1;
long motorType2;
long temp;
char buff[128];


#define COM1 1
#define COM2 2
#define COM3 3
#define COM4 4


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
// CScm2b2Dlg dialog

CScm2b2Dlg::CScm2b2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScm2b2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScm2b2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScm2b2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScm2b2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScm2b2Dlg, CDialog)
	//{{AFX_MSG_MAP(CScm2b2Dlg)
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
	ON_BN_CLICKED(IDC_BUTTON_1_HOME2, OnButton1Home2)
	ON_BN_CLICKED(IDC_BUTTON_1_MINUS2, OnButton1Minus2)
	ON_BN_CLICKED(IDC_BUTTON_1_1000G2, OnButton11000g2)
	ON_BN_CLICKED(IDC_BUTTON_1_PLUS2, OnButton1Plus2)
	ON_BN_CLICKED(IDC_BUTTON_1_LIMIT2, OnButton1Limit2)
	ON_BN_CLICKED(IDC_BUTTON_2_HOME2, OnButton2Home2)
	ON_BN_CLICKED(IDC_BUTTON_2_MINUS2, OnButton2Minus2)
	ON_BN_CLICKED(IDC_BUTTON_2_100G2, OnButton2100g2)
	ON_BN_CLICKED(IDC_BUTTON_2_PLUS2, OnButton2Plus2)
	ON_BN_CLICKED(IDC_BUTTON_2_LIMIT2, OnButton2Limit2)
	ON_BN_CLICKED(IDC_BUTTON_OFF1, OnButtonOff1)
	ON_BN_CLICKED(IDC_BUTTON_MINUS1, OnButtonMinus1)
	ON_BN_CLICKED(IDC_BUTTON_MID1, OnButtonMid1)
	ON_BN_CLICKED(IDC_BUTTON_PLUS1, OnButtonPlus1)
	ON_BN_CLICKED(IDC_BUTTON_FULLON1, OnButtonFullon1)
	ON_BN_CLICKED(IDC_BUTTON_OFF2, OnButtonOff2)
	ON_BN_CLICKED(IDC_BUTTON_MINUS2, OnButtonMinus2)
	ON_BN_CLICKED(IDC_BUTTON_MID2, OnButtonMid2)
	ON_BN_CLICKED(IDC_BUTTON_PLUS2, OnButtonPlus2)
	ON_BN_CLICKED(IDC_BUTTON_FULLON2, OnButtonFullon2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScm2b2Dlg message handlers

BOOL CScm2b2Dlg::OnInitDialog()
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

	serHandle1 = SerConnectionConnect(COM1,DEF_MOTOR_CONTROLLER);

	while ( serHandle1 == 0)
	{
		int resp;
		resp = AfxMessageBox("Could not connect to motor 1",MB_ABORTRETRYIGNORE,0);
		if (resp == IDABORT)
		{
			exit(1);
		}
		else if ( resp == IDRETRY )
		{
			serHandle1 = SerConnectionConnect(COM1,DEF_MOTOR_CONTROLLER);
		}
		else 
			break;
	}

	SerConnectionRead(serHandle1,REG_SYS_PRODUCTID_SUBCLASS,&motorType1);
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


	if ( serHandle1 == 0 )
		GetDlgItem(IDC_MOTORTYPE1)->SetWindowText("no motor");


	SerConnectionRead(serHandle1,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC1)->SetWindowText(buff);

	SerConnectionRead(serHandle1,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE1)->SetWindowText(buff);

	SerConnectionRead(serHandle1,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC1)->SetWindowText(buff);

	SerConnectionRead(serHandle1,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE1)->SetWindowText(buff);


	serHandle2 = SerConnectionConnect(COM2,DEF_MOTOR_CONTROLLER);

	while ( serHandle2 == 0)
	{
		int resp;
		resp = AfxMessageBox("Could not connect to motor 2",MB_ABORTRETRYIGNORE,0);
		if (resp == IDABORT)
		{
			exit(1);
		}
		else if ( resp == IDRETRY )
		{
			serHandle2 = SerConnectionConnect(COM2,DEF_MOTOR_CONTROLLER);
		}
		else 
			break;
	}

	SerConnectionRead(serHandle2,REG_SYS_PRODUCTID_SUBCLASS,&motorType1);
	switch (motorType2)
	{
	default:	// if an unknown value is returned. assume it is subclass 1;
				// the first controller version did not support this and returned 0xffffffd9
	case 1:
		GetDlgItem(IDC_MOTORTYPE2)->SetWindowText("MicroMo Stepper");
		break;
	case 2:
		GetDlgItem(IDC_MOTORTYPE2)->SetWindowText("Vexta 5-Phase");
		break;
	case 3:
		GetDlgItem(IDC_MOTORTYPE2)->SetWindowText("2-Axis DC");
		break;
	}


	if ( serHandle2 == 0 )
		GetDlgItem(IDC_MOTORTYPE2)->SetWindowText("no motor");


	SerConnectionRead(serHandle2,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC1)->SetWindowText(buff);

	SerConnectionRead(serHandle2,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE1)->SetWindowText(buff);

	SerConnectionRead(serHandle2,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC1)->SetWindowText(buff);

	SerConnectionRead(serHandle2,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE1)->SetWindowText(buff);






	serHandle3 = SerConnectionConnect(COM3,DEF_BRIGHTLIGHT);

	while ( serHandle3 == 0)
	{
		int resp;
		resp = AfxMessageBox("Could not connect to brightlight 1",MB_ABORTRETRYIGNORE,0);
		if (resp == IDABORT)
		{
			exit(1);
		}
		else if ( resp == IDRETRY )
		{
			serHandle3 = SerConnectionConnect(COM3,DEF_BRIGHTLIGHT);
		}
		else 
			break;
	}


	if ( serHandle3 != 0 )
		GetDlgItem(IDC_BRIGHTLIGHT1)->SetWindowText("Brightlight 1");
	else
		GetDlgItem(IDC_BRIGHTLIGHT1)->SetWindowText("no brightlight");


	SerConnectionRead(serHandle3,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);



	serHandle4 = SerConnectionConnect(COM4,DEF_BRIGHTLIGHT);

	while ( serHandle4 == 0)
	{
		int resp;
		resp = AfxMessageBox("Could not connect to brightlight 2",MB_ABORTRETRYIGNORE,0);
		if (resp == IDABORT)
		{
			exit(1);
		}
		else if ( resp == IDRETRY )
		{
			serHandle4 = SerConnectionConnect(COM4,DEF_BRIGHTLIGHT);
		}
		else 
			break;
	}


	if ( serHandle4 != 0 )
		GetDlgItem(IDC_BRIGHTLIGHT2)->SetWindowText("Brightlight 2");
	else
		GetDlgItem(IDC_BRIGHTLIGHT2)->SetWindowText("no brightlight");


	SerConnectionRead(serHandle4,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);



	SetTimer(1,250,NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScm2b2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScm2b2Dlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScm2b2Dlg::OnPaint() 
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
HCURSOR CScm2b2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScm2b2Dlg::OnTimer(UINT nIDEvent) 
{
	temp = 0;
	SerConnectionRead(serHandle1,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC1)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle1,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE1)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle1,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC1)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle1,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE1)->SetWindowText(buff);



	temp = 0;
	SerConnectionRead(serHandle2,REG_USER_CURRENT_1,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_1_LOC2)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle2,REG_USER_STATUS_1,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_1_STATE2)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle2,REG_USER_CURRENT_2,&temp);
	sprintf(buff,"%d",temp);
	GetDlgItem(IDC_EDIT_2_LOC2)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle2,REG_USER_STATUS_2,&temp);
	sprintf(buff,"0x%03X",temp);
	GetDlgItem(IDC_EDIT_2_STATE2)->SetWindowText(buff);




	temp = 0;
	SerConnectionRead(serHandle3,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);

	temp = 0;
	SerConnectionRead(serHandle4,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value2)->SetWindowText(buff);
	
	
	CDialog::OnTimer(nIDEvent);
}

void CScm2b2Dlg::OnButton1Home1() 
{
	temp = 0;
	SerConnectionWrite(serHandle1, REG_USER_LIMIT_1, &temp);
}

void CScm2b2Dlg::OnButton1Minus1() 
{
	temp = -100;
	SerConnectionWrite(serHandle1, REG_USER_INCREMENT_1, &temp);
}

void CScm2b2Dlg::OnButton11000g1() 
{
	temp = 1000;
	SerConnectionWrite(serHandle1, REG_USER_TARGET_1, &temp);
}

void CScm2b2Dlg::OnButton1Plus1() 
{
	temp = +100;
	SerConnectionWrite(serHandle1, REG_USER_INCREMENT_1, &temp);
}

void CScm2b2Dlg::OnButton1Limit1() 
{
	temp = 1;
	SerConnectionWrite(serHandle1, REG_USER_LIMIT_1, &temp);
}

void CScm2b2Dlg::OnButton2Home1() 
{
	temp = 0;
	SerConnectionWrite(serHandle1, REG_USER_LIMIT_2, &temp);
}

void CScm2b2Dlg::OnButton2Minus1() 
{
	temp = -100;
	SerConnectionWrite(serHandle1, REG_USER_INCREMENT_2, &temp);
}

void CScm2b2Dlg::OnButton21000g1() 
{
	temp = 1000;
	SerConnectionWrite(serHandle1, REG_USER_TARGET_2, &temp);
}

void CScm2b2Dlg::OnButton2Plus1() 
{
	temp = +100;
	SerConnectionWrite(serHandle1, REG_USER_INCREMENT_2, &temp);
}

void CScm2b2Dlg::OnButton2Limit1() 
{
	temp = 1;
	SerConnectionWrite(serHandle1, REG_USER_LIMIT_2, &temp);
}

void CScm2b2Dlg::OnButton1Home2() 
{
	temp = 0;
	SerConnectionWrite(serHandle2, REG_USER_LIMIT_1, &temp);
}

void CScm2b2Dlg::OnButton1Minus2() 
{
	temp = -100;
	SerConnectionWrite(serHandle2, REG_USER_INCREMENT_1, &temp);
}

void CScm2b2Dlg::OnButton11000g2() 
{
	temp = 1000;
	SerConnectionWrite(serHandle2, REG_USER_TARGET_1, &temp);
}

void CScm2b2Dlg::OnButton1Plus2() 
{
	temp = +100;
	SerConnectionWrite(serHandle2, REG_USER_INCREMENT_1, &temp);
}

void CScm2b2Dlg::OnButton1Limit2() 
{
	temp = 1;
	SerConnectionWrite(serHandle2, REG_USER_LIMIT_1, &temp);
}

void CScm2b2Dlg::OnButton2Home2() 
{
	temp = 0;
	SerConnectionWrite(serHandle2, REG_USER_LIMIT_2, &temp);
}

void CScm2b2Dlg::OnButton2Minus2() 
{
	temp = -100;
	SerConnectionWrite(serHandle2, REG_USER_INCREMENT_2, &temp);
}

void CScm2b2Dlg::OnButton2100g2() 
{
	temp = 1000;
	SerConnectionWrite(serHandle2, REG_USER_TARGET_2, &temp);
}

void CScm2b2Dlg::OnButton2Plus2() 
{
	temp = +100;
	SerConnectionWrite(serHandle2, REG_USER_INCREMENT_2, &temp);
}

void CScm2b2Dlg::OnButton2Limit2() 
{
	temp = 1;
	SerConnectionWrite(serHandle2, REG_USER_LIMIT_2, &temp);
}

void CScm2b2Dlg::OnButtonOff1() 
{
	temp = 0;
	SerConnectionWrite(serHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CScm2b2Dlg::OnButtonMinus1() 
{
	temp = -100;
	SerConnectionWrite(serHandle3,REG_PWM_INCREMENT,&temp);
}

void CScm2b2Dlg::OnButtonMid1() 
{
	temp = 500;
	SerConnectionWrite(serHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CScm2b2Dlg::OnButtonPlus1() 
{
	temp = +100;
	SerConnectionWrite(serHandle3,REG_PWM_INCREMENT,&temp);
}

void CScm2b2Dlg::OnButtonFullon1() 
{
	temp = 1000;
	SerConnectionWrite(serHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CScm2b2Dlg::OnButtonOff2() 
{
	temp = 0;
	SerConnectionWrite(serHandle4,REG_PWM_ABSOLUTE,&temp);
}

void CScm2b2Dlg::OnButtonMinus2() 
{
	temp = -100;
	SerConnectionWrite(serHandle4,REG_PWM_INCREMENT,&temp);
}

void CScm2b2Dlg::OnButtonMid2() 
{
	temp = 500;
	SerConnectionWrite(serHandle4,REG_PWM_ABSOLUTE,&temp);
}

void CScm2b2Dlg::OnButtonPlus2() 
{
	temp = +100;
	SerConnectionWrite(serHandle4,REG_PWM_INCREMENT,&temp);
}

void CScm2b2Dlg::OnButtonFullon2() 
{
	temp = 1000;
	SerConnectionWrite(serHandle4,REG_PWM_ABSOLUTE,&temp);
}
