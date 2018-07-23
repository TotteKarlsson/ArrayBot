// ucm1b0Dlg.h : header file
//

#if !defined(AFX_UCM1B0DLG_H__557844B7_07DF_43C5_8F41_2EDA8E0980D7__INCLUDED_)
#define AFX_UCM1B0DLG_H__557844B7_07DF_43C5_8F41_2EDA8E0980D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUcm1b0Dlg dialog

class CUcm1b0Dlg : public CDialog
{
// Construction
public:
	CUcm1b0Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUcm1b0Dlg)
	enum { IDD = IDD_UCM1B0_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm1b0Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUcm1b0Dlg)
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

#endif // !defined(AFX_UCM1B0DLG_H__557844B7_07DF_43C5_8F41_2EDA8E0980D7__INCLUDED_)
