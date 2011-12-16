//////////////////////////////////////////////////////////////////////////
// FileName: Client.cpp
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: �������������Ŀͻ������ʵ��
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
	return *this;
}

BOOL Client::isOvertime()
{
	ULONG timePassed = ::GetTickCount() - this->timeoutStart;
	return (timePassed >= this->timeout);
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
	
	if (-1 == size) {
		SimpleLog::error(CString("�������ݴ���, ����: [") + buff + "]");
	} else {
		SimpleLog::info(CString("��������, ����: ") + i2str(size) + ", ����: [" + buff + "]");
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
	if (-1 == size)
	{
		SimpleLog::error("�������ݳ���");
		return size;
	}
	data[size] = '\0';
	SimpleLog::info(CString("��������: [") + data + "]");
	return size;
}

int Client::receiveData(int& data)
{
	char str[512];
	int size = receiveData(str, 512);
	data = atoi(str);
	return size;
}