// DataTransfer.h : main header file for the DATATRANSFER application
//

#if !defined(AFX_DATATRANSFER_H__BF436057_D2AD_43D4_82A7_6861E915939F__INCLUDED_)
#define AFX_DATATRANSFER_H__BF436057_D2AD_43D4_82A7_6861E915939F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataTransferApp:
// See DataTransfer.cpp for the implementation of this class
//

class CDataTransferApp : public CWinApp
{
public:
	CDataTransferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDataTransferApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFER_H__BF436057_D2AD_43D4_82A7_6861E915939F__INCLUDED_)
