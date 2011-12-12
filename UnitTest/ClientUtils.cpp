//////////////////////////////////////////////////////////////////////////
// FileName: ClientUrils.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// $Revision$
// Comment: 客户端一些辅助操作的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ClientUtils.h"
#include <string>

using namespace std;

ClientUtils::ClientUtils() {}
ClientUtils::~ClientUtils() {}

int ClientUtils::sendData(SOCKET server, const char* data)
{
	char buff[512];
	memset(buff, 0, 512);
	sprintf(buff, data);
	int size = send(server, buff, strlen(buff), 0);
	return size;
}

int ClientUtils::sendData(SOCKET server, const string data)
{
	return ClientUtils::sendData(server, data.c_str());;
}

int ClientUtils::sendData(SOCKET server, int data)
{
	return ClientUtils::sendData(server, ClientUtils::i2str(data));
}

string ClientUtils::i2str(int a)
{
	char* str = new char[10];
	sprintf(str, "%d", a);
	string str2(str);
	delete str;
	return str2;
}

int ClientUtils::receiveData(SOCKET s, char* data, int len)
{
	int size = recv(s, data, len, 0);
	if (-1 == size)
	{
		return size;
	}
	data[size] = '\0';
	return size;
}

int ClientUtils::receiveData(SOCKET s, int &data)
{
	char str[512];
	int size = receiveData(s, str, 512);
	data = atoi(str);
	return size;
}