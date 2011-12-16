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

			Server::getInstance()->log = "";
			Server::getInstance()->log.Empty(); 
			Server::getInstance()->log.ReleaseBuffer();// �����־

			if (logWindow->GetLineCount() > 1000) // ����1000�����һ��
			{
				logWindow->SetWindowText("");
			}
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
	
	// TODO: ��ʼ��������(��udp���Ե�ʱ��ʹ��, ������������ʱ��Ӧ��ɾ��)
	if (InitUDPComm() == -1) {
		AfxMessageBox("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		SimpleLog::error("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		return INIT_FAILED; // �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
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
	for (set<int>::iterator iter = ServerParam::instance->readerIdSet.begin(); 
			iter != ServerParam::instance->readerIdSet.end(); ++iter) // ������ǰ������id�ļ���
	{
		serv->readerUsage[*iter] = 0; // ��ʼ�������б�
		serv->clientTimeout[*iter] = 60000; // ��ǰ��ʱʱ��
		serv->clients[*iter] = INVALID_SOCKET; // ��ʼ����ǰ�ͻ����б�
	}

	SOCKET client;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);
//	SimpleLog::info(CString("�����������ɹ�, ") + "IP:" + inet_ntoa(local.sin_addr) + ", �˿�: " + i2str(serv->getPort()));
	SimpleLog::info(CString("�����������ɹ�, ") + "�˿�: " + i2str(serv->getPort()));

	AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, ����ȴ����е�
	AfxBeginThread(serv->timeoutListHandler, NULL); // ������ʱ�����߳�, �ֶ����Ե�ʱ����Թر�

	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET) // ���ܿͻ���socketʧ��, ���ڹرշ�������ʱ��
		{
			SimpleLog::warn(CString("���տͻ�������ʧ��, ����") + inet_ntoa(from.sin_addr));
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		

		// ���տͻ��˵�����, ���ȶ�ȡ������id
		int readerId; // ��������
		receiveData(client, readerId);
		if (ServerParam::instance->readerIdSet.count(readerId) > 0 )
		{
			SimpleLog::info(CString("���ն�����com��: [") + i2str(readerId) + "]");			
			sendData(client, "id_ok");
		} else {
			SimpleLog::error(CString("���ն�����com��: [") + i2str(readerId) + "], ������������");			
			sendData(client, "id_wrong");
			closesocket(client);
			continue;
		}
		

		// ��ȡ��ʱ
		int timeout; // ��������ʱ
		receiveData(client, timeout);
		
		SimpleLog::info(CString("[������ ") + i2str(readerId) + "]����ʱΪ: " + i2str(timeout));
		
		Server::getInstance()->addToTimeout(client, timeout);
		sendData(client, "timeout_ok");
		
		serv->addToWaitList(readerId, client); // ��ӵ��ȴ��������
		serv->addToTimeout(client, timeout); // ����ͻ��˳�ʱ��Ϣ
		SimpleLog::info(CString("��������ӵ�[������ ") + i2str(readerId) + "]�ȴ�������...");
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam ) 
{
	while (Server::getInstance()->status == TRUE)
	{
		// �����ٽ���, Ѱ���Ƿ��ж��������ڵȴ�״̬
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		for (int readerId = 0; readerId < Server::getInstance()->readerUsage.size(); ++readerId) // Ѱ��δʹ�õĶ�����
		{
			if (0 == Server::getInstance()->readerUsage[readerId] && !Server::getInstance()->waitList[readerId].empty())
			{
				SimpleLog::info(CString("��ʼ����[������ ") + i2str(readerId) + "]������...");
				Server::getInstance()->updateTimeout(readerId); // ��ʼ����, ������ʱ��ʼʱ��
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)readerId);
				Server::getInstance()->readerUsage[readerId] = 1; // ��Ƕ�����Ϊ����ʹ��
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->g_cs));
		Sleep(100); // ����100ms, ��������ʵ��޸�
	}

	return 0;
}

UINT defaultTimeoutListHandler (LPVOID pParam )
{
	while (Server::getInstance()->status == TRUE) // ����������ʱ����ֻ��Ե�ǰ���ʶ������Ŀͻ���
	{
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		// ��ǰ�ͻ���socket
		for (int readerId = 0; readerId < Server::getInstance()->readerUsage.size(); ++readerId)
		{
			if (1 == Server::getInstance()->readerUsage[readerId] && 
				(GetTickCount() - Server::getInstance()->timepassed[readerId]) > Server::getInstance()->clientTimeout[readerId])
			{
				SimpleLog::error(CString("������") + i2str(readerId) + "�ȴ���ʱ, ���̹ر�");
				SOCKET s = Server::getInstance()->clients[readerId];
				shutdown(s, SD_BOTH);
				closesocket(s);
				Server::getInstance()->readerUsage[readerId] = 0; // �ͷŶ�����
			}
		}
		
		// TODO: �ڵȴ������е�socket, �������ʱ��, ҲҪɾ��
		for (map<SOCKET, ULONG>::iterator iter = Server::getInstance()->timeout.begin(); 
			iter != Server::getInstance()->timeout.end(); ++iter)
		{
			if ((GetTickCount() - Server::getInstance()->timepassed[iter->first]) > Server::getInstance()->timeout[iter->first])
			{
				SimpleLog::error(CString("�ͻ���") + i2str(iter->first) + "�ȴ���ʱ, ���̹ر�");
				shutdown(iter->first, SD_BOTH);
 				closesocket(iter->first);
				Server::getInstance()->timeout.erase(iter);
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
	int readerId = ((int) pParam);
	SOCKET client = Server::getInstance()->getSocketByReaderIdAndDelete(readerId); // ȡ����Ӧ�����������е�socket

	EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->clients[readerId] = client; // ��ӵ���ǰ�ͻ����б���
	Server::getInstance()->clientTimeout[readerId] = Server::getInstance()->timeout[client];
	Server::getInstance()->timeout.erase(client);
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	char buff[512]; // buffer

	sendData(client, "Ready"); // ���߿ͻ����Ѿ�׼���������Բ���

	CString operationName;
	int resultCode;
	while(operationName != "quit")
	{
		
		// ���տͻ��˵�����
		if (receiveData(client, buff, 512) == -1) // �������ݴ��󼴿̹ر�
		{
			break;
		}
		Server::getInstance()->updateTimeout(readerId);
		if ((resultCode= parseCommand(client, readerId, buff, operationName)) >= 0)
		{
			if (Server::getInstance()->status == TRUE)
				SimpleLog::info(CString("[������ ") + i2str(readerId) + "][" + operationName + "]�����ɹ�");
		} else {
			SimpleLog::error(CString("[������ ") + i2str(readerId) + "][" + operationName + "]����ʧ��, ������: " + i2str(resultCode));
		}
		Server::getInstance()->updateTimeout(readerId);
		// ��������͵��ͻ���
		if (sendData(client, resultCode) == -1) // �������ݳ����̹ر�
		{
			break;
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
