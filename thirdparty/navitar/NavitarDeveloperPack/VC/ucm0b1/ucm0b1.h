// ucm0b1.h : main header file for the UCM0B1 application
//

#if !defined(AFX_UCM0B1_H__602AC8CF_D4D3_415A_B1D2_F36EB94B98A5__INCLUDED_)
#define AFX_UCM0B1_H__602AC8CF_D4D3_415A_B1D2_F36EB94B98A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUcm0b1App:
// See ucm0b1.cpp for the implementation of this class
//

class CUcm0b1App : public CWinApp
{
public:
	CUcm0b1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUcm0b1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUcm0b1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UCM0B1_H__602AC8CF_D4D3_415A_B1D2_F36EB94B98A5__INCLUDED_)
