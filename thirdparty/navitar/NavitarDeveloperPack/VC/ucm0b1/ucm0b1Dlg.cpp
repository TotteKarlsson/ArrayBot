// ucm0b1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ucm0b1.h"
#include "ucm0b1Dlg.h"

#include "navusbAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int	 usbHandle3;
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
// CUcm0b1Dlg dialog

CUcm0b1Dlg::CUcm0b1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUcm0b1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUcm0b1Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUcm0b1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUcm0b1Dlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUcm0b1Dlg, CDialog)
	//{{AFX_MSG_MAP(CUcm0b1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OFF1, OnButtonOff1)
	ON_BN_CLICKED(IDC_BUTTON_MINUS1, OnButtonMinus1)
	ON_BN_CLICKED(IDC_BUTTON_MID1, OnButtonMid1)
	ON_BN_CLICKED(IDC_BUTTON_PLUS1, OnButtonPlus1)
	ON_BN_CLICKED(IDC_BUTTON_FULLON1, OnButtonFullon1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUcm0b1Dlg message handlers

BOOL CUcm0b1Dlg::OnInitDialog()
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

	do
	{
		USBFindUSBinterfaces();
		usbHandle3 = USBConnectionConnect(1,DEF_BRIGHTLIGHT);

		if ( usbHandle3 == 0x100)
		{
			int resp;
			resp = AfxMessageBox("Could not connect to brightlight 1",MB_ABORTRETRYIGNORE,0);
			if (resp == IDABORT)
			{
				exit(1);
			}
			else if ( resp == IDRETRY )
			{
				continue;
			}
			else 
				break;
		}
	}	while ( usbHandle3 == 0x100);


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

void CUcm0b1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUcm0b1Dlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUcm0b1Dlg::OnPaint() 
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
HCURSOR CUcm0b1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CUcm0b1Dlg::OnTimer(UINT nIDEvent) 
{
	USBConnectionRead(usbHandle3,REG_PWM_ABSOLUTE,&temp);
	sprintf(buff,"%5.1f",(float)(temp)/10.0);
	GetDlgItem(IDC_Value1)->SetWindowText(buff);
	
	CDialog::OnTimer(nIDEvent);
}

void CUcm0b1Dlg::OnButtonOff1() 
{
	temp = 0;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CUcm0b1Dlg::OnButtonMinus1() 
{
	temp = -100;
	USBConnectionWrite(usbHandle3,REG_PWM_INCREMENT,&temp);
}

void CUcm0b1Dlg::OnButtonMid1() 
{
	temp = 500;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}

void CUcm0b1Dlg::OnButtonPlus1() 
{
	temp = +100;
	USBConnectionWrite(usbHandle3,REG_PWM_INCREMENT,&temp);
}

void CUcm0b1Dlg::OnButtonFullon1() 
{
	temp = 1000;
	USBConnectionWrite(usbHandle3,REG_PWM_ABSOLUTE,&temp);
}
