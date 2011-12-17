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
	this->port = DEFAULT_PORT;
	//this->log = "";

	this->clientHandler = defaultClientHandler;
	//this->clientHandler = helloClientHandler;
	this->serverHandler = defaultServerHandler;
	this->waitListHandler = defaultWaitListHandler;
	this->timeoutListHandler = defaultTimeoutListHandler;
	InitializeCriticalSection(&(this->g_cs));
	this->status = FALSE;
}

Server::~Server()
{
	WSACleanup(); // clean up winsock
	delete this->instance;
}

int Server::start()
{
	this->status = TRUE;
	HANDLE thread = AfxBeginThread(this->serverHandler, this);
	return 0;
}

int Server::stop()
{
	// shutdown��ʧ��
// 	if (shutdown(this->server, SD_SEND) != 0)
// 	{
// 		return -1;
// 	}
	if (closesocket(this->server) != 0)
	{
		SimpleLog::error("�ر�ʧ��");
		return -2;
	}
	this->status = FALSE;
	SimpleLog::info("�������ѹر�");

	// �ָ���������ԭʼ״̬
	readerUsage.clear();
	waitList.clear(); // ������ʱ��ɾ���ȴ����п��Ա�֤�ȴ����м�������

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
	EnterCriticalSection(&(Server::getInstance()->g_cs));
	this->clients.remove(this->waitList[readerId].front());
	this->waitList[readerId].erase(this->waitList[readerId].begin());
	this->readerUsage[readerId] = 0;  // ������ɺ�, ����Ϊ����״̬
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	SimpleLog::info(CString("�ͷ�[������ ") + i2str(readerId) + "]");
}

/// Server�������