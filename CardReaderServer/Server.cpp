//////////////////////////////////////////////////////////////////////////
// FileName: Server.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: 服务器端的简单封装
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	this->port = DEFAULT_PORT;

	this->clientHandler = defaultClientHandler;
	this->serverHandler = defaultServerHandler;
}

Server::~Server()
{
	WSACleanup(); // clean up winsock
	delete this->instance;
}

int Server::start()
{
	HANDLE thread = AfxBeginThread(this->serverHandler, this);
	return 0;
}

int Server::stop()
{
	// shutdown会失败
// 	if (shutdown(this->server, SD_BOTH) != 0)
// 	{
// 		return -1;
// 	}
	if (closesocket(this->server) != 0)
	{
		return -2;
	}
	return 0;
}

int Server::restart()
{
	int result = 0;
	this->stop();
	if ((result = this->start()) != 0)
		return result;
	return 0;
}

int Server::setPort(int port)
{
	this->port = port;
	return this->restart();
}
/// Server定义结束

//////////////////////////////////////////////////////////////////////////
/// 默认的handlers定义 
//////////////////////////////////////////////////////////////////////////

UINT defaultServerHandler(LPVOID pParam)
{
	Server* serv = (Server*) pParam;
	if ((serv->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		return -1;
	}
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(serv->getPort());
	
	if (bind(serv->server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return -2;
	}
	
	if (listen(serv->server, 64) != 0)
	{
		return -3;
	}
	
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);
	SimpleLog::info("Server Ready");
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
		AfxBeginThread(serv->clientHandler, (LPVOID)client);
	}
	return 0;
}

UINT defaultClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	
	char buff[512];
	
	sprintf(buff, "Hello.");
	int size = send(client, buff, strlen(buff), 0);
	SimpleLog::info(CString("发送数据: ") + buff);
	shutdown(client, SD_BOTH);
	closesocket(client);
	
	return 0;
}