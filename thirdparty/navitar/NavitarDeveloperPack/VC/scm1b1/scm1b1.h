// scm1b1.h : main header file for the SCM1B1 application
//

#if !defined(AFX_SCM1B1_H__4FBCEA2E_73E0_46BB_8363_57C5A9BD79BF__INCLUDED_)
#define AFX_SCM1B1_H__4FBCEA2E_73E0_46BB_8363_57C5A9BD79BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScm1b1App:
// See scm1b1.cpp for the implementation of this class
//

class CScm1b1App : public CWinApp
{
public:
	CScm1b1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm1b1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScm1b1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM1B1_H__4FBCEA2E_73E0_46BB_8363_57C5A9BD79BF__INCLUDED_)
