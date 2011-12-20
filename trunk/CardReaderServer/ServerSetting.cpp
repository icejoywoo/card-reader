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
	m_AddReaderId = 0;
	//}}AFX_DATA_INIT
}

BOOL ServerSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}


void ServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Control(pDX, IDC_LIST_READERS, m_ReaderList);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_READER_ID, m_AddReaderId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ServerSetting, CDialog)
	//{{AFX_MSG_MAP(ServerSetting)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddReader)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelReader)
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

	
	ServerParam::instance->saveConfig(); // ��������

	UpdateData(FALSE);
	CDialog::OnOK();
}

void ServerSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);
	
	m_ReaderList.ResetContent();
	int index = 0;
	for (set<int>::iterator iter = ServerParam::instance->readerIdSet.begin();
		iter != ServerParam::instance->readerIdSet.end(); ++iter)
	{
		char name[50];
		sprintf(name, "������ %d", (*iter));
		m_ReaderList.AddString(name);
		m_ReaderList.SetItemData(index, (*iter));
		++index;
	}

	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}

// ��Ӷ�����
void ServerSetting::OnButtonAddReader() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (ServerParam::instance->readerIdSet.count(m_AddReaderId) == 0)
	{
		char name[50];
		sprintf(name, "������ %d", m_AddReaderId);
		m_ReaderList.AddString(name);
		ServerParam::instance->readerIdSet.insert(m_AddReaderId);
	} else {
		AfxMessageBox("����Ķ�����id�Ѿ����ڻ���ȷ. ����!");
	}

	UpdateData(FALSE);
}

// ɾ����ѡ������
void ServerSetting::OnButtonDelReader() 
{
	// TODO: Add your control notification handler code here
	int index = m_ReaderList.GetCurSel();
	if (index != LB_ERR)
	{
		int readerId = m_ReaderList.GetItemData(index);
		ServerParam::instance->readerIdSet.erase(index);
		m_ReaderList.DeleteString(index);
	}
}
