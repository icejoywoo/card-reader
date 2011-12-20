// ServerSetting.cpp : implementation file
// 服务器设置对话框

#include "stdafx.h"
#include "CardReaderServer.h"
#include "ServerSetting.h"
#include "Server.h"
#include "ServerUtils.h"
#include <set>

using namespace std;

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

BOOL ServerSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化读卡器配置listCtrl
	LVCOLUMN column;
	column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	column.fmt = LVCFMT_LEFT;
	column.cx = 80;
	column.iSubItem = 0;
	column.pszText = "读卡器id";
	m_Readers.InsertColumn(0, &column);

	return TRUE;
}


void ServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Control(pDX, IDC_LIST_READER, m_Readers);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
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

	
	
	UpdateData(FALSE);
	CDialog::OnOK();
}

void ServerSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);


	int index = 0;
	for (set<int>::iterator iter = ServerParam::instance->readerIdSet.begin();
		iter != ServerParam::instance->readerIdSet.end(); ++iter)
	{
		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_IMAGE;
		item.iItem = index;
		item.iSubItem = 0;
		char buf[10];
		sprintf(buf, "读卡器 %d", *iter);
		item.pszText = buf;
		m_Readers.InsertItem(&item);
		index++;
	}

	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}
