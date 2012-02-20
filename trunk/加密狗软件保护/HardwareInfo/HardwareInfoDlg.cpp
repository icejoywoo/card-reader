// HardwareInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HardwareInfo.h"
#include "HardwareInfoClass.h"
#include "HardwareInfoDlg.h"

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
// CHardwareInfoDlg dialog

CHardwareInfoDlg::CHardwareInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHardwareInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHardwareInfoDlg)
	m_strFuncKeyNumber = _T("");
	m_strKeyboardType = _T("");
	m_strPhysAvail = _T("");
	m_strPhysTotal = _T("");
	m_strProcessorNumber = _T("");
	m_strVirtualAvail = _T("");
	m_strVirtualTotal = _T("");
	m_strPageSize = _T("");
	m_strProcessorArchitecture = _T("");
	m_strProcessorLevel = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHardwareInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHardwareInfoDlg)
	DDX_Text(pDX, IDC_STATIC_KEYBOARDFUNCNUMBER, m_strFuncKeyNumber);
	DDX_Text(pDX, IDC_STATIC_KEYBOARDTYPE, m_strKeyboardType);
	DDX_Text(pDX, IDC_STATIC_PHYSAVAIL, m_strPhysAvail);
	DDX_Text(pDX, IDC_STATIC_PHYSTOTAL, m_strPhysTotal);
	DDX_Text(pDX, IDC_STATIC_PROCESSORNUMBER, m_strProcessorNumber);
	DDX_Text(pDX, IDC_STATIC_VIRTUALAVAIL, m_strVirtualAvail);
	DDX_Text(pDX, IDC_STATIC_VIRTUALTOTAL, m_strVirtualTotal);
	DDX_Text(pDX, IDC_STATIC_PAGESIZE, m_strPageSize);
	DDX_Text(pDX, IDC_STATIC_PROCESSORARCHITECTURE, m_strProcessorArchitecture);
	DDX_Text(pDX, IDC_STATIC_PROCESSORLEVEL, m_strProcessorLevel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHardwareInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CHardwareInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg message handlers

BOOL CHardwareInfoDlg::OnInitDialog()
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
	CHardwareInfo hdi;

	// Processor info
	DWORD dwProcessorArchitecture = hdi.GetProcessorArchitecture();
	WORD wProcessorLevel = hdi.GetProcessorLevel();
	WORD wProcessorRevision = hdi.GetProcessorRevision();
	switch (dwProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		{
			m_strProcessorArchitecture = "Intel";

			switch (wProcessorLevel)
			{
			case 3:
				m_strProcessorLevel = "Intel 386";
				break;
			case 4:
				m_strProcessorLevel = "Intel 486";
				break;
			case 5:
				m_strProcessorLevel = "Intel Pentium";
				break;
			case 6:
				m_strProcessorLevel = "Intel Pentium Pro or Pentium II";
				break;
			}
		}
		break;
	case PROCESSOR_ARCHITECTURE_MIPS:
		{
			m_strProcessorArchitecture = "MIPS";

			if (0004 == wProcessorLevel)
				m_strProcessorLevel = "MIPS R4000";
		}
		break;
	case PROCESSOR_ARCHITECTURE_ALPHA:
		{
			m_strProcessorArchitecture = "Alpha";

			switch (wProcessorLevel)
			{
			case 21064:
				m_strProcessorLevel = "Alpha 21064";
				break;
			case 21066:
				m_strProcessorLevel = "Alpha 21066";
				break;
			case 21164:
				m_strProcessorLevel = "Alpha 21164";
				break;
			}
		}
		break;
	case PROCESSOR_ARCHITECTURE_PPC:
		{
			m_strProcessorArchitecture = "PowerPC";
			switch (wProcessorLevel)
			{
			case 1:
				m_strProcessorLevel = "PowerPC 601";
				break;
			case 3:
				m_strProcessorLevel = "PowerPC 603";
				break;
			case 4:
				m_strProcessorLevel = "PowerPC 604";
				break;
			case 6:
				m_strProcessorLevel = "PowerPC 603+";
				break;
			case 9:
				m_strProcessorLevel = "PowerPC 604+";
				break;
			case 20:
				m_strProcessorLevel = "PowerPC 620";
				break;
			}
		}
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
			m_strProcessorArchitecture = "Unknown";
			m_strProcessorLevel = "Unknown";
			break;
	}

	m_strProcessorNumber.Format("%d", hdi.GetProcessorNumber());
	m_strPageSize.Format("%d", hdi.GetPageSize());

	// Memory info
	m_strPhysTotal.Format("%lu", hdi.GetTotalPhysicalMemory()/1024);
	m_strPhysAvail.Format("%lu", hdi.GetAvailPhysicalMemory()/1024);
	m_strVirtualTotal.Format("%lu", hdi.GetTotalVirtualMemory()/1024);
	m_strVirtualAvail.Format("%lu", hdi.GetAvailVirtualMemory()/1024);

	// Keyboard info
	switch (hdi.GetKeyboardType())
	{
	case 1:
		m_strKeyboardType = "IBM PC/XT or compatible (83-key) keyboard";
		break;
	case 2:
		m_strKeyboardType = "Olivetti 'ICO' (102-key) keyboard";
		break;
	case 3:
		m_strKeyboardType = "IBM PC/AT (84-key) or similar keyboard";
		break; 
	case 4:
		m_strKeyboardType = "IBM enhanced (101- or 102-key) keyboard";
		break; 
	case 5:
		m_strKeyboardType = "Nokia 1050 and similar keyboards";
		break; 
	case 6:
		m_strKeyboardType = "Nokia 9140 and similar keyboards";
		break; 
	case 7:
		m_strKeyboardType = "Japanese keyboard";
		break;
	}

	int nFuncKeyNum = hdi.GetKeyboardFuncKeyNumber();
	if (nFuncKeyNum == -1)
		m_strFuncKeyNumber = "Dependent and specified by the OEM";
	else
		m_strFuncKeyNumber.Format("%d", nFuncKeyNum);

	// Show info
	UpdateData(FALSE);

	// Drive info

		// Create the listctrl for drive info
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_LIST_DRIVES);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	DWORD dwStyle=WS_CHILD|WS_VISIBLE|LVS_SINGLESEL|LVS_REPORT|
					LVS_SHOWSELALWAYS|LVS_SORTASCENDING;
	m_listDrives.Create(dwStyle, rect, this, IDC_LIST_DRIVES);
	m_listDrives.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);

		// Set Header info
	m_listDrives.InsertColumn(0, _T("Drive"), LVCFMT_CENTER, 50, 0);
	m_listDrives.InsertColumn(1, _T("Drive Type"), LVCFMT_CENTER, 90, 1);
	m_listDrives.InsertColumn(2, _T("Total Space (KB)"), LVCFMT_CENTER, 150, 2);
	m_listDrives.InsertColumn(3, _T("Avail Space (KB)"), LVCFMT_CENTER, 150, 3);

		// Drives info
	CStringList	lstDrives;
	int nDrives = hdi.GetLogicalDrives(&lstDrives);

		// Fill drive info
	for (int i=0; i<nDrives; ++i)
	{
		CString sDrivePath = lstDrives.GetAt(lstDrives.FindIndex(i));
		CString sDriveType;
		switch (hdi.GetDriveType(sDrivePath))
		{
		case DRIVE_UNKNOWN:
			sDriveType = "Unknown Drive Type";
			break;
		case DRIVE_NO_ROOT_DIR:
			sDriveType = "Drive Path does not exist";
			break;
		case DRIVE_REMOVABLE:
			sDriveType = "Floppy Drive";
			break;
		case DRIVE_FIXED:
			sDriveType = "Hard Disk";
			break;
		case DRIVE_REMOTE:
			sDriveType = "Network Drive";
			break;
		case DRIVE_CDROM:
			sDriveType = "CD-ROM";
			break;
		case DRIVE_RAMDISK:
			sDriveType = "RAM Disk";
			break;
		}
		CString sDriveTotalSpace, sDriveAvailSpace;
		ULONGLONG ullDriveTotalSpace = hdi.GetTotalDriveSpace(sDrivePath);
		if (ullDriveTotalSpace == -1)
			sDriveTotalSpace = "Not Ready";
		else
		{
			ullDriveTotalSpace /= 1024;
			sDriveTotalSpace.Format("%lu", ullDriveTotalSpace);
		}
		ULONGLONG ullDriveAvailSpace = hdi.GetAvailDriveSpace(sDrivePath);
		if (ullDriveAvailSpace == -1)
			sDriveAvailSpace = "Not Ready";
		else
		{
			ullDriveAvailSpace /= 1024;
			sDriveAvailSpace.Format("%lu", ullDriveAvailSpace);
		}

		LVITEM lvi;

		lvi.mask = LVIF_TEXT ; 
		lvi.cchTextMax = 64;
		lvi.iItem = i;
		lvi.iSubItem = 0; 
		lvi.pszText = sDrivePath.GetBuffer(64);
		m_listDrives.InsertItem(&lvi);

		m_listDrives.SetItemText(i, 1, sDriveType);
		m_listDrives.SetItemText(i, 2, sDriveTotalSpace);
		m_listDrives.SetItemText(i, 3, sDriveAvailSpace);

		sDrivePath.ReleaseBuffer();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHardwareInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHardwareInfoDlg::OnPaint() 
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
HCURSOR CHardwareInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
