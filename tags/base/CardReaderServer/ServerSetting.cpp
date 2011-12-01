// ServerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "CardReaderServer.h"
#include "ServerSetting.h"
#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServerSetting dialog


ServerSetting::ServerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(ServerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(ServerSetting)
	m_Port = Server::getInstance()->getPort();
	m_ReaderCount = 0;
	//}}AFX_DATA_INIT
}


void ServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Control(pDX, IDC_IPADDRESS4, m_IP4);
	DDX_Control(pDX, IDC_IPADDRESS3, m_IP3);
	DDX_Control(pDX, IDC_IPADDRESS2, m_IP2);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP1);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_READERCOUNT, m_ReaderCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ServerSetting, CDialog)
	//{{AFX_MSG_MAP(ServerSetting)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ServerSetting message handlers

void ServerSetting::OnOK() 
{
	// TODO: Add extra validation here
	int oldPort = Server::getInstance()->getPort(); // 保存原来的端口
	UpdateData(TRUE);
	Server::getInstance()->setPort(m_Port);
	
	if (oldPort != Server::getInstance()->getPort()) // 如果端口修改了, 进行提示
	{
		AfxMessageBox("修改了端口号, 需要重启服务器, 才可以生效!!!");
	}
	
	ServerParam::instance->ip1 = getIpAdress(m_IP1);
	ServerParam::instance->ip2 = getIpAdress(m_IP2);
	ServerParam::instance->ip3 = getIpAdress(m_IP3);
	ServerParam::instance->ip4 = getIpAdress(m_IP4);

	if (m_ReaderCount >= 0 && m_ReaderCount <= 128)
	{
		ServerParam::instance->readerCount = m_ReaderCount;
	} else {
		AfxMessageBox("读卡器数目设置有误, 范围为1-128.");
	}
	
	UpdateData(FALSE);
	CDialog::OnOK();
}

void ServerSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);
	m_IP1.SetWindowText(ServerParam::instance->ip1);
	m_IP2.SetWindowText(ServerParam::instance->ip2);
	m_IP3.SetWindowText(ServerParam::instance->ip3);
	m_IP4.SetWindowText(ServerParam::instance->ip4);

	m_ReaderCount = ServerParam::instance->readerCount;
	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}
