// scm2b2.h : main header file for the SCM2B2 application
//

#if !defined(AFX_SCM2B2_H__B020A154_75D2_4B75_95BB_A46D1BF192A1__INCLUDED_)
#define AFX_SCM2B2_H__B020A154_75D2_4B75_95BB_A46D1BF192A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScm2b2App:
// See scm2b2.cpp for the implementation of this class
//

class CScm2b2App : public CWinApp
{
public:
	CScm2b2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScm2b2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScm2b2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCM2B2_H__B020A154_75D2_4B75_95BB_A46D1BF192A1__INCLUDED_)
