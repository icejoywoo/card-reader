// CardReaderClientDlg.h : header file
//

#if !defined(AFX_CARDREADERCLIENTDLG_H__158A8AD2_C76C_4E76_AA60_A40DB6B93F7F__INCLUDED_)
#define AFX_CARDREADERCLIENTDLG_H__158A8AD2_C76C_4E76_AA60_A40DB6B93F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCardReaderClientDlg dialog

class CCardReaderClientDlg : public CDialog
{
// Construction
public:
	CCardReaderClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCardReaderClientDlg)
	enum { IDD = IDD_CARDREADERCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReaderClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCardReaderClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREADERCLIENTDLG_H__158A8AD2_C76C_4E76_AA60_A40DB6B93F7F__INCLUDED_)
