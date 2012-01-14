// DataTransferToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "DataTransferToolDlg.h"
#include "DataTransfer.h"
#include "Utils.h"
#include "TemplateNameDialog.h"
#include "FieldConfigDialog.h"

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
	m_CurrentTemplate = _T("");
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
	DDX_Text(pDX, IDC_EDIT_CURRENT_TEMPLATE, m_CurrentTemplate);
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
	ON_BN_CLICKED(IDC_BUTTON_NEW_TEMPLATE, OnButtonNewTemplate)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS_TEMPLATE, OnButtonSaveAsTemplate)
	ON_BN_CLICKED(IDC_BUTTON_NEW_FIELD, OnButtonNewField)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_FIELD, OnButtonModifyField)
	ON_BN_CLICKED(IDC_BUTTON_DEL_FIELD, OnButtonDelField)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TEMPLATE1, OnButtonSaveTemplate)
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
	m_TemplateList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
 	m_FiledList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_TemplateList.InsertColumn(0, "模板名", LVCFMT_LEFT, 200);

	m_FiledList.InsertColumn(0, "起始类型", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(1, "起始数据", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(2, "结束类型", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(3, "结束数据", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(4, "标签名", LVCFMT_LEFT, 100);

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

	// 更新数据, 显示已有模板

	m_TemplateList.DeleteAllItems();
	vector<CString> configs = transfer.getConfigs();

	int itemNo = 0;
	for (vector<CString>::iterator configIter = configs.begin(); configIter != configs.end(); ++configIter)
	{
		m_TemplateList.InsertItem(itemNo++, Convert(*configIter, CP_UTF8, CP_ACP));
	}
	
	// 更新字段信息
	m_FiledList.DeleteAllItems();
	
	CString lineTitle;
	vector<TransferRule> rules = transfer.getRules();
	itemNo = 0;
	for (vector<TransferRule>::iterator ruleIter = rules.begin();
		ruleIter != rules.end(); ++ruleIter, ++itemNo)
	{
		TransferRule rule = (*ruleIter);
		m_FiledList.InsertItem(itemNo, "");
		m_FiledList.SetItemText(itemNo, 0, rule.GetStartType());
		m_FiledList.SetItemText(itemNo, 1, rule.GetStartData());
		m_FiledList.SetItemText(itemNo, 2, rule.GetEndType());
		m_FiledList.SetItemText(itemNo, 3, rule.GetEndData());
		m_FiledList.SetItemText(itemNo, 4, rule.GetTag());
	}
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
	if(MessageBox("确认退出?", "操作提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		this->SendMessage(WM_CLOSE);
		//::PostMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}
}

void CDataTransferToolDlg::OnButtonChooseTargetFile() 
{
	// 选择文件
	CFileDialog chooser(TRUE);
	chooser.DoModal();

	UpdateData(TRUE);
	m_TargetToTransfer = chooser.GetPathName();
	UpdateData(FALSE);
	this->SendMessage(WM_PAINT);
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
	bi.lpszTitle = "请您填写目标路径: ";
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

	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonStartTransfer() 
{
	// 开始转换
	UpdateData(TRUE);
	// 判断是否填写目标文件
	if (m_TargetToTransfer.IsEmpty())
	{
		AfxMessageBox("请输入要转换的文件或文件夹!");
		return;
	}

	if (m_CurrentTemplate.IsEmpty())
	{
		AfxMessageBox("请先加载模板!");
		return;
	}

	CString message;
	message.Format("加载模板: %s, 是否确认开始转换?", m_CurrentTemplate);
	if(MessageBox(message, "信息确认", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		AfxBeginThread(DataTransferThread, (LPVOID) &m_TargetToTransfer);
	}

//	this->SendMessage(WM_PAINT);
	UpdateData(FALSE);
	//(CButton*)GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
	//m_StartButton.EnableWindow(FALSE);
}

void CDataTransferToolDlg::OnButtonApplyTemplate() 
{
	UpdateData(TRUE);
	// 应用模板
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_CurrentTemplate = m_TemplateList.GetItemText(i, 0);
		}
	}

	if (m_CurrentTemplate.IsEmpty())
	{
		AfxMessageBox("请先选择模板!");
		return;
	}

	// 加载转换配置
	transfer.load(m_CurrentTemplate);
	// 显示字段信息
	m_FiledList.DeleteAllItems();
	
	CString lineTitle;
	vector<TransferRule> rules = transfer.getRules();
	int itemNo = 0;
	for (vector<TransferRule>::iterator ruleIter = rules.begin();
	ruleIter != rules.end(); ++ruleIter, ++itemNo)
	{
		TransferRule rule = (*ruleIter);
		m_FiledList.InsertItem(itemNo, "");
		m_FiledList.SetItemText(itemNo, 0, rule.GetStartType());
		m_FiledList.SetItemText(itemNo, 1, rule.GetStartData());
		m_FiledList.SetItemText(itemNo, 2, rule.GetEndType());
		m_FiledList.SetItemText(itemNo, 3, rule.GetEndData());
		m_FiledList.SetItemText(itemNo, 4, rule.GetTag());
	}
	this->SendMessage(WM_PAINT);
	UpdateData(FALSE);
}

void CDataTransferToolDlg::OnButtonDelTemplate() 
{
	// 删除模板
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString configName = m_TemplateList.GetItemText(i, 0);
			if(MessageBox("确认删除?", "操作提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				transfer.del(configName);
				m_TemplateList.DeleteItem(i); // 删除GUI上的项
			}
			break;
		}
	}
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonNewTemplate() 
{
	// 新建模板
	m_FiledList.DeleteAllItems();
	transfer.ClearRules();
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveAsTemplate() 
{
	// 另存为模板
	CTemplateNameDialog dialog;
	dialog.DoModal();
	if (m_FiledList.GetItemCount() == 0)
	{
		AfxMessageBox("请配置字段!");
	} 
	else
	{
		transfer.ClearRules();
		for(int i = 0; i < m_FiledList.GetItemCount(); ++i)
		{
			TransferRule rule;
			CString startType = m_FiledList.GetItemText(i, 0);
			CString startData = m_FiledList.GetItemText(i, 1);
			CString endType = m_FiledList.GetItemText(i, 2);
			CString endData = m_FiledList.GetItemText(i, 3);
			CString tag = m_FiledList.GetItemText(i, 4);
			rule.SetStart(startType, startData);
			rule.SetEnd(endType, endData);
			rule.SetTag(tag);
			transfer.AddRule(rule);
		}

		if (!m_NewTemplateName.IsEmpty())
		{
			transfer.save(m_NewTemplateName);
			m_CurrentTemplate = m_NewTemplateName;
		}

		this->SendMessage(WM_PAINT);
	}
	
}

void CDataTransferToolDlg::OnButtonNewField() 
{
	// TODO: Add your control notification handler code here
	int newItemNo = m_FiledList.GetItemCount(); // 在最后插入
	CFieldConfigDialog dialog;
	dialog.DoModal();
	transfer.AddRule(m_TempRule);
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonModifyField() 
{
	// TODO: Add your control notification handler code here
	CFieldConfigDialog dialog;
	
	for(int i=0; i<m_FiledList.GetItemCount(); i++)
	{
		if(m_FiledList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			TransferRule rule;
			CString startType = m_FiledList.GetItemText(i, 0);
			CString startData = m_FiledList.GetItemText(i, 1);
			CString endType = m_FiledList.GetItemText(i, 2);
			CString endData = m_FiledList.GetItemText(i, 3);
			CString tag = m_FiledList.GetItemText(i, 4);
			rule.SetStart(startType, startData);
			rule.SetEnd(endType, endData);
			rule.SetTag(tag);
			transfer.DelRule(rule); // 删除原有的字段

			dialog.m_StartType = startType;
			dialog.m_StartData = startData;
			dialog.m_EndType = endType;
			dialog.m_EndData = endData;
			dialog.m_Tag = tag;
			dialog.DoModal();
			transfer.AddRule(m_TempRule);
			this->SendMessage(WM_PAINT);
		}
	}
	
}

void CDataTransferToolDlg::OnButtonDelField() 
{
	// 删除字段配置中的所选行
	for(int i=0; i<m_FiledList.GetItemCount(); i++)
	{
		if(m_FiledList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			TransferRule rule;
			CString startType = m_FiledList.GetItemText(i, 0);
			CString startData = m_FiledList.GetItemText(i, 1);
			CString endType = m_FiledList.GetItemText(i, 2);
			CString endData = m_FiledList.GetItemText(i, 3);
			CString tag = m_FiledList.GetItemText(i, 4);
			rule.SetStart(startType, startData);
			rule.SetEnd(endType, endData);
			rule.SetTag(tag);
			if(MessageBox("确认删除?", "操作提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				transfer.DelRule(rule);
				//m_FiledList.DeleteItem(i); // 删除GUI上的项
			}
			break;
		}
	}
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveTemplate() 
{
	// 保存当前模板
	if (!m_CurrentTemplate.IsEmpty())
	{
		transfer.save(m_CurrentTemplate);
		AfxMessageBox("保存成功");
	}
	else
	{
		AfxMessageBox("请先加载模板!");
	}
	
	this->SendMessage(WM_PAINT);
}
