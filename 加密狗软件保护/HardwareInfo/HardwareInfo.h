// HardwareInfo.h : main header file for the HARDWAREINFO application
//

#if !defined(AFX_HARDWAREINFO_H__F52A2C87_C043_11D3_BC14_0080C7249374__INCLUDED_)
#define AFX_HARDWAREINFO_H__F52A2C87_C043_11D3_BC14_0080C7249374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoApp:
// See HardwareInfo.cpp for the implementation of this class
//

class CHardwareInfoApp : public CWinApp
{
public:
	CHardwareInfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardwareInfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHardwareInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDWAREINFO_H__F52A2C87_C043_11D3_BC14_0080C7249374__INCLUDED_)
