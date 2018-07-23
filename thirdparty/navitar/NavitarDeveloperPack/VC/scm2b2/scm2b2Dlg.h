// scm2b2Dlg.h : header file
//

#if !defined(AFX_SCM2B2DLG_H__7301FCB7_A183_4B81_B8DA_6010068F1162__INCLUDED_)
#define AFX_SCM2B2DLG_H__7301FCB7_A183_4B81_B8DA_6010068F1162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScm2b2Dlg dialog

class CScm2b2Dlg : public CDialog
{
// Construction
public:
	CScm2b2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScm2b2Dlg)
	enum { IDD = IDD_SCM2B2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm2b2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScm2b2Dlg)
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
	afx_msg void OnButton1Home2();
	afx_msg void OnButton1Minus2();
	afx_msg void OnButton11000g2();
	afx_msg void OnButton1Plus2();
	afx_msg void OnButton1Limit2();
	afx_msg void OnButton2Home2();
	afx_msg void OnButton2Minus2();
	afx_msg void OnButton2100g2();
	afx_msg void OnButton2Plus2();
	afx_msg void OnButton2Limit2();
	afx_msg void OnButtonOff1();
	afx_msg void OnButtonMinus1();
	afx_msg void OnButtonMid1();
	afx_msg void OnButtonPlus1();
	afx_msg void OnButtonFullon1();
	afx_msg void OnButtonOff2();
	afx_msg void OnButtonMinus2();
	afx_msg void OnButtonMid2();
	afx_msg void OnButtonPlus2();
	afx_msg void OnButtonFullon2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM2B2DLG_H__7301FCB7_A183_4B81_B8DA_6010068F1162__INCLUDED_)
