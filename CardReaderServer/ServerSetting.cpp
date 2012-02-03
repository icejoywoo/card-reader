// ServerSetting.cpp : implementation file
// 服务器设置对话框

#include "stdafx.h"
#include "CardReaderServer.h"
#include "ServerSetting.h"
#include "Server.h"
#include "ServerUtils.h"
#include <set>
#include <algorithm>
#include <utility>

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
	m_Port = ServerParam::instance->serverPort;
	m_AddReaderId = 0;
	isChanged = FALSE;
	m_AddReaderCom = 0;
	//}}AFX_DATA_INIT
}

BOOL ServerSetting::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ReaderList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE);
	m_ReaderList.InsertColumn(0, "id", LVCFMT_LEFT, 40);
	m_ReaderList.InsertColumn(1, "COM", LVCFMT_LEFT, 60);

	return TRUE;
}


void ServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ServerSetting)
	DDX_Control(pDX, IDC_LIST_READERS, m_ReaderList);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_READER_ID, m_AddReaderId);
	DDX_Text(pDX, IDC_EDIT_READER_COM, m_AddReaderCom);
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
	int oldPort = ServerParam::instance->serverPort; // 保存原来的端口
	UpdateData(TRUE);
	ServerParam::instance->serverPort = m_Port;
	
	if (oldPort != ServerParam::instance->serverPort) // 如果端口修改了, 进行提示
	{
		AfxMessageBox("修改了端口号, 需要重启服务器, 才可以生效!!!");
	}
	
	if (isChanged == TRUE)
	{
		AfxMessageBox("修改了读卡器配置, 需要重启服务器, 才可以生效!!!");
		isChanged = FALSE;
	}
	
	ServerParam::instance->saveConfig(); // 保存配置

	UpdateData(FALSE);
	CDialog::OnOK();
}

void ServerSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);
	
	m_ReaderList.DeleteAllItems();
	int index = 0;
	for (map<int, int>::iterator iter = ServerParam::instance->readers.begin();
		iter != ServerParam::instance->readers.end(); ++iter)
	{
		char name[50];
		sprintf(name, "%d", iter->first);
		m_ReaderList.InsertItem(index, "");
		m_ReaderList.SetItemText(index, 0, name);
		sprintf(name, "%d", iter->second);
		m_ReaderList.SetItemText(index, 1, name);

		++index;
	}
	
	UpdateData(FALSE);
	// Do not call CDialog::OnPaint() for painting messages
}

// 添加读卡器
void ServerSetting::OnButtonAddReader() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (ServerParam::instance->readers.count(m_AddReaderId) == 0 && m_AddReaderId > 0)
	{
		char name[50];
		m_ReaderList.InsertItem(m_ReaderList.GetItemCount(), "");

		sprintf(name, "%d", m_AddReaderId);
		m_ReaderList.SetItemText(m_ReaderList.GetItemCount(), 0, name);

		sprintf(name, "%d", m_AddReaderCom);
		m_ReaderList.SetItemText(m_ReaderList.GetItemCount(), 1, name);

		ServerParam::instance->readers.insert(make_pair(m_AddReaderId, m_AddReaderCom));
	} else {
		AfxMessageBox("输入的读卡器id已经存在或不正确. 请检查!");
	}
	// 刷新UI
	this->SendMessage(WM_PAINT);
	isChanged = TRUE;
	UpdateData(FALSE);
}

// 删除所选读卡器
void ServerSetting::OnButtonDelReader() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i=0; i<m_ReaderList.GetItemCount(); i++)
	{
		if(m_ReaderList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString configName = m_ReaderList.GetItemText(i, 0);
			if(MessageBox("确认删除?", "操作提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				m_ReaderList.DeleteItem(i); // 删除GUI上的项
			}
			break;
		}
	}
// 	int index = m_ReaderList.GetCurSel();
// 	int count = m_ReaderList.GetCount();
// 	if (index != LB_ERR && count > 1)
// 	{
// 		int readerId = m_ReaderList.GetItemData(index);
// 		TRACE(CString(i2str(index)) + "," +i2str(readerId) + "\n");
// 
// 		for (map<int, int>::iterator iter = ServerParam::instance->readers.begin(); iter != ServerParam::instance->readers.end();)
// 		{
// 			if (iter->first == readerId)
// 			{
// 				ServerParam::instance->readers.erase(iter++);
// 			}
// 			else
// 			{
// 				++iter;
// 			}
// 		}
// 
// 		m_ReaderList.DeleteString(index);
// 
// 		if (++index < count)
// 		{
// 			m_ReaderList.SetCurSel(index);
// 		} else {
// 			m_ReaderList.SetCurSel(0);
// 		}
// 	}
	isChanged = TRUE;
	UpdateData(FALSE);
}
