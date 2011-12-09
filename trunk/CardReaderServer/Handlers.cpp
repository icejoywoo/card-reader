//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ���������߳�ʵ��
//////////////////////////////////////////////////////////////////////////
#include "Handlers.h"
#include "ServerParam.h"
#include "ServerUtils.h"
#include <vector>

using namespace std;

// GUI�Ͽ�����־��ʾ���߳�
UINT logHandler (LPVOID pParam)
{
	while (TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			CEdit* logWindow = (CEdit*) pParam;
			int len = logWindow->GetWindowTextLength();
			logWindow->SetSel(len,len);
			logWindow->ReplaceSel(Server::getInstance()->log);
			Server::getInstance()->log = ""; // �����־
		}
		Sleep(500); // �ӳ�0.5s
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// Ĭ�ϵ�handlers���� 
//////////////////////////////////////////////////////////////////////////

// TODO: �޸�handler
UINT defaultServerHandler(LPVOID pParam)
{
	Server* serv = (Server*) pParam;
	
	if ((serv->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		SimpleLog::error("����������Socketʧ��");
		return -1;
	}

	struct sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(serv->getPort());
	
	if (bind(serv->server, (struct sockaddr*)&local, sizeof(local)) != 0)
	{
		SimpleLog::error("�������󶨶˿�ʧ��");
		return -2;
	}
	
	if (listen(serv->server, 64) != 0)
	{
		SimpleLog::error("�����������˿�ʧ��");
		return -3;
	}
	
	// �Զ������ķ��ʿ���, �ڷ�����������ʱ����г�ʼ������
	if (serv->readerCount != ServerParam::instance->readerCount) // �����������������仯ʱ
	{
		serv->readerCount = ServerParam::instance->readerCount;
		serv->readerUsage.resize(serv->readerCount);
		for (vector<int>::iterator iter = serv->readerUsage.begin(); iter != serv->readerUsage.end(); ++iter)
		{
			*iter = 0; // ��ʼ�������б�
		}
	}

	SOCKET client;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);
	SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(serv->getPort()));
	AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, ����ȴ����е�
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET) // ���ܿͻ���socketʧ��
		{
			SimpleLog::warn(CString("���տͻ�������ʧ��, ����") + inet_ntoa(from.sin_addr));
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));

		char buff[512]; // buffer

		// ���տͻ��˵�����, ���ȶ�ȡ������id
		int size = recv(client, buff, 512, 0);
		buff[size] = '\0';
		
		int cardId = atoi(buff); // ��������
		if (cardId > 0 && cardId <= serv->readerCount) // �ж�cardId�Ƿ�Ϸ�
		{
			SimpleLog::info(CString("���ն�������: ") + i2str(cardId));
			serv->addToWaitList(cardId, client); // ��ӵ��ȴ��������
			SimpleLog::info(CString("��������ӵ�������[") + i2str(cardId) + "]�ȴ�������...");
		}
		else
		{
			SimpleLog::info(CString("���ն���������Ч, ��������: ") + i2str(cardId));
			closesocket(client); // �ر�socket
		}
		
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam )
{
	while (true)
	{
		// �����ٽ���, Ѱ���Ƿ��ж��������ڵȴ�״̬
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		for (int i = 0; i < Server::getInstance()->readerUsage.size(); ++i) // Ѱ��δʹ�õĶ�����
		{
			if (0 == Server::getInstance()->readerUsage[i] && !Server::getInstance()->waitList[i].empty())
			{
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)i);
				Server::getInstance()->readerUsage[i] = 1; // ��Ƕ�����Ϊ����ʹ��
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->g_cs));
		Sleep(100); // ����100ms, ��������ʵ��޸�
	}

	return 0;
}


// TODO: �޸�handler, ��ȡ������������
UINT defaultClientHandler (LPVOID pParam)
{
	int cardId = ((int) pParam);
	SOCKET client = Server::getInstance()->getSocketByCardId(cardId); // ȡ����Ӧ�����������е�socket
	char buff[512]; // buffer

	sendData(client, "Ready"); // ���߿ͻ����Ѿ�׼���������Բ���

	CString operationName;
	int resultCode;
	while(operationName != "quit")
	{
		// ���տͻ��˵�����
		receiveData(client, buff, 512);
		if ((resultCode= parseCommand(client, cardId, buff, operationName)) == 0)
		{
			SimpleLog::info("[" + operationName + "]�����ɹ�");
		} else {
			SimpleLog::info("[" + operationName + "]����ʧ��, ������: " + i2str(resultCode));
		}
		// ��������͵��ͻ���
		sendData(client, resultCode);
	}
	
	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);

	// ������������Ϊ����
	EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->readerUsage[cardId] = 0;  // ������ɺ�, ����Ϊ����״̬
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	return 0;
}

// ������
UINT helloClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	char buff[512]; // buffer
	
 	sprintf(buff, "Hello."); // ��������, ������Hello
// 	int size = send(client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("��������: ") + buff);

	sendData(client, buff);
	
	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);
	
	return 0;
}
