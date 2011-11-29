//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// Comment: 客户端用来连接到服务器的封装, 并发送数据, 默认开启日志记录
//////////////////////////////////////////////////////////////////////////
#include "ClientConnection.h"

ClientConnection::ClientConnection(char* servername, int p, int id)
{
	ASSERT(!WSAStartup(0x101, &this->wsaData)); //初始化winsock环境
	this->serverName = servername;
	ASSERT(p >= 0 && p <= 65535); //保证端口的输入范围是正确的
	this->port = p;

	this->isLog = true; // default 记录日志
	this->readerId = id;

	this->client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server;
	this->getServerAddr(server);
	connect(this->client, (struct sockaddr*)&server, sizeof(server)); // 连接socket
	if (this->isLogged())
	{
		SimpleLog::info(CString("连接服务器") + this->serverName + "成功"); // log
	}
	
}

ClientConnection::~ClientConnection()
{
	closesocket(this->client);
	WSACleanup(); // 清理winsock环境
}

void ClientConnection::getServerAddr(struct sockaddr_in& server)
{
	// 设置server地址
	struct hostent *hp;
	unsigned int addr;
	
	if(inet_addr(this->serverName)==INADDR_NONE)
	{
		hp=gethostbyname(this->serverName);
	}
	else
	{
		addr=inet_addr(this->serverName);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(this->port);
}

int ClientConnection::recvData(char* data)
{
	char buff[512];
	sprintf(buff, "%d", this->readerId); // 请求读卡器的id
	if (this->isLogged())
		SimpleLog::info(CString("请求id: ") + buff);
	send(this->client, buff, sizeof(buff), 0);
	
	memset(buff, 0, 512);
	int z = recv(this->client, buff, 512, 0);
	ASSERT(z != -1); // 接收到的数据长度为-1, 表明程序错误
	buff[z] = '\0'; // c-style字符串
	if (this->isLogged())
		SimpleLog::info(CString("从服务器接收到的数据: ") + buff);
	data = buff;
	return z;
}

bool ClientConnection::isLogged()
{
	return this->isLog;
}

void ClientConnection::setLog(bool log)
{
	this->isLog = log;
}
