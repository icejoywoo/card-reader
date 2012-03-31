// DataTransferToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "DataTransferToolDlg.h"
#include "DataTransfer.h"
#include "Utils.h"
#include "TemplateNameDialog.h"
#include "FieldConfigDialog.h"
#include "TransferingDialog.h"

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
	m_CurrentTemplate = _T("");
	m_InputFile = _T("");
	m_TargetFile = _T("");
	m_TemplateComment = _T("");
	m_SplitSize = 10000;
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
	DDX_Text(pDX, IDC_EDIT_CURRENT_TEMPLATE, m_CurrentTemplate);
	DDX_Text(pDX, IDC_EDIT_INPUT_FILE, m_InputFile);
	DDX_Text(pDX, IDC_EDIT_TARGET_FILE, m_TargetFile);
	DDX_Text(pDX, IDC_EDIT_TEMPLATE_COMMENT, m_TemplateComment);
	DDX_Text(pDX, IDC_EDIT_SPLIT_SIZE, m_SplitSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDataTransferToolDlg, CDialog)
	//{{AFX_MSG_MAP(CDataTransferToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START_TRANSFER, OnButtonStartTransfer)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_TEMPLATE, OnButtonApplyTemplate)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TEMPLATE, OnButtonDelTemplate)
	ON_BN_CLICKED(IDC_BUTTON_NEW_TEMPLATE, OnButtonNewTemplate)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS_TEMPLATE, OnButtonSaveAsTemplate)
	ON_BN_CLICKED(IDC_BUTTON_NEW_FIELD, OnButtonNewField)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_FIELD, OnButtonModifyField)
	ON_BN_CLICKED(IDC_BUTTON_DEL_FIELD, OnButtonDelField)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TEMPLATE1, OnButtonSaveTemplate)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_RENAME_TEMPLATE, OnButtonRenameTemplate)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_INPUT, OnButtonChooseInput)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_INPUT_DIR, OnButtonChooseInputDir)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_TARGETDIR, OnButtonChooseTargetdir)
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

	ShowInfor();
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

	/*
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
	*/
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
	this->SendMessage(WM_CLOSE);
}

void CDataTransferToolDlg::OnButtonStartTransfer() 
{
	// ��ʼת��
	UpdateData(TRUE);
	// �ж��Ƿ���дĿ���ļ�
	if (m_InputFile.IsEmpty())
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
	message.Format("ģ��: %s\nģ�屸ע: %s\n����·��: %s\n���·��: %s\n�Ƿ�ȷ�Ͽ�ʼת��?", m_CurrentTemplate, m_TemplateComment, m_InputFile, m_TargetFile);
	CWinThread* thread;
	if(MessageBox(message, "��Ϣȷ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		thread = ::AfxBeginThread(DataTransferThread, (LPVOID) this);
		// ��Ϊ�ȴ�״̬
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		(CButton*)GetDlgItem(IDC_BUTTON_START_TRANSFER)->EnableWindow(FALSE);

		CTransferingDialog dialog(this);
		dialog.Create(IDD_DIALOG_TRANSFERING, this);
		dialog.ShowWindow(SW_SHOWNORMAL);
		dialog.UpdateWindow();
		
		// �ȴ��������
		while (WAIT_OBJECT_0 == WaitForSingleObject(thread->m_hThread, INFINITE))
		{
			::Sleep(100);
		}		
		dialog.ShowWindow(SW_HIDE);
		AfxMessageBox("����ת�����!");
		// �ظ�Ϊ��׼״̬
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		(CButton*)GetDlgItem(IDC_BUTTON_START_TRANSFER)->EnableWindow(TRUE);
	}
    //this->SendMessage(WM_PAINT);
	UpdateData(FALSE);
	//this->SendMessage(WM_PAINT);
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

	m_TemplateComment = transfer.getTemplateComment();
	m_InputFile = transfer.inputPath;
	m_TargetFile = transfer.outputPath;

	ShowInfor();
	//this->SendMessage(WM_PAINT);
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
	ShowInfor();
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonNewTemplate() 
{
	// �½�ģ��
	m_FiledList.DeleteAllItems();
	transfer.ClearRules();
	ShowInfor();
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveAsTemplate() 
{
	// ���Ϊģ��
	UpdateData(TRUE);
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
			transfer.inputPath = m_InputFile;
			transfer.outputPath = m_TargetFile;
			transfer.save(m_NewTemplateName, m_TemplateComment);
			m_CurrentTemplate = m_NewTemplateName;
		}
		ShowInfor();
		//this->SendMessage(WM_PAINT);
	}
	UpdateData(FALSE);
}

void CDataTransferToolDlg::OnButtonNewField() 
{
	// �½��ֶ�
	int newItemNo = m_FiledList.GetItemCount(); // ��������
	CFieldConfigDialog dialog;
	if (IDOK == dialog.DoModal())
	{
		if (dialog.m_InsertLoc >= 0)
		{
			transfer.AddRule(m_TempRule, dialog.m_InsertLoc);
		}
		else
		{
			transfer.AddRule(m_TempRule);
		}
		
		ShowInfor();
	}
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonModifyField() 
{
	// �޸��ֶ�
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
			vector<TransferRule>::iterator loc = transfer.DelRule(rule); // ɾ��ԭ�е��ֶ�

			dialog.m_StartType = startType;
			dialog.m_StartData = startData;
			dialog.m_EndType = endType;
			dialog.m_EndData = endData;
			dialog.m_Tag = tag;
			if (IDOK == dialog.DoModal())
			{
				if (dialog.m_InsertLoc >= 0)
				{
					transfer.AddRule(m_TempRule, dialog.m_InsertLoc);
				}
				else
				{
					transfer.AddRule(m_TempRule, loc);
				}

				AfxMessageBox("�޸����, ����<����>������!");
				ShowInfor();
			}
			//this->SendMessage(WM_PAINT);
			break;
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
			char message[1024];
			sprintf(message, "�ֶ���ϢΪ: \n��ʼ����: %s\n��ʼ����: %s\n��������: %s\n��������: %s\n���: %s\nȷ��ɾ��?", 
				rule.GetStartType(), rule.GetStartData(), rule.GetEndType(), rule.GetEndData(), rule.GetTag());
			if(MessageBox(message, "������ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				transfer.DelRule(rule);
				m_FiledList.DeleteItem(i); // ɾ��GUI�ϵ���
				AfxMessageBox("�޸����, ����<����>������!");
			}
			break;
		}
	}
	ShowInfor();
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonSaveTemplate() 
{
	// ���浱ǰģ��
	UpdateData(TRUE);
	if (!m_CurrentTemplate.IsEmpty())
	{
		transfer.inputPath = m_InputFile;
		transfer.outputPath = m_TargetFile;
		transfer.save(m_CurrentTemplate, m_TemplateComment);
		AfxMessageBox("����ɹ�");
	}
	else
	{
		AfxMessageBox("���ȼ���ģ��!");
	}	
	ShowInfor();
	UpdateData(FALSE);
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonAbout() 
{
	CAboutDlg dialog;
	dialog.DoModal();
}


void CDataTransferToolDlg::OnClose() 
{
	// �ر�ǰ��ʾ����
	
	if (MessageBox("��ȷ�����˳�ǰ����ģ��, ȷ���˳�?", "�˳���ʾ",MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CDialog::OnClose();
	} 
}

int CDataTransferToolDlg::ShowInfor()
{
	int rs = 0;
	while (TRUE)
	{
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
		break;
	}
	return rs;
}

void CDataTransferToolDlg::OnButtonRenameTemplate() 
{
	UpdateData(TRUE);
	transfer.save(m_CurrentTemplate, m_TemplateComment);
	// ������ ����˳��: ɾ��ģ��, ����, ����
	CString chosenTemplate;

	for(int i=0; i<m_TemplateList.GetItemCount(); i++)
	{
		if(m_TemplateList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			chosenTemplate = m_TemplateList.GetItemText(i, 0);
		}
	}
	
	if (chosenTemplate.IsEmpty())
	{
		AfxMessageBox("����ѡ��ģ��!");
		return;
	}
	
	// ����ת������
	transfer.load(chosenTemplate);

	// ����ģ��
	CTemplateNameDialog dialog;
	dialog.DoModal();
	if (!m_NewTemplateName.IsEmpty())
	{
		transfer.del(chosenTemplate);
		transfer.inputPath = m_InputFile;
		transfer.outputPath = m_TargetFile;
		transfer.save(m_NewTemplateName, m_TemplateComment);
		m_CurrentTemplate = m_NewTemplateName;
	}
	
	// �ظ�ԭ�����ص�ģ��
	transfer.load(m_CurrentTemplate);
	UpdateData(FALSE);
	ShowInfor();
}

void CDataTransferToolDlg::OnButtonChooseInput() 
{
	// ���� ѡ���ļ�
	CFileDialog chooser(TRUE);
	chooser.DoModal();
	
	UpdateData(TRUE);
	m_InputFile = chooser.GetPathName();
	UpdateData(FALSE);
	ShowInfor();
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonChooseInputDir() 
{
	// ѡ��Ŀ���ļ�
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//��ʼ���ƶ���rootĿ¼�ܲ����ף�
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = "����ѡ��·��: ";
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
		m_InputFile = Buffer;
		UpdateData(FALSE);
	}
    
	//this->SendMessage(WM_PAINT);
}

void CDataTransferToolDlg::OnButtonChooseTargetdir() 
{
	// ѡ��Ŀ���ļ�
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;//��ʼ���ƶ���rootĿ¼�ܲ����ף�
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = "����ѡ��·��: ";
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
		m_TargetFile = Buffer;
		UpdateData(FALSE);
	}
    
	//this->SendMessage(WM_PAINT);
}
