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

// GUI�Ͽ�����־��ʾ���߳�, ���û0.5s����һ����־��ʾ
UINT logHandler (LPVOID pParam)
{
	while (Server::getInstance()->status == TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			::PostMessage(ServerParam::instance->mainFrame, LOG_UPDATE_MSG, 1, 1);
		}
		Sleep(100); // �ӳ�0.1s
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

	// TODO: ��ʼ��������(��udp���Ե�ʱ��ʹ��, �����Ѿ�ת��udp)
	if (InitUDPComm() == -1) {
		AfxMessageBox("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		SimpleLog::error("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		return INIT_FAILED; // �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
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

	CWinThread* waitListThread = AfxBeginThread(serv->waitListHandler, NULL); // �����ȴ������߳�, ����ȴ����е�
	waitListThread->m_bAutoDelete = TRUE;
	CWinThread* timeoutListThread = AfxBeginThread(serv->timeoutListHandler, NULL); // ������ʱ�����߳�, �ֶ����Ե�ʱ����Թر�
	waitListThread->m_bAutoDelete = TRUE;

	while (Server::getInstance()->status == TRUE)
	{
		clientSocket = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (clientSocket == INVALID_SOCKET) // ���ܿͻ���socketʧ��, ���ڹرշ�������ʱ��
		{
			sprintf(log, "���տͻ�������ʧ��, ����: %s", inet_ntoa(from.sin_addr));
			SimpleLog::warn(log);

			break;
		}

		sprintf(log, "���տͻ�������, ����: %s:%d", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
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
		Client* client = new Client(clientSocket); // newһ��client, �ڴ�����client��delete
		client->setReaderId(readerId);
		client->setTimeout(timeout);
		EnterCriticalSection(&(Server::getInstance()->readerUsage_cs));
		Server::getInstance()->addToWaitList(client);
		LeaveCriticalSection(&(Server::getInstance()->readerUsage_cs));

		sprintf(log, "��������ӵ�[������ %d]�ĵȴ�������...", readerId);
		SimpleLog::info(log);
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam ) 
{
	while (Server::getInstance()->status == TRUE)
	{
		// �����ٽ���, Ѱ���Ƿ��ж��������ڵȴ�״̬
		EnterCriticalSection(&(Server::getInstance()->readerUsage_cs));
		for (map<int,int>::iterator iter = Server::getInstance()->readerUsage.begin();
			iter != Server::getInstance()->readerUsage.end(); ++iter) // Ѱ��δʹ�õĶ�����
		{
			if (0 == iter->second && !Server::getInstance()->waitList[iter->first].empty())
			{
				Server::getInstance()->getClientByReaderId(iter->first)->updateTimeout();
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)iter->first)->m_bAutoDelete = TRUE;
				Server::getInstance()->readerUsage[iter->first] = 1; // ��Ƕ�����Ϊ����ʹ��
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->readerUsage_cs));
		Sleep(100); // ����100ms, ��������ʵ��޸�
	}
	return 0;
}

UINT defaultTimeoutListHandler (LPVOID pParam )
{
	char log[512];
	while (Server::getInstance()->status == TRUE) // ����������ʱ����ֻ��Ե�ǰ���ʶ������Ŀͻ���
	{
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
// 					Server::getInstance()->waitList[miter->first].remove((*liter)); // ɾ���ȴ��б��еĳ�ʱ�Ŀͻ���, ��������Ӻ���ܻ��ڴ�й©
// 					delete (*liter); // ɾ���ڴ�
// 					sprintf(log, "[������ %d]�Ŀͻ���[%d]��ʱ, �ӵȴ�������ɾ��", (*liter)->getReaderId(), (*liter)->getSocket());
// 					SimpleLog::error(log);
// 					goto outter;// ɾ��Ԫ�غ�, ��������ѭ��, iterator��Ҫ����
// 				}
// 			}
// 		}
		EnterCriticalSection(&(Server::getInstance()->clients_cs));
	
		for (list<Client*>::iterator iter = Server::getInstance()->clients.begin();
			iter != Server::getInstance()->clients.end(); ++iter)
		{
			if((*iter)->isOvertime())
			{
				char name[50];
				(*iter)->getName(name);
				sprintf(log, "[������ %d]�Ŀͻ���[%s]��ʱ, ����ɾ��", (*iter)->getReaderId(), name);
				SimpleLog::warn(log);
				(*iter)->release();
				Server::getInstance()->clients.remove(*iter);
				break;
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->clients_cs));	
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

	if (client->isAvailable()) // ����ͻ�����Ч�ͷ���
	{
		client->sendData("Ready"); // ���߿ͻ����Ѿ�׼���������Բ���
		sprintf(log, "[������ %d]��ʼ��������...", client->getReaderId());
		SimpleLog::info(log);
	} else {

	}
	
	client->updateTimeout();

	string operationName;
	int resultCode;
	while(operationName.compare("quit") != 0)
	{
		// ���տͻ��˵�����
		if (!client->isAvailable() || client->receiveData(buff, 512) == -1) // �������ݴ��󼴿̹ر�
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
		if (!client->isAvailable() || client->sendData(resultCode) == -1) // �������ݳ����̹ر�
		{
			break;
		}
	}

	// �ͷŶ�����
	Server::getInstance()->releaseReader(readerId);
	if (client->isAvailable()) 
	{
		sprintf(log, "�ͷ�[������ %d]", readerId);
		SimpleLog::info(log);
	}
	client->release();
	delete client; // ��Ҫ��ָ��ɾ��

	return 0;
}
