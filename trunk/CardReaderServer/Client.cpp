//////////////////////////////////////////////////////////////////////////
// FileName: Client.cpp
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: �������������Ŀͻ������ʵ��
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Client.h"
#include "ServerUtils.h"

Client::Client(SOCKET s)
{
	this->s = s;
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

// ��ʱ������һ�����������, ���ݲ�ͬ��������е���
Client& Client::setTimeout(ULONG timeout)
{
	this->timeoutStart = ::GetTickCount();
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
	//TRACE(CString("[������ ") + i2str(readerId) + "]����timeout\n");
	return *this;
}

BOOL Client::isOvertime()
{
	ULONG timePassed = ::GetTickCount() - this->timeoutStart;
	BOOL result = (timePassed >= this->timeout);
	//TRACE(CString("[������ ") + i2str(readerId) + "]�Ƿ�ʱ: " + i2str(result) + "\n");
	return result;
}

void Client::release()
{
	shutdownAndCloseSocket(s);
	this->available = FALSE;
	this->_quit = TRUE;
}

int Client::sendData(const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	char log[1024]; // �����־����ʱ�ַ���
	if (-1 == size) {
		sprintf(log, "[������ %d]�������ݴ���, ����: [%s]", readerId, buff);
		SimpleLog::error(log);
	} else {
		sprintf(log, "[������ %d]��������, ����: %d, ����: [%s]", readerId, size, buff);
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
	char log[1024];
	if (-1 == size || 0 == size)
	{
		sprintf(log, "[������ %d]�������ݳ���, size: %d", readerId, size);
		SimpleLog::error(log);
		return size;
	}
	data[size] = '\0';
	sprintf(log, "[������ %d]��������: [%s]", readerId, data);
	SimpleLog::info(log);
	return size;
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
