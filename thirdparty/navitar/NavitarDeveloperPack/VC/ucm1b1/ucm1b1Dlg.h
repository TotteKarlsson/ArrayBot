// ucm1b1Dlg.h : header file
//

#if !defined(AFX_UCM1B1DLG_H__480789EB_8D4D_4A3A_A972_FF7A77BFFF8F__INCLUDED_)
#define AFX_UCM1B1DLG_H__480789EB_8D4D_4A3A_A972_FF7A77BFFF8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUcm1b1Dlg dialog

class CUcm1b1Dlg : public CDialog
{
// Construction
public:
	CUcm1b1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUcm1b1Dlg)
	enum { IDD = IDD_UCM1B1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm1b1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUcm1b1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1Home1();
	afx_msg void OnButton1Minus1();
	afx_msg void OnButton11000g1();
	afx_msg void OnButton1Plus1();
	afx_msg void OnButton1Limit1();
	afx_msg void OnButton2Home1();
	afx_msg void OnButton2Minus1();
	afx_msg void OnButton21000g1();
	afx_msg void OnButton2Plus1();
	afx_msg void OnButton2Limit1();
	afx_msg void OnButtonOff1();
	afx_msg void OnButtonMinus1();
	afx_msg void OnButtonMid1();
	afx_msg void OnButtonPlus1();
	afx_msg void OnButtonFullon1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCM1B1DLG_H__480789EB_8D4D_4A3A_A972_FF7A77BFFF8F__INCLUDED_)
