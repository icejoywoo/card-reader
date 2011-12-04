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

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	this->port = DEFAULT_PORT;
	this->log = "";

	this->clientHandler = defaultClientHandler;
	//this->clientHandler = helloClientHandler;
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
		SimpleLog::error("关闭失败");
		return -2;
	}
	SimpleLog::info("服务器已关闭");
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
/// Server定义结束

//////////////////////////////////////////////////////////////////////////
/// 默认的handlers定义 
//////////////////////////////////////////////////////////////////////////

// TODO: 修改handler
UINT defaultServerHandler(LPVOID pParam)
{
	Server* serv = (Server*) pParam;
	
	if ((serv->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		SimpleLog::error("服务器创建Socket失败");
		return -1;
	}
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(serv->getPort());
	
	if (bind(serv->server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		SimpleLog::error("服务器绑定端口失败");
		return -2;
	}
	
	if (listen(serv->server, 64) != 0)
	{
		SimpleLog::error("服务器监听端口失败");
		return -3;
	}
	
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);
	SimpleLog::info(CString("服务器启动成功, 端口: ") + i2str(serv->getPort()));
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET)
		{
			break;
		}
		SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
		AfxBeginThread(serv->clientHandler, (LPVOID)client);
	}
	return 0;
}

// TODO: 修改handler, 读取读卡器的数据
UINT defaultClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	char buff[512]; // buffer

// 	sprintf(buff, "Hello."); // 测试数据, 仅发送Hello
// 	int size = send(clientParam->client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("发送数据: ") + buff);
// 	clientParam->server->log += formatLog(CString("发送数据: ") + buff);

	// 接收读卡器的cardId
	int size = recv(client, buff, 512, 0);
	buff[size] = '\0';

	SimpleLog::info(CString("接收数据: ") + buff);

	CString operationName;
	int resultCode;
	if ((resultCode= parseCommand(client, buff, operationName)) == 0)
	{
		SimpleLog::info("[" + operationName + CString("]操作成功"));
	} else {
		SimpleLog::info("[" + operationName + CString("]操作失败, 错误码: ") + i2str(resultCode));
	}
	
	// 将结果发送到客户端
	sendData(client, resultCode);

	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);

	return 0;
}

//
UINT helloClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	char buff[512]; // buffer
	
 	sprintf(buff, "Hello."); // 测试数据, 仅发送Hello
// 	int size = send(client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("发送数据: ") + buff);

	sendData(client, buff);
	
	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);
	
	return 0;
}
