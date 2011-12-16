//////////////////////////////////////////////////////////////////////////
// FileName: Server.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: 服务器端的简单封装
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CardReaderServerDlg.h"
#include "ServerUtils.h"

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	this->port = DEFAULT_PORT;
	this->log = "";

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
	// shutdown会失败
// 	if (shutdown(this->server, SD_SEND) != 0)
// 	{
// 		return -1;
// 	}
	if (closesocket(this->server) != 0)
	{
		SimpleLog::error("关闭失败");
		return -2;
	}
	this->status = FALSE;
	SimpleLog::info("服务器已关闭");

	// 恢复服务器的原始状态
	readerUsage.clear();
	waitList.clear(); // 重启的时候不删除等待队列可以保证等待队列继续处理
	clients.clear();

	return 0;
}

int Server::restart()
{
	int result = 0;
	this->stop();
	if ((result = this->start()) != 0)
	{
		SimpleLog::error("重启失败");
		return result;
	}
	//SimpleLog::info(CString("服务器重启成功, 端口: ") + i2str(Server::getInstance()->getPort()));
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
	this->clients[client] = client;
}

Client* Server::getClientByReaderId(int readerId)
{
	return this->waitList[readerId].at(0);
}

Client* Server::getClientByReaderIdAndDelete(int readerId)
{
	Client* result = this->waitList[readerId].at(0);
	Client* beginClient = this->waitList[readerId][0];
	this->clients.erase(beginClient);
	this->waitList[readerId].erase(this->waitList[readerId].begin());
	return result;
}

void Server::releaseReader(int readerId) {
	this->readerUsage[readerId] = 0;
	SimpleLog::info(CString("释放读卡器") + i2str(readerId));
}

/// Server定义结束