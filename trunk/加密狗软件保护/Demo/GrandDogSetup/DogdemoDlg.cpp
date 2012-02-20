// DogdemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dogdemo.h"
#include "DogdemoDlg.h"
#include "dogdriver.h"		//interface function define head file

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//define the interface function pointer
CHECKVERSION	CheckVersion;
INSTALL			Install;
UNINSTALL		Uninstall;
HINSTANCE			mlib;

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
// CDogdemoDlg dialog

CDogdemoDlg::CDogdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDogdemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDogdemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDogdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDogdemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDogdemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDogdemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK_VERSION, OnButtonCheckVersion)
	ON_BN_CLICKED(IDC_BUTTON_INSTALL, OnButtonInstDriver)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL, OnButtonUninstall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDogdemoDlg message handlers

BOOL CDogdemoDlg::OnInitDialog()
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

	char Message[100];
	//Get the handle of GrandDogSetup.dll
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
		MessageBox(Message);
		exit(0);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDogdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDogdemoDlg::OnPaint() 
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
HCURSOR CDogdemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDogdemoDlg::OnButtonCheckVersion() 
{
	// TODO: Add your control notification handler code here
	int RetCode;
	char Message[100];
	WPARAM wParam=0;
	LPARAM lParam=0;
	int		iUsbVerStatus;
	int		iParVerStatus;


	//CheckVersion is used to obtain the driver's information in current computer
	RetCode = CheckVersion(TRUE,&iUsbVerStatus,&iParVerStatus);
	if( 0 == RetCode )
	{
		if(iUsbVerStatus==0)
		{
			wsprintf (Message, "Check Version succeeded! Not find the GrandDog USB driver.");
		}
		else if(iUsbVerStatus==1)
		{
			wsprintf (Message, "Check Version succeeded! Find the same version of GrandDog USB driver.");
		}
		else if(iUsbVerStatus==2)
		{
			wsprintf (Message, "Check Version succeeded! Find the older version of GrandDog USB driver.");
		}

		else if(iUsbVerStatus==3)
		{
			wsprintf (Message, "Check Version succeeded! Find the newer version of GrandDog USB driver.");
		}


		SetDlgItemText(IDC_STATIC_RESULT,Message);
	}
	else
	{
		wsprintf (Message, "Get driver failed. The return code is 0X%X",RetCode);
		SetDlgItemText(IDC_STATIC_RESULT,Message);
	}
}


void CDogdemoDlg::OnButtonInstDriver() 
{
	// TODO: Add your control notification handler code here
	int RetCode;
	char Message[100];
	WPARAM wParam=0;
	LPARAM lParam=0;

	
	GetDlgItem(IDC_BUTTON_INSTALL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BUTTON_UNINSTALL)->EnableWindow(FALSE); 
	
	GetDlgItem(IDC_BUTTON_CHECK_VERSION)->EnableWindow(FALSE); 
	
	
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE); 

	
	wsprintf (Message, "               Please wait ...");
	SetDlgItemText(IDC_STATIC_RESULT,Message);

	//if you want only install the USB driver or Paralle driver ,you can use other Macro.
	//for example 
	//INSTALL_ONLY_USB_DOG_DRVIER
	//INSTALL_ONLY_PARALLEL_DOG_DRVIER

	//InstDriver is used to install driver when you don't want to display the installation's interface
	RetCode = Install(INSTALL_ALL_DOG_DRVIER);

	if(RetCode)
	{
		if (RetCode == 0xA816200C)
		{
			wsprintf (Message, "Please log on with administrator identify.\r error code = 0X%X",RetCode);
			SetDlgItemText(IDC_STATIC_RESULT,Message);
		}
		else
		{

			wsprintf (Message, "Install driver failed.\r error code = is 0X%X",RetCode);
			SetDlgItemText(IDC_STATIC_RESULT,Message);
		}
		GetDlgItem(IDC_BUTTON_INSTALL)->EnableWindow(TRUE);
	}
	else
	{
		wsprintf (Message, " The driver has been installed successfully.");
		SetDlgItemText(IDC_STATIC_RESULT,Message);
		GetDlgItem(IDC_BUTTON_INSTALL)->EnableWindow(FALSE);
		
	}
	GetDlgItem(IDC_BUTTON_UNINSTALL)->EnableWindow(TRUE); 
	GetDlgItem(IDC_BUTTON_CHECK_VERSION)->EnableWindow(TRUE); 
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE); 

}

void CDogdemoDlg::OnButtonUninstall() 
{
	// TODO: Add your control notification handler code here
	int RetCode;
	char Message[100];
	WPARAM wParam=0;
	LPARAM lParam=0;

	GetDlgItem(IDC_BUTTON_INSTALL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BUTTON_UNINSTALL)->EnableWindow(FALSE); 
	
	GetDlgItem(IDC_BUTTON_CHECK_VERSION)->EnableWindow(FALSE); 
	
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE); 
	

	
	
	wsprintf (Message, "                    Please wait ...");
	SetDlgItemText(IDC_STATIC_RESULT,Message);

	//if you want only uninstall the USB driver or Paralle driver ,you can use other Macro.
	//for example 
	//UNINSTALL_ONLY_USB_DOG_DRVIER
	//UNINSTALL_ONLY_PARALLEL_DOG_DRVIER

	//UninstallDriver is used to uninstall driver when you don't want to display the uninstallation's interface
	RetCode = Uninstall(UNINSTALL_ALL_DOG_DRVIER);

	if(RetCode)
	{
		if (RetCode == 0xA816200C)
		{
			wsprintf (Message, "Please log on with administrator identify.\r error code = 0X%X",RetCode);
			SetDlgItemText(IDC_STATIC_RESULT,Message);
		}
		else
		{
			wsprintf (Message, "Uninstall driver failed.\r error code = is 0X%X",RetCode);
			SetDlgItemText(IDC_STATIC_RESULT,Message);
		}
	}
	else
	{
		wsprintf (Message, " The driver has been uninstalled successfully.");
		SetDlgItemText(IDC_STATIC_RESULT,Message);
	}


	GetDlgItem(IDC_BUTTON_INSTALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CHECK_VERSION)->EnableWindow(TRUE); 
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE); 
	if(RetCode!=0)
	{
		GetDlgItem(IDC_BUTTON_UNINSTALL)->EnableWindow(TRUE); 
	}
}

void CDogdemoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(mlib != NULL)
	{
		FreeLibrary(mlib);
	}
	
	CDialog::OnCancel();
}
