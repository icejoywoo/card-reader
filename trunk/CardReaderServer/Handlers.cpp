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
#include <algorithm>

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
		serv->readerUsage[*iter] = 0; // ��ʼ�������б�, ��δʹ��
	}

	SOCKET clientSocket;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);
//	SimpleLog::info(CString("�����������ɹ�, ") + "IP:" + inet_ntoa(local.sin_addr) + ", �˿�: " + i2str(serv->getPort()));
	SimpleLog::info(CString("�����������ɹ�, ") + "�˿�: " + i2str(serv->getPort()));

	AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, ����ȴ����е�
	AfxBeginThread(serv->timeoutListHandler, NULL); // ������ʱ�����߳�, �ֶ����Ե�ʱ����Թر�

	while (true)
	{
		clientSocket = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (clientSocket == INVALID_SOCKET) // ���ܿͻ���socketʧ��, ���ڹرշ�������ʱ��
		{
			SimpleLog::warn(CString("���տͻ�������ʧ��, ����") + inet_ntoa(from.sin_addr));
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		

		// ���տͻ��˵�����, ���ȶ�ȡ������id
		int readerId; // ��������
		receiveData(clientSocket, readerId);
		if (ServerParam::instance->readerIdSet.count(readerId) > 0 )
		{
			SimpleLog::info(CString("���ն�����com��: [") + i2str(readerId) + "]");			
			sendData(clientSocket, "id_ok");
		} else {
			SimpleLog::error(CString("���ն�����com��: [") + i2str(readerId) + "], ������������");			
			sendData(clientSocket, "id_wrong");
			closesocket(clientSocket);
			continue;
		}
		

		// ��ȡ��ʱ
		int timeout; // ��������ʱ
		receiveData(clientSocket, timeout);
		
		SimpleLog::info(CString("[������ ") + i2str(readerId) + "]����ʱΪ: " + i2str(timeout));
		sendData(clientSocket, "timeout_ok");
		Client* client = new Client(clientSocket); // newһ��client
		client->setReaderId(readerId);
		client->setTimeout(timeout);
		Server::getInstance()->addToWaitList(client);
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
		for (map<int,int>::iterator iter = Server::getInstance()->readerUsage.begin();
			iter != Server::getInstance()->readerUsage.end(); ++iter) // Ѱ��δʹ�õĶ�����
		{
			if (0 == iter->second && !Server::getInstance()->waitList[iter->first].empty())
			{
				SimpleLog::info(CString("��ʼ����[������ ") + i2str(iter->first) + "]������...");
				Server::getInstance()->getClientByReaderId(iter->first)->updateTimeout();
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)iter->first);
				Server::getInstance()->readerUsage[iter->first] = 1; // ��Ƕ�����Ϊ����ʹ��
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
		// �������пͻ���
		for (map<Client*, int>::iterator iter = Server::getInstance()->clients.begin();
			iter != Server::getInstance()->clients.end() ; ++iter)
		{
			if (iter->first->isOvertime()) // �ͻ��������ʱ, ��ֱ�ӹر���socket
			{
				iter->first->release();
// 				Server::getInstance()->waitList[iter->second].remove((iter->first)); // ɾ���ȴ��б��еĳ�ʱ�Ŀͻ���
 				SimpleLog::info(CString("[������ ") + i2str(iter->second) + "]�Ŀͻ���" + i2str(iter->first->getSocket()) + "��ʱ, �ӵȴ�������ɾ��");
				break;
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
	Client* client = Server::getInstance()->getClientByReaderId(readerId); // ȡ����Ӧ�����������е�socket

	char buff[512]; // buffer

	client->sendData("Ready"); // ���߿ͻ����Ѿ�׼���������Բ���
	client->updateTimeout();

	CString operationName;
	int resultCode;
	while(operationName != "quit")
	{
		
		// ���տͻ��˵�����
		if (client->receiveData(buff, 512) == -1) // �������ݴ��󼴿̹ر�
		{
			break;
		}
		client->updateTimeout();
		if ((resultCode= parseCommand(client, readerId, buff, operationName)) >= 0)
		{
			if (Server::getInstance()->status == TRUE)
				SimpleLog::info(CString("[������ ") + i2str(readerId) + "][" + operationName + "]�����ɹ�");
		} else {
			SimpleLog::error(CString("[������ ") + i2str(readerId) + "][" + operationName + "]����ʧ��, ������: " + i2str(resultCode));
		}
		client->updateTimeout();
		// ��������͵��ͻ���
		if (client->sendData(resultCode) == -1) // �������ݳ����̹ر�
		{
			break;
		}
	}
	// �ͷŶ�����
	Server::getInstance()->releaseReader(readerId);
	client->release();
//	delete client; // ��Ҫ��ָ��ɾ��

	// ������������Ϊ����
	EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->readerUsage[readerId] = 0;  // ������ɺ�, ����Ϊ����״̬
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	return 0;
}
