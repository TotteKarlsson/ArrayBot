//==========================================================================//
//                                                                          //
//  Copyright (C) 2004 - 2014                                               //
//  OEM uc480		                                                        //
//                                                                          //
//  The information in this document is subject to change without           //
//  notice and should not be construed as a commitment.						//
//  We do not assume any responsibility for any errors						//
//  that may appear in this document.                                       //
//                                                                          //
//  This document, or source code, is provided solely as an example         //
//  of how to utilize uc480 libraries in a sample application.				//
//  We do not assume any responsibility for the use or						//
//  reliability of any portion of this document or the described software.  //
//                                                                          //
//  General permission to copy or modify, but not for profit, is hereby     //
//  granted,  provided that the above copyright notice is included and      //
//  reference made to the fact that reproduction privileges were granted.	//
//                                                                          //
//==========================================================================//



// uc480LiveDlg.h : header file
//

#if !defined(AFX_SIMPLELIVEDLG_H__00EFA87C_7A28_4501_8760_D28D4F306A00__INCLUDED_)
#define AFX_SIMPLELIVEDLG_H__00EFA87C_7A28_4501_8760_D28D4F306A00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uc480class.h"


typedef enum _disp_mode 
{
  e_disp_mode_bitmap = 0,
  e_disp_mode_direct3D
};


/////////////////////////////////////////////////////////////////////////////
// Cuc480LiveDlg dialog

class Cuc480LiveDlg : public CDialog
{
// Construction
public:
	Cuc480LiveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(Cuc480LiveDlg)
	enum { IDD = IDD_SIMPLELIVE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cuc480LiveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON	m_hIcon;
	
	Cuc480   m_camera;

	// Camera varibles
	HWND	m_hDisplay;			// handle to diplay window
	INT		m_Ret;			// return value of SDK functions
	INT		m_nColorMode;	// Y8/RGB16/RGB24/RGB32
	INT		m_nBitsPerPixel;// number of bits needed store one pixel
	INT		m_nSizeX;		// width of video 
	INT		m_nSizeY;		// height of video
    char*   m_pcImageMemory;// image memory - pointer to buffer
    INT     m_lMemoryId;    // image memory - buffer ID
    SENSORINFO m_sInfo;     // sensor info struct
    int m_nDispModeSel;

	bool OpenCamera();
    void ExitCamera();
    int  InitDisplayMode();
    
	// Generated message map functions
	//{{AFX_MSG(Cuc480LiveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonExit();
	LRESULT OnUSBCameraMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonLoadParameter();
    afx_msg void OnBnClickedDispModeChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLELIVEDLG_H__00EFA87C_7A28_4501_8760_D28D4F306A00__INCLUDED_)
