// SecretKeyServer.h : main header file for the SECRETKEYSERVER application
//

#if !defined(AFX_SECRETKEYSERVER_H__22817EE1_163C_4834_9292_C50D4FB3313A__INCLUDED_)
#define AFX_SECRETKEYSERVER_H__22817EE1_163C_4834_9292_C50D4FB3313A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSecretKeyServerApp:
// See SecretKeyServer.cpp for the implementation of this class
//

class CSecretKeyServerApp : public CWinApp
{
public:
	CSecretKeyServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecretKeyServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSecretKeyServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECRETKEYSERVER_H__22817EE1_163C_4834_9292_C50D4FB3313A__INCLUDED_)
