// SecretKeyServerDlg.h : header file
//

#if !defined(AFX_SECRETKEYSERVERDLG_H__0C4073C8_4B48_4B77_A59A_38F7D2882C5E__INCLUDED_)
#define AFX_SECRETKEYSERVERDLG_H__0C4073C8_4B48_4B77_A59A_38F7D2882C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSecretKeyServerDlg dialog

class CSecretKeyServerDlg : public CDialog
{
// Construction
public:
	CSecretKeyServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSecretKeyServerDlg)
	enum { IDD = IDD_SECRETKEYSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecretKeyServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSecretKeyServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECRETKEYSERVERDLG_H__0C4073C8_4B48_4B77_A59A_38F7D2882C5E__INCLUDED_)
