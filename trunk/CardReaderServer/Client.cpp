//////////////////////////////////////////////////////////////////////////
// FileName: Client.cpp
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: 向服务器端请求的客户端类的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Client.h"
#include "ServerUtils.h"

Client::Client(SOCKET s)
{
	this->s = s;
	// closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
// 	BOOL bReuseaddr=TRUE;
// 	::setsockopt(this->s,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL));
	// 处于连接状态的soket在调用closesocket后强制关闭，不经历TIME_WAIT的过程
	BOOL bDontLinger = FALSE;
	setsockopt(this->s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
	
// 	int nNetTimeout=10000;//10秒
// 	//发送时限
// 	setsockopt(this->s,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));
// 	//接收时限
// 	setsockopt(this->s,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));

	//KeepAlive实现
	TCP_KEEPALIVE inKeepAlive = {0}; //输入参数
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE);
	TCP_KEEPALIVE outKeepAlive = {0}; //输出参数
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE);
	unsigned long ulBytesReturn = 0;
	
	//设置socket的keep alive为5秒，并且发送次数为3次
	inKeepAlive.onoff = 1;
	inKeepAlive.keepaliveinterval = 5000; //两次KeepAlive探测间的时间间隔
	inKeepAlive.keepalivetime = 5000; //开始首次KeepAlive探测前的TCP空闭时间
	
	if (WSAIoctl((unsigned int)s, SIO_KEEPALIVE_VALS,	
		(LPVOID)&inKeepAlive, ulInLen,	
		(LPVOID)&outKeepAlive, ulOutLen,	
		&ulBytesReturn, NULL, NULL) == SOCKET_ERROR)	
	{	
		printf("WSAIoctl failed.Error code(%d)!\r\n",WSAGetLastError());	
	}

	this->timeoutStart = ::GetTickCount();
	this->available = TRUE;
	this->_quit = FALSE;
}

Client::~Client()
{
	shutdownAndCloseSocket(s);
}

Client& Client::setReaderId(int readerId)
{
	this->readerId = readerId;
	return *this;
}

// 延时中增加一个特殊的增幅, 根据不同的情况进行调整
Client& Client::setTimeout(ULONG timeout)
{
//	this->timeoutStart = ::GetTickCount();
	this->timeout = timeout + DEFAULT_TIMEOUT_ADDITION;
	return *this;
}

Client& Client::setSocket(SOCKET s)
{
	this->s = s;
	return *this;
}

int Client::getReaderId()
{
	return this->readerId;
}

ULONG Client::getTimeout()
{
	return this->timeout;
}

SOCKET Client::getSocket()
{
	return this->s;
}

Client& Client::updateTimeout()
{
	this->timeoutStart = ::GetTickCount();
	//TRACE(CString("[读卡器 ") + i2str(readerId) + "]更新timeout\n");
	return *this;
}

BOOL Client::isOvertime()
{
	ULONG timePassed = ::GetTickCount() - this->timeoutStart;
	BOOL result = (timePassed >= this->timeout);
	//TRACE(CString("[读卡器 ") + i2str(readerId) + "]是否超时: " + i2str(result) + "\n");
	return result;
}

void Client::release()
{
	shutdownAndCloseSocket(s);
//	closesocket(s);
	this->available = FALSE;
	this->_quit = TRUE;
}

int Client::sendData(const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	char log[1024]; // 存放日志的临时字符串
	if (-1 == size) {
		sprintf(log, "[读卡器 %d]发送数据错误, 数据: [%s], error: %d", readerId, buff, WSAGetLastError());
		SimpleLog::error(log);
	} else {
		sprintf(log, "[读卡器 %d]发送数据, 长度: %d, 数据: [%s]", readerId, size, buff);
		SimpleLog::info(log);
	}
	
	return size;
}

int Client::sendData(int data)
{
	return sendData(i2str(data));
}

int Client::sendData(SmartCom::string data)
{
	return sendData(data.c_str());
}
// 失败返回-1, 成功返回0
int Client::receiveData(char* data, int len)
{
	int size = recv(s, data, len, 0);
	char log[1024];
	if (-1 == size || 0 == size) // recv收到数据还返回-1, 可能是socket已经关闭了
	//if (strlen(data) <= 0) // 这个判断方式没什么用啊
	{
		sprintf(log, "[读卡器 %d]接收数据出错, size: %d, data: %s, error: %d", readerId, size, data, WSAGetLastError());
		SimpleLog::error(log);
		return -1;
	}
	data[size] = '\0';
	sprintf(log, "[读卡器 %d]接收数据: [%s]", readerId, data);
	SimpleLog::info(log);
	return 0;
}

int Client::receiveData(int& data)
{
	char str[512];
	int size = receiveData(str, 512);
	if (-1 == size)
	{
		data = -2;
	}
	else
	{
		data = atoi(str);
	}
	return size;
}

void Client::getName(char* name)
{
	sockaddr_in addr;
	int addrlen = sizeof(addr);
	getpeername(s, (sockaddr *)&addr, &addrlen);
	sprintf(name, "%s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
}

BOOL Client::isAvailable()
{
	return this->available;
}

BOOL Client::isQuit()
{
	return this->_quit;
}

void Client::quit()
{
	this->_quit = TRUE;
}
