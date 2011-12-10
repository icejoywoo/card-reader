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
		// ��ʼ����¼��ǰ������״̬�б�
		serv->readerUsage.resize(serv->readerCount);
		// ��ʼ��timeout�б�
		serv->timeoutList.resize(serv->readerCount);

		for (int i = 0; i < serv->readerCount; ++i)
		{
			serv->readerUsage[i] = 0; // ��ʼ�������б�
			serv->timeoutList[i] = GetTickCount();
			serv->timeout[i] = 100000; // ��ʱ��ʼ��Ϊ100s
			serv->clients[i] = INVALID_SOCKET; // ��ʼ����ǰ�ͻ����б�
		}
	}

	SOCKET client;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);
	SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(serv->getPort()));

	AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, ����ȴ����е�
	//AfxBeginThread(serv->timeoutListHandler, NULL); // ������ʱ�����߳�, �ֶ����Ե�ʱ����Թر�

	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET) // ���ܿͻ���socketʧ��, ���ڹرշ�������ʱ��
		{
			SimpleLog::warn(CString("���տͻ�������ʧ��, ����") + inet_ntoa(from.sin_addr));
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		
		char buff[512]; // buffer

		// ���տͻ��˵�����, ���ȶ�ȡ������id
		int size = recv(client, buff, 512, 0);
		buff[size] = '\0';
		
		int readerId = atoi(buff); // ��������
		if (readerId > 0 && readerId <= serv->readerCount) // �ж�cardId�Ƿ�Ϸ�
		{
			SimpleLog::info(CString("���ն�������: ") + i2str(readerId));
			serv->addToWaitList(readerId, client); // ��ӵ��ȴ��������
			SimpleLog::info(CString("��������ӵ�������[") + i2str(readerId) + "]�ȴ�������...");
		}
		else
		{
			SimpleLog::info(CString("���ն���������Ч, ��������: ") + i2str(readerId));
			closesocket(client); // �ر�socket
		}
		Server::getInstance()->updateTimeout(readerId);
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam )
{
	while (Server::getInstance()->status == TRUE)
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

UINT defaultTimeoutListHandler (LPVOID pParam )
{
	while (Server::getInstance()->status == TRUE)
	{
		// ��ǰ�ͻ���socket
		for (map<int, SOCKET>::iterator iter = Server::getInstance()->clients.begin(); 
		iter != Server::getInstance()->clients.end(); ++iter)
		{
			if (iter->second != INVALID_SOCKET) // �ж��Ƿ������ӵ�socket
			{
				if ((GetTickCount() - Server::getInstance()->timeoutList[iter->first]) > 
					Server::getInstance()->timeout[iter->first])
				{
					SOCKET s = iter->second;
					SimpleLog::warn(CString("������") + i2str(iter->first) + "�ȴ���ʱ, ���̹ر�");
					shutdown(s, SD_BOTH);
					closesocket(s);
					Server::getInstance()->releaseReader(iter->first); // ɾ����������ǰ��socket����
				}
			}
		}
		Sleep(100); // ����100ms, ��������ʵ��޸�
	}
	
	return 0;
}

// TODO: �޸�handler, ��ȡ������������
UINT defaultClientHandler (LPVOID pParam)
{
	int readerId = ((int) pParam);
	SOCKET client = Server::getInstance()->getSocketByReaderId(readerId); // ȡ����Ӧ�����������е�socket
	Server::getInstance()->clients[readerId] = client; // ��ӵ���ǰ�ͻ����б���
	char buff[512]; // buffer

	sendData(client, "Ready"); // ���߿ͻ����Ѿ�׼���������Բ���

	// ��ȡ��ʱ
	int size = recv(client, buff, 512, 0);
	if(size == -1) // �������ݴ����˳�
	{
		Server::getInstance()->clients[readerId] = INVALID_SOCKET;
		closesocket(client);
		return 0;
	}
	buff[size] = '\0';
	int timeout = atoi(buff); // ��������ʱ
	SimpleLog::info(CString("������") + i2str(readerId) + "����ʱΪ: " + i2str(timeout));

	Server::getInstance()->timeout[readerId] = timeout;

	CString operationName;
	int resultCode;
	while(operationName != "quit")
	{
		
		// ���տͻ��˵�����
		if (receiveData(client, buff, 512) == -1) // �������ݴ��󼴿̹ر�
		{
			Server::getInstance()->clients[readerId] = INVALID_SOCKET;
			closesocket(client);
			return 0;
		}
		Server::getInstance()->updateTimeout(readerId);
		if ((resultCode= parseCommand(client, readerId, buff, operationName)) == 0)
		{
			SimpleLog::info("[" + operationName + "]�����ɹ�");
		} else {
			SimpleLog::info("[" + operationName + "]����ʧ��, ������: " + i2str(resultCode));
		}
		// ��������͵��ͻ���
		if (sendData(client, resultCode) == -1) // �������ݳ����̹ر�
		{
			Server::getInstance()->clients[readerId] = INVALID_SOCKET;
			closesocket(client);
			return 0;
		}
		Server::getInstance()->updateTimeout(readerId);
	}
	
	//Sleep(10000);
	Server::getInstance()->clients[readerId] = INVALID_SOCKET;
	shutdown(client, SD_BOTH);
	closesocket(client);

	// ������������Ϊ����
	EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->readerUsage[readerId] = 0;  // ������ɺ�, ����Ϊ����״̬
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
