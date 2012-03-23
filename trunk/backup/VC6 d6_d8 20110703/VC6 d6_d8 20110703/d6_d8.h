// d6_d8.h : main header file for the D6_D8 DLL
//

#if !defined(AFX_D6_D8_H__3E7D3C56_4D24_46CC_BEC1_FAE4E374C2B3__INCLUDED_)
#define AFX_D6_D8_H__3E7D3C56_4D24_46CC_BEC1_FAE4E374C2B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "D6touch.h"
#include "D8Cap.h"

#define BUFSIZE MAX_PATH
/////////////////////////////////////////////////////////////////////////////
// CD6_d8App
// See d6_d8.cpp for the implementation of this class
//

class CD6_d8App : public CWinApp
{
public:
	CD6_d8App();
	virtual BOOL InitInstance();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD6_d8App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CD6_d8App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

enum erro_info{Load_D8_dll_error,Can_not_find_ini_file,setup_ini_file_error};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_D6_D8_H__3E7D3C56_4D24_46CC_BEC1_FAE4E374C2B3__INCLUDED_)
