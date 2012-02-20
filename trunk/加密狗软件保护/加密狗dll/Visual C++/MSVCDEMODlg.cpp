// MSVCDEMODlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSVCDEMO.h"
#include "MSVCDEMODlg.h"
#include "GrandDogofDll.h"


RC_OPENDOG 							RC_OpenDog;
RC_CLOSEDOG 						RC_CloseDog;
RC_CHECKDOG							RC_CheckDog;
RC_GETDOGINFO						RC_GetDogInfo;
RC_GETPRODUCTCURRENTNO				RC_GetProductCurrentNo;
RC_VERIFYPASSWORD					RC_VerifyPassword;
RC_CHANGEPASSWORD					RC_ChangePassword;
RC_UPGRADE							RC_Upgrade;
RC_GETRANDOM						RC_GetRandom;
RC_ENCRYPTDATA						RC_EncryptData;
RC_DECRYPTDATA						RC_DecryptData;
RC_CONVERTDATA						RC_ConvertData;
RC_SETKEY							RC_SetKey;
RC_SIGNDATA							RC_SignData;
RC_EXECUTEFILE						RC_ExecuteFile;
RC_WRITEFILE						RC_WriteFile;
RC_VISITLICENSEFILE					RC_VisitLicenseFile;
RC_CREATEFILE						RC_CreateFile;
RC_DELETEFILE						RC_DeleteFile;
RC_CREATEDIR						RC_CreateDir;
RC_DELETEDIR						RC_DeleteDir;
RC_DEFRAGFILESYSTEM					RC_DefragFileSystem;
RC_READFILE							RC_ReadFile;
RC_GETUPGRADEREQUESTSTRING			RC_GetUpgradeRequestString;
RC_GETLICENSEINFO					RC_GetLicenseInfo;

HINSTANCE mlib;
/////////////////////////////////////////////////////////////////////////////
// CMSVCDEMODlg dialog

CMSVCDEMODlg::CMSVCDEMODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSVCDEMODlg::IDD, pParent)
{
	//initialize the member variable
	m_ulCurrentDogHandle=0;
	m_iDogIndex = 0;
	m_ulOpenFlag=RC_OPEN_FIRST_IN_LOCAL;
	m_ucPasswordType = RC_PASSWORDTYPE_USER;
	m_ucKeyType = RC_KEY_SIGN;
	m_bCallOpenFirstInLocal=false;
	//{{AFX_DATA_INIT(CMSVCDEMODlg)
	m_strProductName = _T("GrandDog");
	m_strOpenFlag = _T("1: OpenFirstInLocal");
	m_strPassword = _T("12345678");
	m_strUpgradeFilePath = _T("");
	m_iKeyIndex = 0;
	m_iPasswordIndex = 0;
	m_strResult = _T("");
	m_sDirID = 0;
	m_sFileID = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int iCount =0;iCount<32;iCount++)
	{
		m_ulDogHandleArray[iCount] = 0;
	}
}

void CMSVCDEMODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSVCDEMODlg)
	DDX_Text(pDX, IDC_EDIT_PRODUCT_NAME, m_strProductName);
	DDV_MaxChars(pDX, m_strProductName, 15);
	DDX_CBString(pDX, IDC_COMBO_OPEN_FLAG, m_strOpenFlag);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_UPGRADE_FILE_PATH, m_strUpgradeFilePath);
	DDV_MaxChars(pDX, m_strUpgradeFilePath, 128);
	DDX_Radio(pDX, IDC_RADIO_SIGN_KEY, m_iKeyIndex);
	DDX_Radio(pDX, IDC_RADIO_USER, m_iPasswordIndex);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_DIR_ID, m_sDirID);
	DDX_Text(pDX, IDC_EDIT_FILE_ID, m_sFileID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSVCDEMODlg, CDialog)
	//{{AFX_MSG_MAP(CMSVCDEMODlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DOG, OnButtonOpenDog)
	ON_BN_CLICKED(IDC_BUTTON_GET_DOG_INFO, OnButtonGetDogInfo)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_DOG, OnButtonCloseDog)
	ON_BN_CLICKED(IDC_BUTTON_GET_PRODUCT_INFO, OnButtonGetProductInfo)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY_PASSWORD, OnButtonVerifyPassword)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_PASSWORD, OnButtonChangePassword)
	ON_BN_CLICKED(IDC_BUTTON_SET_KEY, OnButtonSetKey)
	ON_BN_CLICKED(IDC_BUTTON_SIGN_DATA, OnButtonSignData)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT_DATA, OnButtonEncryptData)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT_DATA, OnButtonConvertData)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT_DATA, OnButtonDecryptData)
	ON_BN_CLICKED(IDC_BUTTON_GET_RANDOM, OnButtonGetRandom)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_DIR, OnButtonCreateDir)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_FILE, OnButtonDeleteFile)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_FILE, OnButtonCreateFile)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_DIR, OnButtonDeleteDir)
	ON_BN_CLICKED(IDC_BUTTON_READ_FILE, OnButtonReadFile)
	ON_BN_CLICKED(IDC_BUTTON_VISIT_LICENSE_FILE, OnButtonVisitLicenseFile)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_FILE, OnButtonWriteFile)
	ON_BN_CLICKED(IDC_BUTTON_DEFLAG_FILE_SYSTEM, OnButtonDeflagFileSystem)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE_FILE, OnButtonExecuteFile)
	ON_BN_CLICKED(IDC_BUTTON_GET_REQUEST, OnButtonGetRequest)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_UPGRADE, OnButtonUpgrade)
	ON_CBN_SELCHANGE(IDC_COMBO_OPEN_FLAG, OnSelchangeComboOpenFlag)
	ON_BN_CLICKED(IDC_RADIO_USER, OnRadioUser)
	ON_BN_CLICKED(IDC_RADIO_DEVELOPER, OnRadioDeveloper)
	ON_BN_CLICKED(IDC_RADIO_SIGN_KEY, OnRadioSignKey)
	ON_BN_CLICKED(IDC_RADIO_EN_DECRYPT_KEY, OnRadioEnDecryptKey)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_DOG, OnButtonCheckDog)
	ON_BN_CLICKED(IDC_BUTTON_GET_LICENSE_INFO, OnBnClickedButtonGetLicenseInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSVCDEMODlg message handlers

BOOL CMSVCDEMODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMSVCDEMODlg::OnPaint() 
{
	char Message[100];
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
		MessageBox(Message);
	 	exit(0);
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMSVCDEMODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMSVCDEMODlg::OnButtonOpenDog() 
{
	HRESULT hrReturnCode;
	int		iCount;
	UpdateData(TRUE);

	memset(m_cProductName, 0, 16);
	memcpy(m_cProductName, m_strProductName, m_strProductName.GetLength());

	if (m_ulCurrentDogHandle!=0)//You have opened dog before
	{
		if(RC_OPEN_FIRST_IN_LOCAL == m_ulOpenFlag)
		{
			m_ulCurrentDogHandle=0;
			//first step, Close all opened Dog handle
			for(iCount=0;iCount<m_iDogIndex;iCount++)
			{
				if(m_ulDogHandleArray[iCount]!=0)
				{
					RC_CloseDog(m_ulDogHandleArray[iCount]);
					m_ulDogHandleArray[iCount] = 0;
				}
			}
			m_iDogIndex=0;
			m_bCallOpenFirstInLocal = false;
			//second step, Open Dog Again.

			hrReturnCode = RC_OpenDog(m_ulOpenFlag,m_cProductName,&m_ulCurrentDogHandle);
			if (hrReturnCode!=S_OK)
			{
				m_strResult.Format("Open dog failed!\nThe error code is 0X%X.",hrReturnCode);
				UpdateData(FALSE);
				return;
			}
			else
			{
				m_strResult.Format("Open dog succeeded!\nThe dog handle is 0X%X.",m_ulCurrentDogHandle);
				m_iDogIndex=0;
				m_bCallOpenFirstInLocal = true;
				UpdateData(FALSE);
				return ;
			}
		}
		else if(RC_OPEN_NEXT_IN_LOCAL == m_ulOpenFlag)
		{
			if(m_bCallOpenFirstInLocal == false)
			{
				m_strResult.Format("You should use OpenFirstInLocal to call OpenDog!");
				UpdateData(FALSE);
				return;
			}
			else
			{
				unsigned long ulTmpDogHandle;
				ulTmpDogHandle = m_ulCurrentDogHandle;
				hrReturnCode = RC_OpenDog(m_ulOpenFlag,m_cProductName,&ulTmpDogHandle);
				if (hrReturnCode!=S_OK)
				{
					m_strResult.Format("Open dog failed!\nThe error code is 0X%X.",hrReturnCode);
					UpdateData(FALSE);
					return;
				}
				else
				{
					m_iDogIndex++;
					m_ulDogHandleArray[m_iDogIndex]=ulTmpDogHandle;
					m_ulCurrentDogHandle=ulTmpDogHandle;

					m_strResult.Format("Open dog succeeded!\nThe dog handle is 0X%X.",m_ulCurrentDogHandle);
					//m_iDogIndex=0;
					m_bCallOpenFirstInLocal = true;
					UpdateData(FALSE);
					return ;
				}
			}

		}
		else if(RC_OPEN_IN_LAN == m_ulOpenFlag 
			|| RC_OPEN_LOCAL_FIRST == m_ulOpenFlag 
			|| RC_OPEN_LAN_FIRST == m_ulOpenFlag)
		{

			m_ulCurrentDogHandle=0;
			//first step, Close all opened Dog handle
			for(iCount=0;iCount<m_iDogIndex;iCount++)
			{
				if(m_ulDogHandleArray[iCount]!=0)
				{
					RC_CloseDog(m_ulDogHandleArray[iCount]);
					m_ulDogHandleArray[iCount] = 0;
				}
			}
			m_iDogIndex=0;
			m_bCallOpenFirstInLocal = false;
			//second step, Open Dog Again.

			hrReturnCode = RC_OpenDog(m_ulOpenFlag,m_cProductName,&m_ulCurrentDogHandle);
			if (hrReturnCode!=S_OK)
			{
				m_strResult.Format("Open dog failed!\nThe error code is 0X%X.",hrReturnCode);
				UpdateData(FALSE);
				return;
			}
			else
			{	
				m_strResult.Format("Open dog succeeded!\nThe dog handle is 0X%X.",m_ulCurrentDogHandle);
				UpdateData(FALSE);
				return ;
			}
		}
		else
		{
			;
		}
	}
	else//m_ulCurrentDogHandle==0
	{
		if(RC_OPEN_NEXT_IN_LOCAL == m_ulOpenFlag)
		{
			m_strResult.Format("You should use OpenFirstInLocal to call OpenDog!");
		}
		else
		{
			hrReturnCode = RC_OpenDog(m_ulOpenFlag,m_cProductName,&m_ulCurrentDogHandle);
			if (hrReturnCode!=S_OK)
			{
				m_strResult.Format("Open dog failed!\nThe error code is 0X%X.",hrReturnCode);
				UpdateData(FALSE);
				return;
			}
			else
			{
				m_strResult.Format("Open dog succeeded!\nThe dog handle is 0X%X.",m_ulCurrentDogHandle);
				if(RC_OPEN_FIRST_IN_LOCAL == m_ulOpenFlag)
				{
					m_iDogIndex=0;
					m_bCallOpenFirstInLocal = true;
					m_ulDogHandleArray[0] = m_ulCurrentDogHandle;
				}
				UpdateData(FALSE);
				return ;
			}

		}
	}
	UpdateData(FALSE);
}


void CMSVCDEMODlg::OnButtonCheckDog() 
{
	HRESULT	hrReturnCode;
	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_CheckDog to judge whether the Hardware Dog exists or not
	hrReturnCode = RC_CheckDog(m_ulCurrentDogHandle);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Check dog failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{
		m_strResult.Format("Check dog succeeded!");
	}

	UpdateData(FALSE);

}



void CMSVCDEMODlg::OnButtonGetDogInfo()  
{
	HRESULT				hrReturnCode;
	RC_HARDWARE_INFO	HardwareInfo;
	ULONG				ulLen= sizeof(HardwareInfo);
	CString				strTmp;
	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;

	}
	//Call RC_GetDogInfo to get the Hardware Dog Infomation(SerialNumber, CurrentNumber, DogType, DogModel)
	hrReturnCode = RC_GetDogInfo(m_ulCurrentDogHandle,&HardwareInfo,&ulLen);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Get dog information failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{
		m_strResult.Format("GetDogInfo succeeded!\n");
		strTmp.Format("The serial number is Dec:%u  Hex:0X%X\nThe current number is Dec:%u  Hex:0X%X\n" 
			,HardwareInfo.ulSerialNumber,HardwareInfo.ulSerialNumber,
			HardwareInfo.ulCurrentNumber,HardwareInfo.ulCurrentNumber);
		m_strResult = m_strResult + strTmp;
		if (RC_DOGTYPE_LOCAL == HardwareInfo.ucDogType)
		{
			strTmp.Format("The dog type is STAND-ALONE dog. \n");
			m_strResult = m_strResult + strTmp;
		}
		else if (RC_DOGTYPE_NET == HardwareInfo.ucDogType)
		{
			strTmp.Format("The dog type is NET dog. \n");
			m_strResult = m_strResult + strTmp;
		}
		strTmp.Format("The dog model is %c%c%c%c",HardwareInfo.ucDogModel[0],HardwareInfo.ucDogModel[1],HardwareInfo.ucDogModel[2],HardwareInfo.ucDogModel[3]);
		m_strResult = m_strResult + strTmp;

	}

	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonGetProductInfo() 
{
	HRESULT				hrReturnCode;
	ULONG				ulProductCurrentNo;
	CString				strTmp;
	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;

	}
	//Call RC_GetProductInfo to get the product information(Product name Product current number)
	hrReturnCode = RC_GetProductCurrentNo(m_ulCurrentDogHandle,&ulProductCurrentNo);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Get product current number failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{
		m_strResult.Format("Get product current number succeeded!\nThe poduct current number is:");
		strTmp.Format("Dec:%u  Hex:0X%X",ulProductCurrentNo,ulProductCurrentNo);
		m_strResult = m_strResult + strTmp;
	}

	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonCloseDog() 
{
	
	HRESULT	hrReturnCode;
	int		iCount;
	UpdateData(TRUE);

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}

	//Close all opened dog
	for(iCount=0;iCount<m_iDogIndex+1;iCount++)
	{
		if(m_ulDogHandleArray[iCount]!=0)
		{
			hrReturnCode = RC_CloseDog(m_ulDogHandleArray[iCount]);
			if (S_OK != hrReturnCode)
			{
				m_strResult.Format("Close dog failed!\nThe error code is 0X%X",hrReturnCode);
				UpdateData(FALSE);				
				return;
			}
			else
			{
				m_ulDogHandleArray[iCount] = 0;
			}
		}
	}
	if(RC_OPEN_IN_LAN == m_ulOpenFlag 
			|| RC_OPEN_LAN_FIRST == m_ulOpenFlag)
	{
		//Close the current Dog Handle;
		if(m_ulCurrentDogHandle!=0)
		{
			hrReturnCode = RC_CloseDog(m_ulCurrentDogHandle);
			if (S_OK != hrReturnCode)
			{
				m_strResult.Format("Close dog failed!\nThe error code is 0X%X",hrReturnCode);
				UpdateData(FALSE);				
				return;
			}
			else
			{
				m_ulCurrentDogHandle= 0;
			}
		}
	}
	else
	{
		m_ulCurrentDogHandle=0;
	}
	m_iDogIndex=0;
	m_bCallOpenFirstInLocal = false;

	m_strResult.Format("Close dog succeeded!");
	UpdateData(FALSE);
	
}


void CMSVCDEMODlg::OnButtonVerifyPassword() 
{
	
	HRESULT	hrReturnCode;
	UCHAR	ucVerifyCount;
	
	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	if (m_strPassword.GetLength()<8)
	{
		m_strResult.Format("The length of password can not be less than 8!");
		UpdateData(FALSE);
		return ;
	}

	//Call RC_VerifyPassword to verify User or Developer password
	hrReturnCode = 	RC_VerifyPassword(m_ulCurrentDogHandle,m_ucPasswordType,m_strPassword.GetBuffer(m_strPassword.GetLength()),&ucVerifyCount);
	if (hrReturnCode == S_OK)
	{
		if( RC_PASSWORDTYPE_USER == m_ucPasswordType)
		{
			m_strResult.Format("Verify user password succeeded!");
		}
		else if(RC_PASSWORDTYPE_DEVELOPER == m_ucPasswordType)
		{
			m_strResult.Format("Verify developer password succeeded!");
		}
	}
	else
	{
		if( RC_PASSWORDTYPE_USER == m_ucPasswordType)
		{
			m_strResult.Format("Verify user password failed!\nThe verify count left is %d \nThe error code is 0X%X",ucVerifyCount,hrReturnCode);
		}
		else if(RC_PASSWORDTYPE_DEVELOPER == m_ucPasswordType)
		{
			m_strResult.Format("Verify developer password failed!\nThe verify count left is %d \nThe error code is 0X%X",ucVerifyCount,hrReturnCode);
		}
	}
	UpdateData(FALSE);

}

void CMSVCDEMODlg::OnButtonChangePassword() 
{
	
	HRESULT	hrReturnCode;
		
	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	if (m_strPassword.GetLength()<8)
	{
		m_strResult.Format("The length of password can not be less than 8!");
		UpdateData(FALSE);
		return;
	}

	//Call RC_ChangePassword to Change the password.
	hrReturnCode = 	RC_ChangePassword(m_ulCurrentDogHandle,m_ucPasswordType,m_strPassword.GetBuffer(m_strPassword.GetLength()));
	if (hrReturnCode == S_OK)
	{
		if( RC_PASSWORDTYPE_USER == m_ucPasswordType)
		{
			m_strResult.Format("Change user password succeeded!");
		}
		else if(RC_PASSWORDTYPE_DEVELOPER == m_ucPasswordType)
		{
			m_strResult.Format("Change developer password succeeded!");
		}
	}
	else
	{
		if( RC_PASSWORDTYPE_USER == m_ucPasswordType)
		{
			m_strResult.Format("Change user password failed!\nThe error code is 0X%X",hrReturnCode);
		}
		else if(RC_PASSWORDTYPE_DEVELOPER == m_ucPasswordType)
		{
			m_strResult.Format("Change developer password failed!\nThe error code is 0X%X",hrReturnCode);
		}
	}
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonSetKey() 
{
	UCHAR	ucKey[16]={0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50};//"ABCDEFGHIJKLMNOP"
	HRESULT	hrReturnCode;
	int		iCount;
	CString strTmp;
	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_SetKey to set the signature key or AES key.
	hrReturnCode = RC_SetKey(m_ulCurrentDogHandle,m_ucKeyType,ucKey,16);
	if (hrReturnCode!=S_OK)
	{
		if(RC_KEY_AES == m_ucKeyType)
		{
			m_strResult.Format("Set AES Key failed!\nThe error code is 0X%X.",hrReturnCode);
		}
		else if(RC_KEY_SIGN == m_ucKeyType)
		{
			m_strResult.Format("Set Sign Key failed!\nThe error code is 0X%X.",hrReturnCode);
		}

	}
	else
	{
		if(RC_KEY_AES == m_ucKeyType)
		{
			m_strResult.Format("Set AES Key succeeded!\nThe key is:\n");
		}
		else if(RC_KEY_SIGN == m_ucKeyType)
		{
			m_strResult.Format("Set Sign Key succeeded!\nThe key is:\n");
		}
		for(iCount=0;iCount<16;iCount++)
		{
			strTmp.Format("0X%02X " ,ucKey[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnButtonSignData() 
{
	HRESULT	hrReturnCode;
	int		iCount;
	CString strTmp;
	UCHAR	ucSignData[256];
	ULONG	ulSignLen=16;
	ULONG	ulResultLen=16;
	UCHAR	ucSignResult[16];

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	for(iCount=0;iCount<256;iCount++)
	{
		ucSignData[iCount]=iCount;
	}
	//Call RC_SignData to get the result of signature
	hrReturnCode=RC_SignData(m_ulCurrentDogHandle,ucSignData,ulSignLen,ucSignResult,&ulResultLen);
	if (hrReturnCode!=S_OK)
	{

		m_strResult.Format("Sign data failed!\nThe error code is 0X%X.",hrReturnCode);

	}
	else
	{

		m_strResult.Format("Sign data succeeded!\nThe result is:\n");
		for(iCount=0;iCount<16;iCount++)
		{
			strTmp.Format("0X%02X " ,ucSignResult[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);	
}

void CMSVCDEMODlg::OnButtonEncryptData() 
{
	HRESULT	hrReturnCode;
	int		iCount;
	CString strTmp;
	UCHAR	ucEncryptData[16];
	ULONG	ulEncryptLen=16;
	ULONG	ulResultLen=16;
	UCHAR	ucResult[16];

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	for(iCount=0;iCount<16;iCount++)
	{
		ucEncryptData[iCount]=iCount;
	}
	//Call RC_EncryptData to get the result of encryption
	hrReturnCode=RC_EncryptData(m_ulCurrentDogHandle,ucEncryptData,ulEncryptLen,ucResult,&ulResultLen);
	if (hrReturnCode!=S_OK)
	{

		m_strResult.Format("Encrypt data failed!\nThe error code is 0X%X.",hrReturnCode);

	}
	else
	{

		m_strResult.Format("Encrypt data succeeded!\nThe encrypted data is:\n");
		for(iCount=0;iCount<16;iCount++)
		{
			strTmp.Format("0X%02X " ,ucEncryptData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}

		strTmp.Format("\nThe result is:\n");
		m_strResult = m_strResult+strTmp;
		for(iCount=0;iCount<16;iCount++)
		{
			m_ucEncryptedData[iCount]=ucResult[iCount];//store the encrypted data

			strTmp.Format("0X%02X " ,ucResult[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);	
}

void CMSVCDEMODlg::OnButtonConvertData() 
{
	HRESULT	hrReturnCode;
	int		iCount;
	UCHAR	ucConvertData[16];
	ULONG	ulLen=16;
	ULONG	ulResult;
	CString strTmp;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	for(iCount=0;iCount<16;iCount++)
	{
		ucConvertData[iCount]=0x41+iCount;
	}
	//Call RC_ConvertData to get the result of convertion
	hrReturnCode = RC_ConvertData(m_ulCurrentDogHandle,ucConvertData,ulLen,&ulResult);

	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Convert data failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{

		m_strResult.Format("Convert data succeeded!\n\nThe data is:\n");
		for(iCount=0;iCount<16;iCount++)
		{
			strTmp.Format("0X%02X " ,ucConvertData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
		strTmp.Format("\nThe result is: DEC:%u  HEX:0X%X",ulResult,ulResult);
		m_strResult = m_strResult+strTmp;
	}
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonDecryptData() 
{

	HRESULT	hrReturnCode;
	int		iCount;
	CString strTmp;
	ULONG	ulDecryptLen=16;
	ULONG	ulResultLen=16;
	UCHAR	ucResult[16];

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_DecryptData to get the result of decryption
	hrReturnCode=RC_DecryptData(m_ulCurrentDogHandle,m_ucEncryptedData,ulDecryptLen,ucResult,&ulResultLen);
	if (hrReturnCode!=S_OK)
	{

		m_strResult.Format("Decrypt data failed!\nThe error code is 0X%X.",hrReturnCode);

	}
	else
	{

		m_strResult.Format("Decrypt data succeeded!\nThe decrypted data is:\n");
		for(iCount=0;iCount<16;iCount++)
		{
			strTmp.Format("0X%02X " ,m_ucEncryptedData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}

		strTmp.Format("\nThe Result is:\n");
		m_strResult = m_strResult+strTmp;
		for(iCount=0;iCount<16;iCount++)
		{

			strTmp.Format("0X%02X " ,ucResult[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);	

	
}

void CMSVCDEMODlg::OnButtonGetRandom() 
{
	HRESULT	hrReturnCode;
	int		iCount;
	UCHAR	ucRandomData[256];
	UCHAR	ucLen=255;
	CString strTmp;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_GetRandom to get the random data 
	hrReturnCode = RC_GetRandom(m_ulCurrentDogHandle,ucRandomData,ucLen);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Get random data failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{

		m_strResult.Format("Get random data succeeded!\n\nThe random data is\n");
		for(iCount=0;iCount<ucLen;iCount++)
		{
			strTmp.Format("0X%02X " ,ucRandomData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonCreateDir() 
{
	HRESULT		hrReturnCode;
	USHORT		usDirSize = 266;	
	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_CreateDir to create directory file
	hrReturnCode = RC_CreateDir(m_ulCurrentDogHandle,m_sDirID,usDirSize);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Create directory succeeded!\nThe directory ID is DEC:%d  HEX:0X%04X\nThe directory size is DEC:%d  HEX:0X%04X",m_sDirID,m_sDirID,usDirSize,usDirSize);
	}
	else
	{
		m_strResult.Format("Create directory failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
	
}


void CMSVCDEMODlg::OnButtonCreateFile() 
{
	HRESULT		hrReturnCode;
	USHORT		usFileSize = 110;	

	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_CreateFile to create file
	//We only create data file in here. You can create license file or algorithm file with Developer Tool.	
	hrReturnCode = RC_CreateFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID,RC_TYPEFILE_DATA,usFileSize);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Create file succeeded!\nThe directory ID is DEC:%d  HEX:0X%04X \nThe File ID is DEC:%d  HEX:0X%04X\nThe file size is DEC:%d  HEX:0X%04X",
			m_sDirID,m_sDirID,m_sFileID,m_sFileID,usFileSize,usFileSize);
	}
	else
	{
		m_strResult.Format("Create file failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}


void CMSVCDEMODlg::OnButtonWriteFile() 
{
	CString		strTmp;
	HRESULT		hrReturnCode;
	int			iCount;
	ULONG		ulPos=0;
	ULONG		ulLen=100;
	UCHAR		ucData[100];
	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	for(iCount=0;iCount<100;iCount++)
	{
		ucData[iCount]=iCount;
	}
	//Call RC_WriteFile to write data to the specified file
	hrReturnCode = RC_WriteFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID,ulPos,ulLen,ucData);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Write file failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{

		m_strResult.Format("Write file succeeded!\n\nThe write data is\n");
		for(iCount=0;iCount<(int)ulLen;iCount++)
		{
			strTmp.Format("0X%02X " ,ucData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);
}


void CMSVCDEMODlg::OnButtonReadFile() 
{
	CString		strTmp;
	HRESULT		hrReturnCode;
	int			iCount;
	ULONG		ulPos=0;
	ULONG		ulLen=100;
	UCHAR		ucData[100];
	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	memset(ucData,0,100);
	//Call RC_ReadFile to read data from the specified file.
	hrReturnCode = RC_ReadFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID,ulPos,ulLen,ucData);
	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Read file failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{

		m_strResult.Format("Read file succeeded!\nThe read data is\n");
		for(iCount=0;iCount<(int)ulLen;iCount++)
		{
			strTmp.Format("0X%02X " ,ucData[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
	}
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonVisitLicenseFile() 
{
	HRESULT		hrReturnCode;
	ULONG		ulReserved=0;

	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_VisitLicenseFile to visit license file
	hrReturnCode = RC_VisitLicenseFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID,ulReserved);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Visit license file succeeded!\n");
	}
	else
	{
		m_strResult.Format("Visit license file failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnButtonDeleteDir() 
{
	HRESULT		hrReturnCode;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_DeleteDir to delete the specified directory file.
	hrReturnCode = RC_DeleteDir(m_ulCurrentDogHandle,m_sDirID);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Delete directory succeeded!\n");
	}
	else
	{
		m_strResult.Format("Delete directory failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}
void CMSVCDEMODlg::OnButtonDeleteFile() 
{
	HRESULT		hrReturnCode;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_Deletefile to delete the specified file.
	hrReturnCode = RC_DeleteFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Delete file succeeded!\n");
	}
	else
	{
		m_strResult.Format("Delete file failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnButtonDeflagFileSystem() 
{
	HRESULT		hrReturnCode;

	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_DefragFileSystem to defrag the file system of the specified directory in Hardware Dog.
	//If you want to defrag the root directory, usDirID should be 0x3F00.
	hrReturnCode = RC_DefragFileSystem(m_ulCurrentDogHandle,m_sDirID);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Defrag file system succeeded!\n");
	}
	else
	{
		m_strResult.Format("Defrag file system failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnButtonExecuteFile() 
{
	UCHAR		ucDataIn[32];
	ULONG		ulInLen=32;
	UCHAR		ucDataOut[32];
	ULONG		ulOutLen=32;
	HRESULT		hrReturnCode;
	int			iCount;
	CString		strTmp;
	int			i;

	UpdateData(TRUE);
	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	for(i=0;i<32;i++)
	{
		ucDataIn[i] = i;
	}
	//Call RC_ExecuteFile to execute algorithm file and get the result.
	hrReturnCode = RC_ExecuteFile(m_ulCurrentDogHandle,m_sDirID,m_sFileID,ucDataIn,ulInLen,ucDataOut,&ulOutLen);
	if (S_OK == hrReturnCode)
	{
		m_strResult.Format("Execute file succeeded!\nThe input data is\n");
		for(iCount=0;iCount<(int)ulInLen;iCount++)
		{
			strTmp.Format("0X%02X " ,ucDataIn[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}
		strTmp.Format("\nThe output data is\n");
		m_strResult = m_strResult+strTmp;
		for(iCount=0;iCount<(int)ulOutLen;iCount++)
		{
			strTmp.Format("0X%02X " ,ucDataOut[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%8==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}

	}
	else
	{
		m_strResult.Format("Execute file failed!\nThe error code is 0X%X",hrReturnCode);
	}
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnButtonGetRequest() 
{
	HRESULT	hrReturnCode;
	UCHAR	ucRequestString[64];
	ULONG	ulLen=64;
	CString strTmp;
	int		iCount;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	//Call RC_GetUpgradeRequestString to get the upgrade request string.
	hrReturnCode = RC_GetUpgradeRequestString(m_ulCurrentDogHandle,ucRequestString,&ulLen);

	if (hrReturnCode!=S_OK)
	{
		m_strResult.Format("Get upgrade request string failed!\nThe error code is 0X%X.",hrReturnCode);
	}
	else
	{
		m_strResult.Format("Get upgrade request string succeeded!\n\nThe request string is:\n");
		for (iCount=0;iCount<64;iCount++)
		{
			strTmp.Format("%c",ucRequestString[iCount]);
			m_strResult = m_strResult+strTmp;
			if((iCount+1)%32==0)
			{
				strTmp.Format("\n");
				m_strResult = m_strResult+strTmp;
			}
		}

	}
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnButtonBrowse() 
{
	CFileDialog filedlg (TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Upgrade Files (*.upg) | *.upg||");
	if (filedlg.DoModal() == IDOK)
	{		
		m_strUpgradeFilePath = filedlg.GetPathName();
		UpdateData(false);
	}

}

void CMSVCDEMODlg::OnButtonUpgrade() 
{
	CString		strTmp;
	HANDLE		hHandle	;
	DWORD		dwLength;
	UCHAR *		pucTemp;
	BOOL		bRet;
	HRESULT		hrReturnCode;
	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}
	hHandle = CreateFile(m_strUpgradeFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
		                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE==hHandle)
	{
		m_strResult.Format("Open upgrade file failed!");
		UpdateData(FALSE);
		return;
	}


	dwLength = GetFileSize(hHandle,NULL);
	pucTemp = new unsigned char[dwLength+1];

	bRet = ReadFile(hHandle, pucTemp, dwLength, &dwLength, NULL);
	if(!bRet)
	{
		m_strResult.Format("Read upgrade file failed!");
		CloseHandle(hHandle);
		delete pucTemp;
		UpdateData(FALSE);
		return ;
	}
	CloseHandle(hHandle);
	hrReturnCode = RC_Upgrade(  m_ulCurrentDogHandle, pucTemp, dwLength);
	
	if(S_OK == hrReturnCode)
	{
		m_strResult.Format("Upgrade succeeded!");
	}
	else
	{
		m_strResult.Format("Upgrade failed!\nError code is :0x%x",hrReturnCode);
	}
	
	delete pucTemp;
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnSelchangeComboOpenFlag() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCBox = (CComboBox*)GetDlgItem(IDC_COMBO_OPEN_FLAG);
	int iIndex = pCBox->GetCurSel();
	if (iIndex == CB_ERR)
	{
		return;
	}
	m_ulOpenFlag=iIndex+1;
	pCBox->GetLBText(iIndex, m_strOpenFlag);
	UpdateData(FALSE);
}

void CMSVCDEMODlg::OnRadioUser() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ucPasswordType = RC_PASSWORDTYPE_USER;
	UpdateData(FALSE);

}

void CMSVCDEMODlg::OnRadioDeveloper() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ucPasswordType = RC_PASSWORDTYPE_DEVELOPER;
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnRadioSignKey() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ucKeyType = RC_KEY_SIGN;
	UpdateData(FALSE);
	
}

void CMSVCDEMODlg::OnRadioEnDecryptKey() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ucKeyType = RC_KEY_AES;
	UpdateData(FALSE);
}


void CMSVCDEMODlg::OnBnClickedButtonGetLicenseInfo()
{
	HRESULT hRet;
    USHORT usLimit;
    ULONG ulCount;
    ULONG ulRuntime;
    ULONG ulDay, ulHour, ulMinute;
    USHORT usBeginYear, usEndYear;
    UCHAR ucBeginMonth, ucBeginDay, ucBeginHour, ucBeginMinute, ucBeginSecond;
    UCHAR ucEndMonth, ucEndDay, ucEndHour, ucEndMinute, ucEndSecond;

	UpdateData(TRUE);

	if (m_ulCurrentDogHandle == 0)
	{
		m_strResult.Format("There is no valid Dog handle.\nYou should call OpenDog first!");
		UpdateData(FALSE);
		return;
	}

    hRet = RC_GetLicenseInfo(m_ulCurrentDogHandle, m_sDirID, m_sFileID, &usLimit, &ulCount, &ulRuntime, 
            &usBeginYear,&ucBeginMonth,&ucBeginDay,&ucBeginHour,&ucBeginMinute,&ucBeginSecond,
            &usEndYear,&ucEndMonth,&ucEndDay,&ucEndHour,&ucEndMinute,&ucEndSecond);
    if (hRet == 0)
    {
        // succeeded
        m_strResult = "Get license information succeeded!\n";
        if ((usLimit & 0x0001) == 1)			// Limit number
        {
			CString csTemp;
			csTemp.Format("Check Limit Count!\nThe Limit Count is :%u\n", ulCount);
			m_strResult += csTemp;
        }

        if ((usLimit & 0x0002) == 2)		// Limit runtime
        {
            ulDay = ulRuntime / (24 * 60);
            ulHour = ulRuntime % (24 * 60) / 60;
            ulMinute = ulRuntime % (24 * 60) % 60;

			CString csTemp;
			csTemp.Format("Check Runtime!\nThe Runtime is :%d Days, %d Hours, %d Minutes\n", ulDay, ulHour, ulMinute);
			m_strResult += csTemp;
        }

        if ((usLimit & 0x0004) == 4)		// Limit end time and begin time
        {
			CString csTemp;
			csTemp.Format("Check expiration date!\nThe begin time is:%d-%d-%d %d:%d:%d\nThe end time is:%d-%d-%d %d:%d:%d\n",
				usBeginYear, ucBeginMonth, ucBeginDay, ucBeginHour, ucBeginMinute,ucBeginSecond, 
				usEndYear, ucEndMonth, ucEndDay, ucEndHour, ucEndMinute,ucEndSecond);

			m_strResult += csTemp;
        }

    }
    else
    {
        // failed
		CString csTemp;
		csTemp.Format("Get license information failed!\nError code is: 0x%x", hRet);
		m_strResult = csTemp;
    }

    UpdateData(FALSE);
}
