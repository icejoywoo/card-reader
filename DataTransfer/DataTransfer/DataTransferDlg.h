// DataTransferDlg.h : header file
//

#if !defined(AFX_DATATRANSFERDLG_H__04AC6109_1399_4912_936F_A1A1534A38B5__INCLUDED_)
#define AFX_DATATRANSFERDLG_H__04AC6109_1399_4912_936F_A1A1534A38B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataTransferDlg dialog

class CDataTransferDlg : public CDialog
{
// Construction
public:
	CDataTransferDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDataTransferDlg)
	enum { IDD = IDD_DATATRANSFER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDataTransferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFERDLG_H__04AC6109_1399_4912_936F_A1A1534A38B5__INCLUDED_)
