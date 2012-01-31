// DataTransferTool.h : main header file for the DATATRANSFERTOOL application
//

#if !defined(AFX_DATATRANSFERTOOL_H__E18893F1_84B6_41F9_95AE_86C1CB42A7E6__INCLUDED_)
#define AFX_DATATRANSFERTOOL_H__E18893F1_84B6_41F9_95AE_86C1CB42A7E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataTransferToolApp:
// See DataTransferTool.cpp for the implementation of this class
//

class CDataTransferToolApp : public CWinApp
{
public:
	CDataTransferToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransferToolApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDataTransferToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFERTOOL_H__E18893F1_84B6_41F9_95AE_86C1CB42A7E6__INCLUDED_)
