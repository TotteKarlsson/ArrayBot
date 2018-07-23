// scm0b1.h : main header file for the SCM0B1 application
//

#if !defined(AFX_SCM0B1_H__65B88456_7538_4EBA_B4F6_5C0B62E10D85__INCLUDED_)
#define AFX_SCM0B1_H__65B88456_7538_4EBA_B4F6_5C0B62E10D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScm0b1App:
// See scm0b1.cpp for the implementation of this class
//

class CScm0b1App : public CWinApp
{
public:
	CScm0b1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm0b1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScm0b1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM0B1_H__65B88456_7538_4EBA_B4F6_5C0B62E10D85__INCLUDED_)
