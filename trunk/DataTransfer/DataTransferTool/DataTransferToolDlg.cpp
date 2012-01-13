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
	// ��������, ��ʾ����ģ��
	m_TemplateList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	vector<CString> configs = transfer.getConfigs();
	int itemNo = 0;
	for (vector<CString>::iterator iter = configs.begin(); iter != configs.end(); ++iter)
	{
		m_TemplateList.InsertItem(itemNo++, *iter);
	}
	
	// ��ʾ�ֶ���Ϣ
	m_FiledList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_FiledList.InsertColumn(0, "��ʼ����", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(1, "��ʼ����", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(2, "��������", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(3, "��������", LVCFMT_LEFT, 100);
	m_FiledList.InsertColumn(4, "��ǩ��", LVCFMT_LEFT, 100);
	m_FiledList.InsertItem(0, "");
	m_FiledList.SetItemText(0, 1, "λ��");

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
	// �˳�
	exit(0);
}

void CDataTransferToolDlg::OnButtonChooseTargetFile() 
{
	// ѡ���ļ�
	CFileDialog chooser(TRUE);
	chooser.DoModal();

	UpdateData(TRUE);
	m_TargetToTransfer = chooser.GetPathName();
	UpdateData(FALSE);
}

void CDataTransferToolDlg::OnButtonChooseDir() 
{
	// ѡ��Ŀ���ļ�
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//��ʼ���ƶ���rootĿ¼�ܲ����ף�
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = "�޸Ľ���·��";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�
	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList,Buffer);
		//ȡ���ļ���·����Buffer��
		UpdateData(TRUE);
		m_TargetToTransfer = Buffer;
		UpdateData(FALSE);
	}
}

void CDataTransferToolDlg::OnButtonStartTransfer() 
{
	// ��ʼת��
	UpdateData(TRUE);
	AfxBeginThread(DataTransferThread, (LPVOID) &m_TargetToTransfer);
	UpdateData(FALSE);
	//(CButton*)GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
	//m_StartButton.EnableWindow(FALSE);
}

void CDataTransferToolDlg::OnButtonApplyTemplate() 
{
	// Ӧ��ģ��
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString str;
			str.Format(_T("ѡ���˵�%d��"), i);
			AfxMessageBox(str);
		}
	}
}

void CDataTransferToolDlg::OnButtonDelTemplate() 
{
	// ɾ��ģ��
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_TemplateList.DeleteItem(i); // ɾ��GUI�ϵ���
		}
   }
}
