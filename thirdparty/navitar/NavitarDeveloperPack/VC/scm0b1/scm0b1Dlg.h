// scm0b1Dlg.h : header file
//

#if !defined(AFX_SCM0B1DLG_H__8D95785B_E440_4B88_BD7A_F7136108D223__INCLUDED_)
#define AFX_SCM0B1DLG_H__8D95785B_E440_4B88_BD7A_F7136108D223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScm0b1Dlg dialog

class CScm0b1Dlg : public CDialog
{
// Construction
public:
	CScm0b1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScm0b1Dlg)
	enum { IDD = IDD_SCM0B1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm0b1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScm0b1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
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

#endif // !defined(AFX_SCM0B1DLG_H__8D95785B_E440_4B88_BD7A_F7136108D223__INCLUDED_)
