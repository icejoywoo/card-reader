//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam用来存放客户端配置参数, ClientParam的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ClientParam.h"
#include "ClientUtils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

ClientParam::ClientParam() 
{
	OutputDebugString("ClientParam初始化...");
	this->clientNum = 0; // 初始化客户端数量为0
	this->mutex = CreateMutex(NULL, FALSE, LPCTSTR("clients"));
	this->isInit = false;
	char logfile[512];
	time_t t;
	time(&t);
	tm * current_tm = localtime(&t);
	sprintf(logfile, "CardReaderClientDll-log-%04d-%02d-%02d-%d.txt", current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, t);
	this->log = fopen(logfile, "w");

	// 读取配置文件, 目前读取有问题
	this->serverIp = new char[512];
	ClientUtils::getConfig("Server", "ip", this->serverIp, 512);
	this->serverPort = ClientUtils::getConfigInt("Server", "port");
}
ClientParam::~ClientParam() 
{
	delete serverIp;
	fclose(this->log);
	// 在析构函数的时候, 调用释放socket环境
	if (ClientParam::instance->isClientEmpty())
	{
		WSACleanup();
	}
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