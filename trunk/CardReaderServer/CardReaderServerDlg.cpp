// CardReaderServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CardReaderServer.h"
#include "CardReaderServerDlg.h"
#include "ServerSetting.h"
#include "ServerUtils.h"
#include "CustomMessage.h"
#include <set>
#include <list>
#include <map>

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
// CCardReaderServerDlg dialog

CCardReaderServerDlg::CCardReaderServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardReaderServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardReaderServerDlg)
	m_errors = 0;
	m_warns = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardReaderServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardReaderServerDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_logWindow);
	DDX_Control(pDX, IDC_TREE_CLIENTS, m_Tree);
	DDX_Text(pDX, IDC_EDIT_ERRORS, m_errors);
	DDX_Text(pDX, IDC_EDIT_WARNS, m_warns);
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
	ON_MESSAGE(LOG_UPDATE_MSG, updateLog)
	ON_WM_DESTROY()
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
	
	

	// Ϊ�����ͼ��
// 	CImageList cImageList;
// 	cImageList.Create(16, 16,  ILC_COLOR32| ILC_MASK, 1, 2);
// 	HICON hIcon= ::AfxGetApp()->LoadIcon(IDI_ICON_SERVERROOT);
// 	cImageList.Add(hIcon);
// 	m_Tree.SetImageList(&cImageList, TVSIL_NORMAL);
	m_Tree.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	HTREEITEM root = m_Tree.InsertItem(_T("server"));


	// ��¼��־���߳�
	m_logWindow.SetLimitText(500000);
	logThread = AfxBeginThread(logHandler, NULL);


	// ��ʼ�����ô���
	settingDlg = new ServerSetting(this);
	settingDlg->Create(IDD_SERVERSETTING_DIALOG);

	ServerParam::instance->mainFrame = this->GetSafeHwnd();

	// ��ʼ��������set

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

// TODO: ��ʼ��ť�ĵ����Ӧ
void CCardReaderServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	if (FALSE == Server::getInstance()->status)
	{
		if (Server::getInstance()->start() != 0)
		{
			AfxMessageBox("����ʧ��");
		}
	} else {
		AfxMessageBox("�������ѿ���");
	}
	
}

// TODO: ֹͣ��ť�ĵ����Ӧ
void CCardReaderServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if (TRUE == Server::getInstance()->status)
	{
		if (Server::getInstance()->stop() != 0)
		{
			AfxMessageBox("�ر�ʧ��");
		}
	} else {
		AfxMessageBox("������δ����");
	}
}

// TODO: ������ť�ĵ����Ӧ
void CCardReaderServerDlg::OnButtonRestart() 
{
	// TODO: Add your control notification handler code here
	if (TRUE == Server::getInstance()->status) 
	{
		if (Server::getInstance()->restart() != 0)
		{
			AfxMessageBox("����ʧ��");
		}
	} else {
		AfxMessageBox("������δ����");
	}
	
}

// TODO: �������ð�ť
void CCardReaderServerDlg::OnButtonSetting() 
{
	// TODO: Add your control notification handler code here
	
	settingDlg->ShowWindow(SW_SHOWNORMAL);
}

// TODO: ������հ�ť
void CCardReaderServerDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_logWindow.SetWindowText(""); // �����־����
}

// ��־button��Ӧ
void CCardReaderServerDlg::OnButtonLog() 
{
	// TODO: Add your control notification handler code here
	WinExec(CString("notepad ") + SimpleLog::GetlogFileLocation(), SW_SHOWNORMAL); // �ڼ��±������־�ļ�
}

LRESULT CCardReaderServerDlg::updateLog(WPARAM wparam,LPARAM lparam)
{
	if (this->m_logWindow.GetLineCount() >= 1000) // ����1000��,���һ��
	{
		this->m_logWindow.SetWindowText("");
	}
	int len = this->m_logWindow.GetWindowTextLength();
	this->m_logWindow.SetSel(len,len);
	this->m_logWindow.ReplaceSel(Server::getInstance()->log);

	WaitForSingleObject(SimpleLog::getMutex(), 100);
	//EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->log = "";
	Server::getInstance()->log.Empty();// �����־
	//LeaveCriticalSection(&(Server::getInstance()->g_cs));
	ReleaseMutex(SimpleLog::getMutex());
	
	// ��̬��ʾ�ͻ��˽ڵ�
	m_Tree.DeleteAllItems();
	HTREEITEM root = m_Tree.InsertItem(_T("server"));

	// ������ж�����
	map<int, HTREEITEM> readersTree;
	for (set<int>::iterator i = ServerParam::instance->readerIdSet.begin();
		i != ServerParam::instance->readerIdSet.end(); ++i)
	{
		readersTree[(*i)] = m_Tree.InsertItem(_T("������ " + i2str((*i))), root);
	}
	
	// ������пͻ��˵���Ӧ�������ڵ�
	for (list<Client*>::iterator iter = Server::getInstance()->clients.begin();
		iter != Server::getInstance()->clients.end(); ++iter)
	{
		char name[512];
		(*iter)->getName(name);
		m_Tree.InsertItem(_T(name), readersTree[(*iter)->getReaderId()]);
	}

	// չ�����нڵ�, ��������нڵ��Ժ���չ��
	m_Tree.Expand(root, TVE_EXPAND);
	for (map<int, HTREEITEM>::iterator miter = readersTree.begin();
		miter != readersTree.end(); ++miter)
	{
		m_Tree.Expand(miter->second, TVE_EXPAND);
	}

	// ������ʾͳ����Ϣ
	UpdateData(TRUE);
	m_errors = SimpleLog::getErrors();
	m_warns = SimpleLog::getWarns();
	UpdateData(FALSE);

	return 0;
}

BOOL CCardReaderServerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CCardReaderServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	delete settingDlg;
	::WaitForSingleObject(logThread, INFINITE);
	delete logThread;
//	_CrtDumpMemoryLeaks();
}