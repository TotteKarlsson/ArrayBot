// ucm1b1.h : main header file for the UCM1B1 application
//

#if !defined(AFX_UCM1B1_H__879E67AE_85FE_4C0F_8737_F38A26660751__INCLUDED_)
#define AFX_UCM1B1_H__879E67AE_85FE_4C0F_8737_F38A26660751__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUcm1b1App:
// See ucm1b1.cpp for the implementation of this class
//

class CUcm1b1App : public CWinApp
{
public:
	CUcm1b1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm1b1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUcm1b1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCM1B1_H__879E67AE_85FE_4C0F_8737_F38A26660751__INCLUDED_)
