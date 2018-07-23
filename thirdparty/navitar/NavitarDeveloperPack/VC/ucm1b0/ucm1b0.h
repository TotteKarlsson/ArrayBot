// ucm1b0.h : main header file for the UCM1B0 application
//

#if !defined(AFX_UCM1B0_H__B55F3146_B3CE_45D9_B2F4_3EE7E723A117__INCLUDED_)
#define AFX_UCM1B0_H__B55F3146_B3CE_45D9_B2F4_3EE7E723A117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUcm1b0App:
// See ucm1b0.cpp for the implementation of this class
//

class CUcm1b0App : public CWinApp
{
public:
	CUcm1b0App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm1b0App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUcm1b0App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCM1B0_H__B55F3146_B3CE_45D9_B2F4_3EE7E723A117__INCLUDED_)
