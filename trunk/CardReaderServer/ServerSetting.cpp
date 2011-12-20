// ServerSetting.cpp : implementation file
// ���������öԻ���

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

	// ��ʼ������������listCtrl
	LVCOLUMN column;
	column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	column.fmt = LVCFMT_LEFT;
	column.cx = 80;
	column.iSubItem = 0;
	column.pszText = "������id";
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
		sprintf(buf, "������ %d", *iter);
		item.pszText = buf;
		m_Readers.InsertItem(&item);
		index++;
	}

	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}
