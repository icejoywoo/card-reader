#if !defined(AFX_TEMPLATENAMEDIALOG_H__DECD7A14_6849_40F7_960C_CA150706C63B__INCLUDED_)
#define AFX_TEMPLATENAMEDIALOG_H__DECD7A14_6849_40F7_960C_CA150706C63B__INCLUDED_

#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TemplateNameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDialog dialog

class CTemplateNameDialog : public CDialog
{
// Construction
public:
	CTemplateNameDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplateNameDialog)
	enum { IDD = IDD_DIALOG_TEMPLATE_NAME };
	CString	m_TemplateName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateNameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemplateNameDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATENAMEDIALOG_H__DECD7A14_6849_40F7_960C_CA150706C63B__INCLUDED_)
