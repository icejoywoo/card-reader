#if !defined(AFX_TRANSFERINGDIALOG_H__7FCCB211_211D_48AF_9FDE_92104039DA44__INCLUDED_)
#define AFX_TRANSFERINGDIALOG_H__7FCCB211_211D_48AF_9FDE_92104039DA44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransferingDialog dialog

class CTransferingDialog : public CDialog
{
// Construction
public:
	CTransferingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransferingDialog)
	enum { IDD = IDD_DIALOG_TRANSFERING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransferingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransferingDialog)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFERINGDIALOG_H__7FCCB211_211D_48AF_9FDE_92104039DA44__INCLUDED_)
