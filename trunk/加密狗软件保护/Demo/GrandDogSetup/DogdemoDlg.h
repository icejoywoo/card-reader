// DogdemoDlg.h : header file
//

#if !defined(AFX_DOGDEMODLG_H__20C4CDB7_ECB8_408C_90FD_4A2C6A064CBB__INCLUDED_)
#define AFX_DOGDEMODLG_H__20C4CDB7_ECB8_408C_90FD_4A2C6A064CBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CDogdemoDlg dialog

class CDogdemoDlg : public CDialog
{
// Construction
public:
	CDogdemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDogdemoDlg)
	enum { IDD = IDD_DOGDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogdemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDogdemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheckVersion();
	afx_msg void OnButtonInstDriver();
	afx_msg void OnButtonUninstall();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGDEMODLG_H__20C4CDB7_ECB8_408C_90FD_4A2C6A064CBB__INCLUDED_)
