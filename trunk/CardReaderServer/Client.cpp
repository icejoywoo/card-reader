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
	// closesocket��һ�㲻�������رն�����TIME_WAIT�Ĺ��̣�����������ø�socket
// 	BOOL bReuseaddr=TRUE;
// 	::setsockopt(this->s,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL));
	// ��������״̬��soket�ڵ���closesocket��ǿ�ƹرգ�������TIME_WAIT�Ĺ���
	BOOL bDontLinger = FALSE;
	setsockopt(this->s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
	
// 	int nNetTimeout=10000;//10��
// 	//����ʱ��
// 	setsockopt(this->s,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));
// 	//����ʱ��
// 	setsockopt(this->s,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));

	//KeepAliveʵ��
	TCP_KEEPALIVE inKeepAlive = {0}; //�������
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE);
	TCP_KEEPALIVE outKeepAlive = {0}; //�������
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE);
	unsigned long ulBytesReturn = 0;
	
	//����socket��keep aliveΪ5�룬���ҷ��ʹ���Ϊ3��
	inKeepAlive.onoff = 1;
	inKeepAlive.keepaliveinterval = 5000; //����KeepAlive̽����ʱ����
	inKeepAlive.keepalivetime = 5000; //��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
	
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

// ��ʱ������һ�����������, ���ݲ�ͬ��������е���
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
//	closesocket(s);
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
		sprintf(log, "[������ %d]�������ݴ���, ����: [%s], error: %d", readerId, buff, WSAGetLastError());
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
// ʧ�ܷ���-1, �ɹ�����0
int Client::receiveData(char* data, int len)
{
	int size = recv(s, data, len, 0);
	char log[1024];
	if (-1 == size || 0 == size) // recv�յ����ݻ�����-1, ������socket�Ѿ��ر���
	//if (strlen(data) <= 0) // ����жϷ�ʽûʲô�ð�
	{
		sprintf(log, "[������ %d]�������ݳ���, size: %d, data: %s, error: %d", readerId, size, data, WSAGetLastError());
		SimpleLog::error(log);
		return -1;
	}
	data[size] = '\0';
	sprintf(log, "[������ %d]��������: [%s]", readerId, data);
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
