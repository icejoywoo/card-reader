//////////////////////////////////////////////////////////////////////////
// FileName: Server.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: �������˵ļ򵥷�װ
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CardReaderServerDlg.h"
#include "ServerUtils.h"

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	//this->log = "";

	this->clientHandler = defaultClientHandler;
	//this->clientHandler = helloClientHandler;
	this->serverHandler = defaultServerHandler;
	this->waitListHandler = defaultWaitListHandler;
	this->timeoutListHandler = defaultTimeoutListHandler;
	InitializeCriticalSection(&(this->readerUsage_cs));
	InitializeCriticalSection(&(this->clients_cs));
	this->status = FALSE;
}

Server::~Server()
{
	WSACleanup(); // clean up winsock
	delete this->instance;
}

int Server::start()
{
	this->setPort(ServerParam::instance->serverPort);

	if ((this->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		SimpleLog::error("����������Socketʧ��");
		return -1;
	}

	struct sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(this->getPort());
	
	if (bind(this->server, (struct sockaddr*)&local, sizeof(local)) != 0)
	{
		SimpleLog::error("�������󶨶˿�ʧ��");
		return -2;
	}
	
	if (listen(this->server, 128) != 0)
	{
		SimpleLog::error("�����������˿�ʧ��");
		return -3;
	}
	this->status = TRUE; // �޸ķ�����״̬
	AfxBeginThread(this->serverHandler, this)->m_bAutoDelete = TRUE;
	AfxBeginThread(logHandler, NULL)->m_bAutoDelete = TRUE;
	return 0;
}

int Server::stop()
{
	// shutdown��ʧ��
// 	if (shutdown(this->server, SD_SEND) != 0)
// 	{
// 		return -1;
// 	}
// 	if (closesocket(this->server) != 0)
// 	{
// 		SimpleLog::error("�ر�ʧ��");
// 		return -2;
// 	}
	shutdownAndCloseSocket(this->server);
	for (list<Client*>::iterator iter = clients.begin(); iter != clients.end(); ++iter)
	{
		shutdownAndCloseSocket((*iter)->getSocket());
	}


	SimpleLog::info("�������ѹر�");

	// �ָ���������ԭʼ״̬
	readerUsage.clear();
	waitList.clear(); // ������ʱ��ɾ���ȴ����п��Ա�֤�ȴ����м�������
	EnterCriticalSection(&(Server::getInstance()->clients_cs));
	ServerParam::instance->readers.clear();
	LeaveCriticalSection(&(Server::getInstance()->clients_cs));	
	this->status = FALSE;

	return 0;
}

int Server::restart()
{
	int result = 0;
	this->stop();
	if ((result = this->start()) != 0)
	{
		SimpleLog::error("����ʧ��");
		return result;
	}
	//SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(Server::getInstance()->getPort()));
	return 0;
}

int Server::setPort(int &port)
{
	this->port = port;
	// return this->restart();
	//WSACleanup();
	//WSAStartup(MAKEWORD(2,2), &this->wsaData);
	return 0;
}

void Server::addToWaitList(Client* client)
{
	this->waitList[client->getReaderId()].push_back(client);
	this->clients.push_back(client);
}

Client* Server::getClientByReaderId(int readerId)
{
	return this->waitList[readerId].front();
}

void Server::releaseReader(int readerId) {
	// ������������Ϊ����
	EnterCriticalSection(&(Server::getInstance()->readerUsage_cs));
	this->clients.remove(this->waitList[readerId].front());
	this->waitList[readerId].erase(this->waitList[readerId].begin());
	this->readerUsage[readerId] = 0;  // ������ɺ�, ����Ϊ����״̬
	LeaveCriticalSection(&(Server::getInstance()->readerUsage_cs));
}

/// Server�������