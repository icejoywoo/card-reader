#if !defined(AFX_SERVERSETTING_H__6252E540_7B1A_449D_80F2_FB0403CC0A4E__INCLUDED_)
#define AFX_SERVERSETTING_H__6252E540_7B1A_449D_80F2_FB0403CC0A4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ServerSetting dialog

class ServerSetting : public CDialog
{
// Construction
public:
	ServerSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ServerSetting)
	enum { IDD = IDD_SERVERSETTING_DIALOG };
	CIPAddressCtrl	m_IP4;
	CIPAddressCtrl	m_IP3;
	CIPAddressCtrl	m_IP2;
	CIPAddressCtrl	m_IP1;
	int		m_Port;
	int		m_ReaderCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServerSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ServerSetting)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSETTING_H__6252E540_7B1A_449D_80F2_FB0403CC0A4E__INCLUDED_)
