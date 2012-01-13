// DataTransferToolDlg.h : header file
//

#if !defined(AFX_DATATRANSFERTOOLDLG_H__D31C02BB_95F4_4450_9505_AC977AB74745__INCLUDED_)
#define AFX_DATATRANSFERTOOLDLG_H__D31C02BB_95F4_4450_9505_AC977AB74745__INCLUDED_

#include "DataTransfer.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataTransferToolDlg dialog

class CDataTransferToolDlg : public CDialog
{
// Construction
public:
	CDataTransferToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDataTransferToolDlg)
	enum { IDD = IDD_DATATRANSFERTOOL_DIALOG };
	CButton	m_StartButton;
	CListCtrl	m_FiledList;
	CListCtrl	m_TemplateList;
	CString		m_TargetToTransfer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransferToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	DataTransfer transfer;

	// Generated message map functions
	//{{AFX_MSG(CDataTransferToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonChooseTargetFile();
	afx_msg void OnButtonChooseDir();
	afx_msg void OnButtonStartTransfer();
	afx_msg void OnButtonApplyTemplate();
	afx_msg void OnButtonDelTemplate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFERTOOLDLG_H__D31C02BB_95F4_4450_9505_AC977AB74745__INCLUDED_)
