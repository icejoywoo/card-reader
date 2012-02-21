// KeyGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyGenerator.h"
#include "KeyGeneratorDlg.h"
#include "Base64.h"

#include <string>
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyGeneratorDlg dialog

CKeyGeneratorDlg::CKeyGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyGeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyGeneratorDlg)
	m_RequestFile = _T(".//request.ini");
	m_Days = 30;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyGeneratorDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_ResultList);
	DDX_Text(pDX, IDC_EDIT_REQUEST_FILE, m_RequestFile);
	DDX_Text(pDX, IDC_EDIT_DAYS, m_Days);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyGeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FILE, OnButtonChooseFile)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_KEY, OnButtonGenerateKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyGeneratorDlg message handlers

BOOL CKeyGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyGeneratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyGeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeyGeneratorDlg::OnButtonChooseFile() 
{
	// 选择文件
	CFileDialog chooser(TRUE);
	chooser.DoModal();
	
	UpdateData(TRUE);
	m_RequestFile = chooser.GetPathName();
	UpdateData(FALSE);
}

void CKeyGeneratorDlg::OnButtonGenerateKey() 
{
	UpdateData(TRUE);
	CString strResult;

	// 读取配置文件的mac地址
	char mac[7];
	//GetMacAddress(mac);
	GetPrivateProfileString("request", "mac", "", mac, 7, m_RequestFile);
	mac[6] = '\0';
	
	DogInformation dogInfo;
	dogInfo.mac = new char(12);
	strcpy(dogInfo.mac, mac);
	
	char message[1024];
	dogInfo.serial = GetPrivateProfileInt("request", "serial", 1, m_RequestFile) + 1;
	dogInfo.count = 20 * 60 * m_Days;
	sprintf(message, "%ld|%ld|%s", dogInfo.serial, dogInfo.count, dogInfo.mac);
	strResult.Format("写入信息: %s", message);
	m_ResultList.AddString(strResult);

	string encodeStr = Base64::encode(string(message));
	strResult.Format("加密后信息: %s", encodeStr.c_str());
	m_ResultList.AddString(strResult);
	
	ofstream out("mingsen.key");
	out.write(encodeStr.c_str(), encodeStr.size());
	out.flush();
	out.close();
	strResult.Format("写入文件 mingsen.key");
	m_ResultList.AddString(strResult);
	
	string decodeStr = Base64::decode(encodeStr);
	strResult.Format("解密后信息: %s", decodeStr.c_str());
	m_ResultList.AddString(strResult);

	UpdateData(FALSE);
	m_ResultList.AddString("key生成完毕, 保存到程序所在目录下mingsen.key!");
}
