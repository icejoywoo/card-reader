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

typedef struct _clientParam 
{
	Server* server;
	SOCKET client;
} ClientParam;

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	this->port = DEFAULT_PORT;
	this->log = "";

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
	SimpleLog::info(CString("服务器重启成功, 端口: ") + i2str(Server::getInstance()->getPort()));
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
	SimpleLog::info(CString("服务器启动成功, 端口: ") + i2str(serv->getPort()));
	serv->log += formatLog(CString("服务器启动成功, 端口: ") + i2str(serv->getPort()));
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET)
		{
			break;
		}
		SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
		serv->log += formatLog(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
		ClientParam clientParam;
		clientParam.server = serv;
		clientParam.client = client;
		AfxBeginThread(serv->clientHandler, (LPVOID)&clientParam);
	}
	return 0;
}

// TODO: 修改handler, 读取读卡器的数据
UINT defaultClientHandler (LPVOID pParam)
{
	ClientParam* clientParam = (ClientParam *) pParam;
	char buff[512];
	SOCKET client = clientParam->client;

// 	sprintf(buff, "Hello."); // 测试数据, 仅发送Hello
// 	int size = send(clientParam->client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("发送数据: ") + buff);
// 	clientParam->server->log += formatLog(CString("发送数据: ") + buff);

	// 接收读卡器的cardId
	int size = recv(client, buff, 512, 0);
	buff[size] = '\0';
	int cardId = atoi(buff);

	CString ip; // 读卡器对应的ip
	int port; // 读卡器对应的端口号
	Communicator communicator; // 与读卡器通信的通信其
	
	GetIpAndPort(ip, port, cardId, ServerParam::instance); 
	GetOneUDPCommunicator()


	//Sleep(10000);
	shutdown(clientParam->client, SD_BOTH);
	closesocket(clientParam->client);

	return 0;
}
