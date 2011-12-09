//////////////////////////////////////////////////////////////////////////
// FileName: ClientUrils.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// $Revision$
// Comment: �ͻ���һЩ����������ʵ��
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
	return ClientUtils::sendData(server, ClientUtils::i2str(data).c_str());
}

string ClientUtils::i2str(int a)
{
	char temp[5];
	itoa(a, temp, 5);
	string str(temp);
	return str;
}