// ServerSetting.cpp : implementation file
// ���������öԻ���

#include "stdafx.h"
#include "CardReaderServer.h"
#include "ServerSettingDlg.h"
#include "Server.h"
#include "ServerUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServerSetting dialog


ServerSettingDlg::ServerSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ServerSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ServerSetting)
	m_Port = Server::getInstance()->getPort();
	//}}AFX_DATA_INIT
}


void ServerSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ServerSettingDlg, CDialog)
	//{{AFX_MSG_MAP(ServerSetting)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ServerSetting message handlers

void ServerSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	int oldPort = Server::getInstance()->getPort(); // ����ԭ���Ķ˿�
	UpdateData(TRUE);
	Server::getInstance()->setPort(m_Port);
	
	if (oldPort != Server::getInstance()->getPort()) // ����˿��޸���, ������ʾ
	{
		AfxMessageBox("�޸��˶˿ں�, ��Ҫ����������, �ſ�����Ч!!!");
	}
	
	UpdateData(FALSE);
	CDialog::OnOK();
}

void ServerSettingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);

	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}
