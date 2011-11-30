// CardReaderServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CardReaderServer.h"
#include "CardReaderServerDlg.h"
#include "ServerSetting.h"

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
// CCardReaderServerDlg dialog

CCardReaderServerDlg::CCardReaderServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardReaderServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardReaderServerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// 初始化设置窗口
	settingDlg = new ServerSetting(this);
	settingDlg->Create(IDD_SERVERSETTING_DIALOG);
}

void CCardReaderServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardReaderServerDlg)
	DDX_Control(pDX, IDC_TREE_VIEW, m_Tree);
	DDX_Control(pDX, IDC_EDIT_LOG, m_logWindow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCardReaderServerDlg, CDialog)
	//{{AFX_MSG_MAP(CCardReaderServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, OnButtonRestart)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnButtonLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardReaderServerDlg message handlers

BOOL CCardReaderServerDlg::OnInitDialog()
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

void CCardReaderServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCardReaderServerDlg::OnPaint() 
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
HCURSOR CCardReaderServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// TODO: 开始按钮的点击响应
void CCardReaderServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	if (Server::getInstance()->start() != 0)
	{
		AfxMessageBox("开启失败");
		appendTextToEdit(m_logWindow, CString("服务器开启失败\n"));
	} else {
		appendTextToEdit(m_logWindow, CString("服务器已开启, 端口") + i2str(Server::getInstance()->getPort()) + "\n");
	}
}

// TODO: 停止按钮的点击响应
void CCardReaderServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if (Server::getInstance()->stop() != 0)
	{
		AfxMessageBox("关闭失败");
		appendTextToEdit(m_logWindow, CString("服务器关闭失败\n"));
	} else {
		appendTextToEdit(m_logWindow, CString("服务器已关闭\n"));
	}
	
}

// TODO: 重启按钮的点击响应
void CCardReaderServerDlg::OnButtonRestart() 
{
	// TODO: Add your control notification handler code here
	if (Server::getInstance()->restart() != 0)
	{
		AfxMessageBox("重启失败");
		appendTextToEdit(m_logWindow, CString("服务器重启失败\n"));
	} else {
		appendTextToEdit(m_logWindow, CString("服务器已重启, 端口") + i2str(Server::getInstance()->getPort()) + "\n");
	}
}

// TODO: 单击设置按钮
void CCardReaderServerDlg::OnButtonSetting() 
{
	// TODO: Add your control notification handler code here
	
	settingDlg->ShowWindow(SW_SHOWNA);
}

// TODO: 单击清空按钮
void CCardReaderServerDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_logWindow.SetWindowText(""); // 清空日志窗口
}

void CCardReaderServerDlg::OnButtonLog() 
{
	// TODO: Add your control notification handler code here
	WinExec(CString("notepad ") + SimpleLog::GetlogFileLocation(), SW_SHOWNORMAL);
}
