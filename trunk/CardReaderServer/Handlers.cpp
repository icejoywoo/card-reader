//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ���������߳�ʵ��
//////////////////////////////////////////////////////////////////////////
#include "Handlers.h"
#include "ServerParam.h"
#include "ServerUtils.h"
#include "CustomMessage.h"
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
			::PostMessage(ServerParam::instance->mainFrame, LOG_UPDATE_MSG, 1, 1);
		}
		Sleep(100); // �ӳ�0.5s
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

	char log[512]; // �����־����ʱ�ַ���

	sprintf(log, "�����������ɹ�, �˿�: %d", serv->getPort());
	SimpleLog::info(log);

	AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, �����ȴ����е�
	AfxBeginThread(serv->timeoutListHandler, NULL); // ������ʱ�����߳�, �ֶ����Ե�ʱ����Թر�

	while (true)
	{
		clientSocket = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (clientSocket == INVALID_SOCKET) // ���ܿͻ���socketʧ��, ���ڹرշ�������ʱ��
		{
			sprintf(log, "���տͻ�������ʧ��, ����: %s", inet_ntoa(from.sin_addr));
			SimpleLog::warn(log);

			break;
		}

		sprintf(log, "���տͻ�������ʧ��, ����: %s", inet_ntoa(from.sin_addr));
		SimpleLog::info(log);
		

		// ���տͻ��˵�����, ���ȶ�ȡ������id
		int readerId; // ��������
		receiveData(clientSocket, readerId);
		if (ServerParam::instance->readerIdSet.count(readerId) > 0 )
		{
			sprintf(log, "���ն�����com��: [%d]", readerId);
			SimpleLog::info(log);

			sendData(clientSocket, "id_ok");
		} else {
			sprintf(log, "���ն�����com��: [%d], ������������", readerId);
			SimpleLog::error(log);		
			
			sendData(clientSocket, "id_wrong");
			closesocket(clientSocket);
			continue;
		}
		

		// ��ȡ��ʱ
		int timeout; // ��������ʱ
		receiveData(clientSocket, timeout);

		sprintf(log, "[������ %d]����ʱΪ: %d", readerId, timeout);
		SimpleLog::info(log);

		sendData(clientSocket, "timeout_ok");
		Client* client = new Client(clientSocket); // newһ��client
		client->setReaderId(readerId);
		client->setTimeout(timeout);
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		Server::getInstance()->addToWaitList(client);
		LeaveCriticalSection(&(Server::getInstance()->g_cs));

		sprintf(log, "���������ӵ�[������ %d]�ĵȴ�������...", readerId);
		SimpleLog::info(log);
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam ) 
{
	char log[512];
	while (Server::getInstance()->status == TRUE)
	{
		// �����ٽ���, Ѱ���Ƿ��ж��������ڵȴ�״̬
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		for (map<int,int>::iterator iter = Server::getInstance()->readerUsage.begin();
			iter != Server::getInstance()->readerUsage.end(); ++iter) // Ѱ��δʹ�õĶ�����
		{
			if (0 == iter->second && !Server::getInstance()->waitList[iter->first].empty())
			{
				sprintf(log, "[������ %d]��ʼ��������...", iter->first);
				SimpleLog::info(log);

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
	char log[512];
	while (Server::getInstance()->status == TRUE) // ����������ʱ����ֻ��Ե�ǰ���ʶ������Ŀͻ���
	{
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		// �������пͻ���
// outter:
// 		for (map<int, list<Client*> >::iterator miter = Server::getInstance()->waitList.begin();
// 			miter != Server::getInstance()->waitList.end() ; ++miter)
// 		{
// 			list<Client*> l = miter->second;
// 
// 			for (list<Client*>::iterator liter = l.begin(); liter != l.begin(); ++liter)
// 			{
// 				if ((*liter)->isOvertime()) // �ͻ��������ʱ, ��ֱ�ӹر���socket
// 				{
// 					(*liter)->release();
// 					Server::getInstance()->waitList[miter->first].remove((*liter)); // ɾ���ȴ��б��еĳ�ʱ�Ŀͻ���, ���������Ӻ���ܻ��ڴ�й©
// 					delete (*liter); // ɾ���ڴ�
// 					sprintf(log, "[������ %d]�Ŀͻ���[%d]��ʱ, �ӵȴ�������ɾ��", (*liter)->getReaderId(), (*liter)->getSocket());
// 					SimpleLog::error(log);
// 					goto outter;// ɾ��Ԫ�غ�, ��������ѭ��, iterator��Ҫ����
// 				}
// 			}
// 		}
		for (list<Client*>::iterator iter = Server::getInstance()->clients.begin();
			iter != Server::getInstance()->clients.end(); ++iter)
		{
			if((*iter)->isOvertime())
			{
				sprintf(log, "[������ %d]�Ŀͻ���[%d]��ʱ, ����ɾ��", (*iter)->getReaderId(), (*iter)->getSocket());
				SimpleLog::error(log);
				(*iter)->release();
				Server::getInstance()->clients.remove(*iter);
				break;
			}
		}
		
		LeaveCriticalSection(&(Server::getInstance()->g_cs));
		Sleep(10); // ����100ms, ��������ʵ��޸�
	}
	
	return 0;
}

// TODO: �޸�handler, ��ȡ������������
UINT defaultClientHandler (LPVOID pParam)
{
	int readerId = ((int) pParam);
	Client* client = Server::getInstance()->getClientByReaderId(readerId); // ȡ����Ӧ�����������е�socket

	char buff[512]; // buffer
	char log[512];

	client->sendData("Ready"); // ���߿ͻ����Ѿ�׼���������Բ���
	client->updateTimeout();

	string operationName;
	int resultCode;
	while(operationName.compare("quit") != 0)
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
			{
				sprintf(log, "[������ %d][%s]�����ɹ�", readerId, operationName.c_str());
				SimpleLog::info(log);
			}
		} else {
			sprintf(log, "[������ %d][%s]����ʧ��, ������: %d", readerId, operationName.c_str(), resultCode);
			SimpleLog::error(log);
		}
		client->updateTimeout();
		// ��������͵��ͻ���
		if (client->sendData(resultCode) == -1) // �������ݳ������̹ر�
		{
			break;
		}
	}

	EnterCriticalSection(&(Server::getInstance()->g_cs));
	// �ͷŶ�����
	Server::getInstance()->releaseReader(readerId);
	client->release();
	delete client; // ��Ҫ��ָ��ɾ��
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	return 0;
}