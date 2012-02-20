#if !defined(AFX_FIELDCONFIGDIALOG_H__9A73F078_CE1D_416D_8551_8BE0F22F56AA__INCLUDED_)
#define AFX_FIELDCONFIGDIALOG_H__9A73F078_CE1D_416D_8551_8BE0F22F56AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FieldConfigDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFieldConfigDialog dialog

class CFieldConfigDialog : public CDialog
{
// Construction
public:
	CFieldConfigDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFieldConfigDialog)
	enum { IDD = IDD_DIALOG_FIELD_CONFIG };
	CString	m_EndType;
	CString	m_StartType;
	CString	m_EndData;
	CString	m_StartData;
	CString	m_Tag;
	int		m_InsertLoc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFieldConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFieldConfigDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIELDCONFIGDIALOG_H__9A73F078_CE1D_416D_8551_8BE0F22F56AA__INCLUDED_)
