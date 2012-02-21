// KeyGeneratorDlg.h : header file
//

#if !defined(AFX_KEYGENERATORDLG_H__3BAE522D_7E08_46BC_AA15_4A6E45709680__INCLUDED_)
#define AFX_KEYGENERATORDLG_H__3BAE522D_7E08_46BC_AA15_4A6E45709680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _DogInformation
{
	unsigned long serial;
	unsigned long count;
	char* mac;
} DogInformation, *PDogInformation;

/////////////////////////////////////////////////////////////////////////////
// CKeyGeneratorDlg dialog

class CKeyGeneratorDlg : public CDialog
{
// Construction
public:
	CKeyGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyGeneratorDlg)
	enum { IDD = IDD_KEYGENERATOR_DIALOG };
	CListBox	m_ResultList;
	CString	m_RequestFile;
	long	m_Days;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyGeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeyGeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonChooseFile();
	afx_msg void OnButtonGenerateKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYGENERATORDLG_H__3BAE522D_7E08_46BC_AA15_4A6E45709680__INCLUDED_)
