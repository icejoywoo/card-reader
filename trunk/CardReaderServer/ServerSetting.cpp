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
	//}}AFX_DATA_INIT
}


void ServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ServerSetting, CDialog)
	//{{AFX_MSG_MAP(ServerSetting)
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
	UpdateData(FALSE);
	if (oldPort != Server::getInstance()->getPort()) // 如果端口修改了, 进行提示
	{
		AfxMessageBox("需要重启服务器, 才可以生效!!!");
	}

	CDialog::OnOK();
}
