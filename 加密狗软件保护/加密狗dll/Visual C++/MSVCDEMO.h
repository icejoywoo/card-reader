// MSVCDEMO.h : main header file for the MSVCDEMO application
//

#if !defined(AFX_MSVCDEMO_H__334F45C5_CA60_481A_A093_E8FCF50F45D6__INCLUDED_)
#define AFX_MSVCDEMO_H__334F45C5_CA60_481A_A093_E8FCF50F45D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSVCDEMOApp:
// See MSVCDEMO.cpp for the implementation of this class
//

class CMSVCDEMOApp : public CWinApp
{
public:
	CMSVCDEMOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSVCDEMOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSVCDEMOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSVCDEMO_H__334F45C5_CA60_481A_A093_E8FCF50F45D6__INCLUDED_)
