// DogControllerDlg.h : header file
//

#if !defined(AFX_DOGCONTROLLERDLG_H__E3A3E230_58A4_4943_B0DE_2DBEF7266AD0__INCLUDED_)
#define AFX_DOGCONTROLLERDLG_H__E3A3E230_58A4_4943_B0DE_2DBEF7266AD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDogControllerDlg dialog

class CDogControllerDlg : public CDialog
{
// Construction
public:
	CDogControllerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDogControllerDlg)
	enum { IDD = IDD_DOGCONTROLLER_DIALOG };
	CListBox	m_ResultList;
	CString	m_ProductName;
	CString	m_DeveloperPassword;
	ULONG	m_ContractDays;
	CString	m_UpdateFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogControllerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDogControllerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheckVersion();
	afx_msg void OnButtonInstallDriver();
	afx_msg void OnButtonUninstallDriver();
	afx_msg void OnButtonStartInit();
	afx_msg void OnButtonChooseUpdateFile();
	afx_msg void OnButtonUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGCONTROLLERDLG_H__E3A3E230_58A4_4943_B0DE_2DBEF7266AD0__INCLUDED_)
