// Dogdemo.h : main header file for the DOGDEMO application
//

#if !defined(AFX_DOGDEMO_H__713B13ED_AB97_4B13_B2D4_FD98901D30C3__INCLUDED_)
#define AFX_DOGDEMO_H__713B13ED_AB97_4B13_B2D4_FD98901D30C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDogdemoApp:
// See Dogdemo.cpp for the implementation of this class
//

class CDogdemoApp : public CWinApp
{
public:
	CDogdemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogdemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDogdemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGDEMO_H__713B13ED_AB97_4B13_B2D4_FD98901D30C3__INCLUDED_)
