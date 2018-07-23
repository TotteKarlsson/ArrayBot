// scm1b0Dlg.h : header file
//

#if !defined(AFX_SCM1B0DLG_H__389C84A4_32A7_4C4C_A4ED_3C04B2DCAE81__INCLUDED_)
#define AFX_SCM1B0DLG_H__389C84A4_32A7_4C4C_A4ED_3C04B2DCAE81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScm1b0Dlg dialog

class CScm1b0Dlg : public CDialog
{
// Construction
public:
	CScm1b0Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScm1b0Dlg)
	enum { IDD = IDD_SCM1B0_DIALOG };
	CButton	m_motorType1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm1b0Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScm1b0Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
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
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM1B0DLG_H__389C84A4_32A7_4C4C_A4ED_3C04B2DCAE81__INCLUDED_)
