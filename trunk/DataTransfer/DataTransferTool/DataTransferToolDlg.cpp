// DataTransferToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "DataTransferToolDlg.h"
#include "DataTransfer.h"
#include "Utils.h"

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
// CDataTransferToolDlg dialog

CDataTransferToolDlg::CDataTransferToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataTransferToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataTransferToolDlg)
	m_TargetToTransfer = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataTransferToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataTransferToolDlg)
	DDX_Control(pDX, IDC_BUTTON_START_TRANSFER, m_StartButton);
	DDX_Control(pDX, IDC_LIST_FIELD_TABLE, m_FiledList);
	DDX_Control(pDX, IDC_LIST_TEMPLATES, m_TemplateList);
	DDX_Text(pDX, IDC_EDIT_TARGET_FILE, m_TargetToTransfer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDataTransferToolDlg, CDialog)
	//{{AFX_MSG_MAP(CDataTransferToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_TARGET, OnButtonChooseTargetFile)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_DIR, OnButtonChooseDir)
	ON_BN_CLICKED(IDC_BUTTON_START_TRANSFER, OnButtonStartTransfer)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_TEMPLATE, OnButtonApplyTemplate)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TEMPLATE, OnButtonDelTemplate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTransferToolDlg message handlers

BOOL CDataTransferToolDlg::OnInitDialog()
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

void CDataTransferToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDataTransferToolDlg::OnPaint() 
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
	UpdateData(TRUE);
	// 更新数据, 显示已有模板
	m_TemplateList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	vector<CString> configs = transfer.getConfigs();
	int itemNo = 0;
	for (vector<CString>::iterator iter = configs.begin(); iter != configs.end(); ++iter)
	{
		m_TemplateList.InsertItem(itemNo++, *iter);
	}
	
	// 显示字段信息
	m_FiledList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_FiledList.InsertColumn(0, "起始类型", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(1, "起始数据", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(2, "结束类型", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(3, "结束数据", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(4, "标签名", LVCFMT_LEFT, 100);
	m_FiledList.InsertItem(0, "");
	m_FiledList.SetItemText(0, 1, "位置");

	UpdateData(FALSE);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataTransferToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDataTransferToolDlg::OnButtonExit() 
{
	// 退出
	exit(0);
}

void CDataTransferToolDlg::OnButtonChooseTargetFile() 
{
	// 选择文件
	CFileDialog chooser(TRUE);
	chooser.DoModal();

	UpdateData(TRUE);
	m_TargetToTransfer = chooser.GetPathName();
	UpdateData(FALSE);
}

void CDataTransferToolDlg::OnButtonChooseDir() 
{
	// 选择目标文件
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//初始化制定的root目录很不容易，
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "修改接收路径";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件
	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList,Buffer);
		//取得文件夹路径到Buffer里
		UpdateData(TRUE);
		m_TargetToTransfer = Buffer;
		UpdateData(FALSE);
	}
}

void CDataTransferToolDlg::OnButtonStartTransfer() 
{
	// 开始转换
	UpdateData(TRUE);
	AfxBeginThread(DataTransferThread, (LPVOID) &m_TargetToTransfer);
	UpdateData(FALSE);
	//(CButton*)GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
	//m_StartButton.EnableWindow(FALSE);
}

void CDataTransferToolDlg::OnButtonApplyTemplate() 
{
	// 应用模板
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString str;
			str.Format(_T("选中了第%d行"), i);
			AfxMessageBox(str);
		}
	}
}

void CDataTransferToolDlg::OnButtonDelTemplate() 
{
	// 删除模板
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_TemplateList.DeleteItem(i); // 删除GUI上的项
		}
   }
}
