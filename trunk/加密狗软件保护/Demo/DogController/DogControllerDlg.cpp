// DogControllerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogController.h"
#include "DogControllerDlg.h"
#include "DogDriver.h"
#include "MingsenKey.h"
#include "GrandDogofDll.h"
#include "Base64.h"
#include "HardwareInfo.h"
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
// CDogControllerDlg dialog

CDogControllerDlg::CDogControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDogControllerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDogControllerDlg)
	m_ProductName = _T("GrandDog");
	m_DeveloperPassword = _T("abcdefgh");
	m_ContractDays = 30;
	m_UpdateFile = _T("mingsen.key");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDogControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDogControllerDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_ResultList);
	DDX_Text(pDX, IDC_EDIT_PRODUCT_NAME, m_ProductName);
	DDX_Text(pDX, IDC_EDIT_DEVELOPER_PASSWORD, m_DeveloperPassword);
	DDX_Text(pDX, IDC_EDIT_CONTRACT_DAYS, m_ContractDays);
	DDX_Text(pDX, IDC_EDIT_UPDATE_FILE, m_UpdateFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDogControllerDlg, CDialog)
	//{{AFX_MSG_MAP(CDogControllerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK_VERSION, OnButtonCheckVersion)
	ON_BN_CLICKED(IDC_BUTTON_INSTALL_DRIVER, OnButtonInstallDriver)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL_DRIVER, OnButtonUninstallDriver)
	ON_BN_CLICKED(IDC_BUTTON_START_INIT, OnButtonStartInit)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_UPDATE_FILE, OnButtonChooseUpdateFile)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDogControllerDlg message handlers

BOOL CDogControllerDlg::OnInitDialog()
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
	// ���� GrandDogSetup.dll
	HINSTANCE mlib;
	char Message[100];
	mlib = LoadLibrary(TEXT("GrandDogSetup.dll"));
	if(mlib != NULL)
	{
		//Get the interface function
		Install = (INSTALL)GetProcAddress(mlib, "Install");
		Uninstall = (UNINSTALL)GetProcAddress(mlib, "Uninstall");
		CheckVersion = (CHECKVERSION)GetProcAddress(mlib, "CheckVersion");
	}
	else
	{
		wsprintf (Message, "Load GrandDogSetup.dll failed.");
		AfxMessageBox(Message);
		exit(0);
	}

	// ����dll
	mlib = LoadLibrary(TEXT("RCGrandDogW32.dll"));
	if(mlib != NULL)
	{
		RC_OpenDog = (RC_OPENDOG)GetProcAddress(mlib, "rc_OpenDog");
		RC_CloseDog = (RC_CLOSEDOG)GetProcAddress(mlib, "rc_CloseDog");
		RC_CheckDog = (RC_CHECKDOG)GetProcAddress(mlib, "rc_CheckDog");
		RC_GetDogInfo = (RC_GETDOGINFO)GetProcAddress(mlib, "rc_GetDogInfo");
		RC_GetProductCurrentNo = (RC_GETPRODUCTCURRENTNO)GetProcAddress(mlib, "rc_GetProductCurrentNo");
		RC_VerifyPassword = (RC_VERIFYPASSWORD)GetProcAddress(mlib, "rc_VerifyPassword");
		RC_ChangePassword = (RC_CHANGEPASSWORD)GetProcAddress(mlib, "rc_ChangePassword");
		RC_Upgrade = (RC_UPGRADE)GetProcAddress(mlib, "rc_Upgrade");
		RC_GetRandom = (RC_GETRANDOM)GetProcAddress(mlib, "rc_GetRandom");
		RC_EncryptData = (RC_ENCRYPTDATA)GetProcAddress(mlib, "rc_EncryptData");
		RC_DecryptData = (RC_DECRYPTDATA)GetProcAddress(mlib, "rc_DecryptData");
		RC_ConvertData = (RC_CONVERTDATA)GetProcAddress(mlib, "rc_ConvertData");
		RC_SetKey = (RC_SETKEY)GetProcAddress(mlib, "rc_SetKey");
		RC_SignData = (RC_SIGNDATA)GetProcAddress(mlib, "rc_SignData");
		RC_ExecuteFile = (RC_EXECUTEFILE)GetProcAddress(mlib, "rc_ExecuteFile");
		RC_WriteFile = (RC_WRITEFILE)GetProcAddress(mlib, "rc_WriteFile");
		RC_VisitLicenseFile = (RC_VISITLICENSEFILE)GetProcAddress(mlib, "rc_VisitLicenseFile");
		RC_CreateFile = (RC_CREATEFILE)GetProcAddress(mlib, "rc_CreateFile");
		RC_DeleteFile = (RC_DELETEFILE)GetProcAddress(mlib, "rc_DeleteFile");
		RC_CreateDir = (RC_CREATEDIR)GetProcAddress(mlib, "rc_CreateDir");
		RC_DeleteDir = (RC_DELETEDIR)GetProcAddress(mlib, "rc_DeleteDir");
		RC_DefragFileSystem = (RC_DEFRAGFILESYSTEM)GetProcAddress(mlib, "rc_DefragFileSystem");
		RC_ReadFile = (RC_READFILE)GetProcAddress(mlib, "rc_ReadFile");
		RC_GetUpgradeRequestString = (RC_GETUPGRADEREQUESTSTRING)GetProcAddress(mlib, "rc_GetUpgradeRequestString");
		RC_GetLicenseInfo = (RC_GETLICENSEINFO)GetProcAddress(mlib, "rc_GetLicenseInfo");
	}
	else
	{
		wsprintf (Message, "Load RCGrandDogW32.dll failed.");
		AfxMessageBox(Message);
		exit(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDogControllerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDogControllerDlg::OnPaint() 
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
HCURSOR CDogControllerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ��������汾
void CDogControllerDlg::OnButtonCheckVersion() 
{
	int RetCode;
	char Message[1024]; // ��ϸ��Ϣ
	int		iUsbVerStatus;
	int		iParVerStatus;

	RetCode = CheckVersion(TRUE, &iUsbVerStatus, &iParVerStatus);
	if( 0 == RetCode )
	{
		if(iUsbVerStatus==0)
		{
			wsprintf (Message, "δ����GrandDog USB����.");
		}
		else if(iUsbVerStatus==1)
		{
			wsprintf (Message, "�����Ѱ�װ���°�.");
		}
		else if(iUsbVerStatus==2)
		{
			wsprintf (Message, "Find the older version of GrandDog USB driver.");
		}
		
		else if(iUsbVerStatus==3)
		{
			wsprintf (Message, "Find the newer version of GrandDog USB driver.");
		}
	}
	else
	{
		wsprintf (Message, "��ȡ����ʧ��. ������Ϊ0X%X",RetCode);
	}
	m_ResultList.AddString(Message);
}

// ��װ����
void CDogControllerDlg::OnButtonInstallDriver() 
{
	int RetCode;
	char Message[1024];

	wsprintf (Message, "���ڰ�װ����, ���Ժ� ...");
	m_ResultList.AddString(Message);
	RetCode = Install(INSTALL_ALL_DOG_DRVIER);
	
	if(RetCode)
	{
		if (RetCode == 0xA816200C)
		{
			wsprintf (Message, "��ʹ�ù���Ա��ݵ�¼.\r ������ = 0X%X",RetCode);
		}
		else
		{
			wsprintf (Message, "��װ����ʧ��.\r ������ = is 0X%X",RetCode);
		}
	}
	else
	{
		wsprintf (Message, "�����Ѿ���ɰ�װ.");
	}
	m_ResultList.AddString(Message);
}

// ж������
void CDogControllerDlg::OnButtonUninstallDriver() 
{
	int RetCode;
	char Message[1024];

	wsprintf (Message, "����ж������, ���Ժ� ...");
	m_ResultList.AddString(Message);

	RetCode = Uninstall(UNINSTALL_ALL_DOG_DRVIER);
	
	if(RetCode)
	{
		if (RetCode == 0xA816200C)
		{
			wsprintf (Message, "��ʹ�ù���Ա��ݵ�¼.\r ������ = 0X%X",RetCode);
		}
		else
		{
			wsprintf (Message, "ж������ʧ��.\r ������ = 0X%X",RetCode);
		}
	}
	else
	{
		wsprintf (Message, "�����Ѿ����ж��.");
	}
	m_ResultList.AddString(Message);
}

// ��ʼ��ʼ��
void CDogControllerDlg::OnButtonStartInit() 
{
	HRESULT retCode;
	ULONG DogHandle;
	CString strResult;
	retCode = RC_OpenDog(RC_OPEN_FIRST_IN_LOCAL, m_ProductName.GetBuffer(16), &DogHandle);

	if (retCode == S_OK)
	{
		strResult.Format("��Ӳ�����ɹ�, Ӳ�������Ϊ0X%X.", DogHandle);
		m_ResultList.AddString(strResult);
	} 
	else if (retCode == 0xA8160002L)
	{
		strResult.Format("��Ӳ����ʧ��, û�з���Ӳ����, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
	else if (retCode == 0xA8160001L)
	{
		strResult.Format("��Ӳ����ʧ��, û�з���������������װ����ȷ, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
	else
	{
		strResult.Format("��Ӳ����ʧ��, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	UCHAR ucDegree = 0;
	retCode = RC_VerifyPassword(DogHandle, RC_PASSWORDTYPE_DEVELOPER, m_DeveloperPassword.GetBuffer(512), &ucDegree);

	if (retCode == S_OK)
	{
		strResult.Format("����������У��ɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("����������У��ʧ��, ʣ��У�����: %d.", ucDegree);
		m_ResultList.AddString(strResult);
		return;
	}

	retCode = RC_CreateDir(DogHandle, 1, 256);
	if (retCode == S_OK)
	{
		strResult.Format("�����ļ��гɹ�.");
		m_ResultList.AddString(strResult);
	}
	else if (retCode == 0xA816000AL)
	{
		strResult.Format("�ļ����Ѿ�����");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("�����ļ���ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	retCode = RC_CreateFile(DogHandle, 1, 2, RC_TYPEFILE_DATA, 200);
	if (retCode == S_OK)
	{
		strResult.Format("�����ļ��ɹ�.");
		m_ResultList.AddString(strResult);
	}
	else if (retCode == 0xA816000AL)
	{
		strResult.Format("�ļ��Ѿ�����");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("�����ļ�ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	char mac[6];
	GetMacAddress(mac); 

	ofstream out("request.key");
	out.write(mac, 6);
	out.flush();
	out.close();

	UCHAR buf[200]; // ���ļ���Сһ��
	UpdateData(TRUE);
	ULONG serial = 1;
	ULONG countMinutes = m_ContractDays * 20 * 60; // 20��Сʱ, 60����, �������ÿ������20Сʱ
	UpdateData(FALSE);

	memset(buf, 0, 200);
	memcpy(buf, &serial, sizeof(long));
	memcpy(&buf[4], &countMinutes, sizeof(long));
	memcpy(&buf[8], &mac, 6 * sizeof(char));
	retCode = RC_WriteFile(DogHandle, 1, 2, 0l, 200l, buf);
	if (retCode == S_OK)
	{
		strResult.Format("���ļ���д���ݳɹ�. ����Ϊ%ld, %ld, %s.", serial, countMinutes, mac);
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("���ļ���д����ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	retCode = RC_CloseDog(DogHandle);
	if (retCode == S_OK)
	{
		strResult.Format("�ر�Ӳ�����ɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("�ر�Ӳ����ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
	
}

void CDogControllerDlg::OnButtonChooseUpdateFile() 
{
	UpdateData(TRUE);
	CFileDialog filedlg (TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"All Files (*.*) | *.*||");
	if (filedlg.DoModal() == IDOK)
	{		
		m_UpdateFile = filedlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CDogControllerDlg::OnButtonUpdate() 
{
	// ��ȡ�����ļ�
	CStdioFile keyConfig(m_UpdateFile, CFile::modeRead);
	CString content;
	if (!keyConfig.ReadString(content)) 
	{
		CString message;
		message.Format("��ȡ�����ļ�[%s]����!", m_UpdateFile);
		AfxMessageBox(message);
		return;
	}

	HRESULT retCode;
	ULONG DogHandle;
	CString strResult;
	retCode = RC_OpenDog(RC_OPEN_FIRST_IN_LOCAL, m_ProductName.GetBuffer(16), &DogHandle);

	if (retCode == S_OK)
	{
		strResult.Format("��Ӳ�����ɹ�, Ӳ�������Ϊ0X%X.", DogHandle);
		m_ResultList.AddString(strResult);
	} 
	else if (retCode == 0xA8160002L)
	{
		strResult.Format("��Ӳ����ʧ��, û�з���Ӳ����, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
	else if (retCode == 0xA8160001L)
	{
		strResult.Format("��Ӳ����ʧ��, û�з���������������װ����ȷ, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
	else
	{
		strResult.Format("��Ӳ����ʧ��, ��������0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	UCHAR ucDegree = 0;
	retCode = RC_VerifyPassword(DogHandle, RC_PASSWORDTYPE_DEVELOPER, m_DeveloperPassword.GetBuffer(512), &ucDegree);

	if (retCode == S_OK)
	{
		strResult.Format("����������У��ɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("����������У��ʧ��, ʣ��У�����: %d.", ucDegree);
		m_ResultList.AddString(strResult);
		return;
	}
	
	string encodeStr((LPCSTR)content);
	ULONG count = 0; // ������
	ULONG serial = 0; // ���к�
	string decodedStr = Base64::decode(encodeStr);
	
	// 1|10000|08-00-27-00-F0-54
	// serial|count|mac
	string serialStr = decodedStr.substr(0, decodedStr.find_first_of("|"));
	decodedStr = decodedStr.substr(decodedStr.find_first_of("|") + 1);
	string countStr = decodedStr.substr(0, decodedStr.find_first_of("|"));
	decodedStr = decodedStr.substr(decodedStr.find_first_of("|") + 1);
	string mac = decodedStr.substr(decodedStr.find_first_of("|") + 1);

	serial = _ttol(serialStr.c_str()); // ���к�
	count = _ttol(countStr.c_str()); // ������

	char buf1[200];
	retCode = RC_ReadFile(DogHandle, 1, 2, 0l, 200l, (UCHAR*)buf1);
	if (retCode == S_OK)
	{
		strResult.Format("��ȡӲ�������ݳɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("��ȡӲ��������ʧ��.");
		m_ResultList.AddString(strResult);
		return;
	}
	long serialInDog;
	memcpy(&serialInDog, buf1, sizeof(long));
	long countInDog;
	memcpy(&countInDog, &buf1[4], sizeof(long));
	char macInDog[6];
	memcpy(&macInDog, &buf1[8], 6 * sizeof(char));
	macInDog[6] = '\0';

	if (serial != serialInDog + 1)
	{
		AfxMessageBox("�ø����ļ�����Ч!");
		return;
	}
	strResult.Format("Ӳ�����м�����Ϊ: %d.", countInDog);
	m_ResultList.AddString(strResult);
	
	if (strcmp(macInDog, mac.c_str()) != 0)
	{
		AfxMessageBox("�뱣֤���µĻ�������Ӳ����ƥ��Ļ����Ա�֤��������!");
		return;
	}

	UCHAR buf[200]; // ���ļ���Сһ��
	memset(buf, 0, 200);
	memcpy(buf, &serial, sizeof(long));
	memcpy(&buf[4], &count, sizeof(long));
	memcpy(&buf[8], &macInDog, strlen(macInDog)*sizeof(char));
	retCode = RC_WriteFile(DogHandle, 1, 2, 0l, 200l, buf);
	if (retCode == S_OK)
	{
		strResult.Format("���ļ���д���ݳɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("���ļ���д����ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}

	retCode = RC_CloseDog(DogHandle);
	if (retCode == S_OK)
	{
		strResult.Format("�ر�Ӳ�����ɹ�.");
		m_ResultList.AddString(strResult);
	}
	else
	{
		strResult.Format("�ر�Ӳ����ʧ��, ������: 0X%X.", retCode);
		m_ResultList.AddString(strResult);
		return;
	}
}
