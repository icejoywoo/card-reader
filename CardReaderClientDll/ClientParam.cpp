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

using namespace std;

ClientParam::ClientParam() 
{
	OutputDebugString("ClientParam初始化...");
	this->clientNum = 0; // 初始化客户端数量为0
	this->mutex = CreateMutex(NULL, FALSE, LPCTSTR("clients"));

	// 读取配置文件, 目前读取有问题
	ifstream fin("client.config");
	string config;
	if (!(fin >> config))
	{
		cout << "读取配置文件出错" << endl;
	}

	string first;
	string second;

	ClientUtils::splitString(config.c_str(), first, second);
	this->serverIp = new char[20];
	strcpy(this->serverIp, first.c_str());
	this->serverPort = atoi(second.c_str());
	
	cout << this->serverIp << ", " << this->serverPort << endl;

	fin.close();
// 	this->serverIp = "127.0.0.1";
// 	this->serverPort = 60000;
}
ClientParam::~ClientParam() 
{
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