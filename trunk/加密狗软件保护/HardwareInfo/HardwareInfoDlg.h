// HardwareInfoDlg.h : header file
//

#if !defined(AFX_HARDWAREINFODLG_H__F52A2C89_C043_11D3_BC14_0080C7249374__INCLUDED_)
#define AFX_HARDWAREINFODLG_H__F52A2C89_C043_11D3_BC14_0080C7249374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg dialog

class CHardwareInfoDlg : public CDialog
{
// Construction
public:
	CHardwareInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHardwareInfoDlg)
	enum { IDD = IDD_HARDWAREINFO_DIALOG };
	CString	m_strFuncKeyNumber;
	CString	m_strKeyboardType;
	CString	m_strPhysAvail;
	CString	m_strPhysTotal;
	CString	m_strProcessorNumber;
	CString	m_strVirtualAvail;
	CString	m_strVirtualTotal;
	CString	m_strPageSize;
	CString	m_strProcessorArchitecture;
	CString	m_strProcessorLevel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardwareInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CListCtrl m_listDrives;

	// Generated message map functions
	//{{AFX_MSG(CHardwareInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDWAREINFODLG_H__F52A2C89_C043_11D3_BC14_0080C7249374__INCLUDED_)
