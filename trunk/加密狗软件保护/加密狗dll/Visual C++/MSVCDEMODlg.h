// MSVCDEMODlg.h : header file
//

#if !defined(AFX_MSVCDEMODLG_H__556C0074_2ABE_44EE_BF66_972AFF6DA16F__INCLUDED_)
#define AFX_MSVCDEMODLG_H__556C0074_2ABE_44EE_BF66_972AFF6DA16F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMSVCDEMODlg dialog

class CMSVCDEMODlg : public CDialog
{
// Construction
public:
	char			m_cProductName[16];
	int				m_iDogIndex;
	unsigned long	m_ulCurrentDogHandle;
	unsigned long	m_ulDogHandleArray[32]; // We support 32 devices at most in one computer
	unsigned long	m_ulDogHandle2;
	unsigned long	m_ulOpenFlag;
	unsigned char	m_ucPasswordType;
	unsigned char	m_ucKeyType;
	bool			m_bCallOpenFirstInLocal;
	unsigned char	m_ucEncryptedData[16];

	CMSVCDEMODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMSVCDEMODlg)
	enum { IDD = IDD_MSVCDEMO_DIALOG };
	CString	m_strProductName;
	CString	m_strOpenFlag;
	CString	m_strPassword;
	CString	m_strUpgradeFilePath;
	int		m_iKeyIndex;
	int		m_iPasswordIndex;
	CString	m_strResult;
	int		m_sDirID;
	int		m_sFileID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSVCDEMODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMSVCDEMODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpenDog();
	afx_msg void OnButtonGetDogInfo();
	afx_msg void OnButtonCloseDog();
	afx_msg void OnButtonGetProductInfo();
	afx_msg void OnButtonVerifyPassword();
	afx_msg void OnButtonChangePassword();
	afx_msg void OnButtonSetKey();
	afx_msg void OnButtonSignData();
	afx_msg void OnButtonEncryptData();
	afx_msg void OnButtonConvertData();
	afx_msg void OnButtonDecryptData();
	afx_msg void OnButtonGetRandom();
	afx_msg void OnButtonCreateDir();
	afx_msg void OnButtonDeleteFile();
	afx_msg void OnButtonCreateFile();
	afx_msg void OnButtonDeleteDir();
	afx_msg void OnButtonReadFile();
	afx_msg void OnButtonVisitLicenseFile();
	afx_msg void OnButtonWriteFile();
	afx_msg void OnButtonDeflagFileSystem();
	afx_msg void OnButtonExecuteFile();
	afx_msg void OnButtonGetRequest();
	afx_msg void OnButtonBrowse();
	afx_msg void OnButtonUpgrade();
	afx_msg void OnSelchangeComboOpenFlag();
	afx_msg void OnRadioUser();
	afx_msg void OnRadioDeveloper();
	afx_msg void OnRadioSignKey();
	afx_msg void OnRadioEnDecryptKey();
	afx_msg void OnButtonCheckDog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetLicenseInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSVCDEMODLG_H__556C0074_2ABE_44EE_BF66_972AFF6DA16F__INCLUDED_)
// constant definition

//int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long FAR PASCAL MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL About(HWND, unsigned, WORD, LONG);
BOOL FAR PASCAL DemoDlg(HWND hDlg, unsigned message, WORD wParam, LONG lParam);

void OnDialogInit(HWND hDlg);
void CenterWindow(HWND hWnd);
