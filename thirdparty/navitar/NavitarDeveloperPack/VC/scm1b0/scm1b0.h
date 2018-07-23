// scm1b0.h : main header file for the SCM1B0 application
//

#if !defined(AFX_SCM1B0_H__80F7C1C1_5902_43A7_A0A5_5A524B95EF90__INCLUDED_)
#define AFX_SCM1B0_H__80F7C1C1_5902_43A7_A0A5_5A524B95EF90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScm1b0App:
// See scm1b0.cpp for the implementation of this class
//

class CScm1b0App : public CWinApp
{
public:
	CScm1b0App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm1b0App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScm1b0App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM1B0_H__80F7C1C1_5902_43A7_A0A5_5A524B95EF90__INCLUDED_)
