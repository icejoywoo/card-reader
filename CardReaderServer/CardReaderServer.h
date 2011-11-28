// CardReaderServer.h : main header file for the CARDREADERSERVER application
//

#if !defined(AFX_CARDREADERSERVER_H__4C26F9F1_C29F_4AB5_8629_E63CFD4EAB37__INCLUDED_)
#define AFX_CARDREADERSERVER_H__4C26F9F1_C29F_4AB5_8629_E63CFD4EAB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCardReaderServerApp:
// See CardReaderServer.cpp for the implementation of this class
//

class CCardReaderServerApp : public CWinApp
{
public:
	CCardReaderServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReaderServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCardReaderServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREADERSERVER_H__4C26F9F1_C29F_4AB5_8629_E63CFD4EAB37__INCLUDED_)
