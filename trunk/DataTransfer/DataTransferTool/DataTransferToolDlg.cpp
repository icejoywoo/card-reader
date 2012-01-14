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

	m_TemplateList.InsertColumn(0, "ģ����", LVCFMT_LEFT, 200);

	m_FiledList.InsertColumn(0, "��ʼ����", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(1, "��ʼ����", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(2, "��������", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(3, "��������", LVCFMT_LEFT, 70);
	m_FiledList.InsertColumn(4, "��ǩ��", LVCFMT_LEFT, 100);

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

	// ��������, ��ʾ����ģ��

	m_TemplateList.DeleteAllItems();
	vector<CString> configs = transfer.getConfigs();

	int itemNo = 0;
	for (vector<CString>::iterator configIter = configs.begin(); configIter != configs.end(); ++configIter)
	{
		m_TemplateList.InsertItem(itemNo++, Convert(*configIter, CP_UTF8, CP_ACP));
	}
	
	// �����ֶ���Ϣ
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
	// �˳�
	if(MessageBox("ȷ���˳�?", "������ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		this->SendMessage(WM_CLOSE);
		//::PostMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}
}

void CDataTransferToolDlg::OnButtonChooseTargetFile() 
{
	// ѡ���ļ�
	CFileDialog chooser(TRUE);
	chooser.DoModal();

	UpdateData(TRUE);
	m_TargetToTransfer = chooser.GetPathName();
	UpdateData(FALSE);
	this->SendMessage(WM_PAINT);
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
	bi.lpszTitle = "������дĿ��·��: ";
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

	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonStartTransfer() 
{
	// ��ʼת��
	UpdateData(TRUE);
	// �ж��Ƿ���дĿ���ļ�
	if (m_TargetToTransfer.IsEmpty())
	{
		AfxMessageBox("������Ҫת�����ļ����ļ���!");
		return;
	}

	if (m_CurrentTemplate.IsEmpty())
	{
		AfxMessageBox("���ȼ���ģ��!");
		return;
	}

	CString message;
	message.Format("����ģ��: %s, �Ƿ�ȷ�Ͽ�ʼת��?", m_CurrentTemplate);
	if(MessageBox(message, "��Ϣȷ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
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
	// Ӧ��ģ��
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_CurrentTemplate = m_TemplateList.GetItemText(i, 0);
		}
	}

	if (m_CurrentTemplate.IsEmpty())
	{
		AfxMessageBox("����ѡ��ģ��!");
		return;
	}

	// ����ת������
	transfer.load(m_CurrentTemplate);
	// ��ʾ�ֶ���Ϣ
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
	// ɾ��ģ��
	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString configName = m_TemplateList.GetItemText(i, 0);
			if(MessageBox("ȷ��ɾ��?", "������ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				transfer.del(configName);
				m_TemplateList.DeleteItem(i); // ɾ��GUI�ϵ���
			}
			break;
		}
	}
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonNewTemplate() 
{
	// �½�ģ��
	m_FiledList.DeleteAllItems();
	transfer.ClearRules();
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveAsTemplate() 
{
	// ���Ϊģ��
	CTemplateNameDialog dialog;
	dialog.DoModal();
	if (m_FiledList.GetItemCount() == 0)
	{
		AfxMessageBox("�������ֶ�!");
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
	int newItemNo = m_FiledList.GetItemCount(); // ��������
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
			transfer.DelRule(rule); // ɾ��ԭ�е��ֶ�

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
	// ɾ���ֶ������е���ѡ��
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
			if(MessageBox("ȷ��ɾ��?", "������ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				transfer.DelRule(rule);
				//m_FiledList.DeleteItem(i); // ɾ��GUI�ϵ���
			}
			break;
		}
	}
	this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveTemplate() 
{
	// ���浱ǰģ��
	if (!m_CurrentTemplate.IsEmpty())
	{
		transfer.save(m_CurrentTemplate);
		AfxMessageBox("����ɹ�");
	}
	else
	{
		AfxMessageBox("���ȼ���ģ��!");
	}
	
	this->SendMessage(WM_PAINT);
}
