// ucm2b2.h : main header file for the UCM2B2 application
//

#if !defined(AFX_UCM2B2_H__5DE1021D_B2DC_4C52_9BB1_C20E86A44303__INCLUDED_)
#define AFX_UCM2B2_H__5DE1021D_B2DC_4C52_9BB1_C20E86A44303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUcm2b2App:
// See ucm2b2.cpp for the implementation of this class
//

class CUcm2b2App : public CWinApp
{
public:
	CUcm2b2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm2b2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUcm2b2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCM2B2_H__5DE1021D_B2DC_4C52_9BB1_C20E86A44303__INCLUDED_)
