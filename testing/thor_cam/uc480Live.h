// uc480Live.h : main header file for the SIMPLELIVE application
//

#if !defined(AFX_SIMPLELIVE_H__3066A7A2_C7D9_4E0E_AF60_510BE2961B11__INCLUDED_)
#define AFX_SIMPLELIVE_H__3066A7A2_C7D9_4E0E_AF60_510BE2961B11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// Cuc480LiveApp:
// See uc480Live.cpp for the implementation of this class
//

class Cuc480LiveApp : public CWinApp
{
public:
	Cuc480LiveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cuc480LiveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(Cuc480LiveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLELIVE_H__3066A7A2_C7D9_4E0E_AF60_510BE2961B11__INCLUDED_)
