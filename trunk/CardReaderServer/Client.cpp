//////////////////////////////////////////////////////////////////////////
// FileName: Client.cpp
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: 向服务器端请求的客户端类的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Client.h"
#include "ServerUtils.h"

Client::Client()
{
	this->timeoutStart = ::GetTickCount();
}

Client::Client(SOCKET s)
{
	this->s = s;
	this->timeoutStart = ::GetTickCount();
}

Client::~Client()
{
	closesocket(s);
}

Client& Client::setReaderId(int readerId)
{
	this->readerId = readerId;
	return *this;
}

Client& Client::setTimeout(ULONG timeout)
{
	this->timeout = timeout;
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
	TRACE(CString("[读卡器 ") + i2str(readerId) + "]更新timeout\n");
	return *this;
}

BOOL Client::isOvertime()
{
	ULONG timePassed = ::GetTickCount() - this->timeoutStart;
	BOOL result = (timePassed >= this->timeout);
	TRACE(CString("[读卡器 ") + i2str(readerId) + "]是否超时: " + i2str(result) + "\n");
	return result;
}

void Client::release()
{
	shutdown(s, SD_BOTH);
	closesocket(s);
}

int Client::sendData(const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	char log[512];
	if (-1 == size) {
		sprintf(log, "[读卡器 %d]发送数据错误, 数据: [%s]", readerId, buff);
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

int Client::receiveData(char* data, int len)
{
	int size = recv(s, data, len, 0);
	char log[512];
	if (-1 == size || 0 == size)
	{
		sprintf(log, "[读卡器 %d]接收数据出错", readerId);
		SimpleLog::error(log);
		return size;
	}
	data[size] = '\0';
	sprintf(log, "[读卡器 %d]接收数据: [%s]", readerId, data);
	SimpleLog::info(log);
	return size;
}

int Client::receiveData(int& data)
{
	char str[512];
	int size = receiveData(str, 512);
	data = atoi(str);
	return size;
}
