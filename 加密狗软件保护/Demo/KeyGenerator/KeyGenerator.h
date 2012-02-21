// KeyGenerator.h : main header file for the KEYGENERATOR application
//

#if !defined(AFX_KEYGENERATOR_H__1E76B9A4_EEA4_4A27_8BC0_77FC0874BA45__INCLUDED_)
#define AFX_KEYGENERATOR_H__1E76B9A4_EEA4_4A27_8BC0_77FC0874BA45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeyGeneratorApp:
// See KeyGenerator.cpp for the implementation of this class
//

class CKeyGeneratorApp : public CWinApp
{
public:
	CKeyGeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyGeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKeyGeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYGENERATOR_H__1E76B9A4_EEA4_4A27_8BC0_77FC0874BA45__INCLUDED_)
