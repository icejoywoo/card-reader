//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam������ſͻ������ò���, ClientParam��ʵ��
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ClientParam.h"
#include "ClientUtils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

ClientParam::ClientParam() 
{
	OutputDebugString("ClientParam��ʼ��...");
	this->clientNum = 0; // ��ʼ���ͻ�������Ϊ0
	this->mutex = CreateMutex(NULL, FALSE, LPCTSTR("clients"));

	// ��ȡ�����ļ�, Ŀǰ��ȡ������
	this->serverIp = new char[512];
	ClientUtils::getConfig("Server", "ip", this->serverIp, 512);
	this->serverPort = ClientUtils::getConfigInt("Server", "port");
}
ClientParam::~ClientParam() 
{
	delete serverIp;
	delete instance;
}

ClientParam* ClientParam::instance = new ClientParam();

void ClientParam::addClient()
{
	WaitForSingleObject(mutex, INFINITE);
	++clientNum;
	ReleaseMutex(mutex);
}

void ClientParam::deleteClient()
{
	WaitForSingleObject(mutex, INFINITE);
	if (!isClientEmpty())
		--clientNum;
	ReleaseMutex(mutex);
}

BOOL ClientParam::isClientEmpty()
{
	return (0 == clientNum);
}