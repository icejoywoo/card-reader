//////////////////////////////////////////////////////////////////////////
// FileName: Server.cpp
// Creator: icejoywoo
// Date: 2011.11.29
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
	//HANDLE thread = AfxBeginThread(this->serverHandler, 0);
	if ((this->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		return -1;
	}
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(this->port);
	
	if (bind(server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return -2;
	}
	
	if (listen(server, 64) != 0)
	{
		return -3;
	}
	
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);
	SimpleLog::info("Server Ready");
	while (true)
	{
		client = accept(server, (struct sockaddr*) &from, &fromlen);
		SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
	}
	return 0;
}

int Server::stop()
{
	if (shutdown(this->server, SD_BOTH) != 0)
	{
		return -1;
	}
	if (closesocket(this->server) != 0)
	{
		return -2;
	}
	return 0;
}

int Server::restart()
{
	int result = 0;
	if ((result = this->stop()) != 0)
		return result;
	if ((result = this->start()) != 0)
		return result;
	return 0;
}

int Server::setPort(int port)
{
	this->port = port;
	return this->restart();
}

UINT Server::defaultServerHandler(LPVOID pParam)
{

}