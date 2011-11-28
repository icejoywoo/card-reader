// CardReaderClient.h : main header file for the CARDREADERCLIENT application
//

#if !defined(AFX_CARDREADERCLIENT_H__4EFCA2B0_1BE3_431C_89A0_92BDD0A8D512__INCLUDED_)
#define AFX_CARDREADERCLIENT_H__4EFCA2B0_1BE3_431C_89A0_92BDD0A8D512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCardReaderClientApp:
// See CardReaderClient.cpp for the implementation of this class
//

class CCardReaderClientApp : public CWinApp
{
public:
	CCardReaderClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReaderClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCardReaderClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREADERCLIENT_H__4EFCA2B0_1BE3_431C_89A0_92BDD0A8D512__INCLUDED_)
