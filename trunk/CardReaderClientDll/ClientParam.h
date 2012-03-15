//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam用来存放客户端配置参数, ClientParam的定义
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_PARAM_H_
#define _CLIENT_PARAM_H_

#include "StdAfx.h"
#include <stdio.h>

class ClientParam
{
private:
	ClientParam();
public:
	virtual ~ClientParam();

public:
	// 添加一个客户端
	void addClient();
	// 删除一个客户端
	void deleteClient();
	// 看当前是否有客户端
	BOOL isClientEmpty();

public:
	// 服务器ip地址
	char* serverIp;
	// 服务器端口号
	int serverPort;
	// 互斥量, 保证客户端数量原子性地修改
	HANDLE mutex;
	// 客户端数量
	unsigned int clientNum;
	// 是否初始化socket环境
	volatile bool isInit;
	// 单例
	static ClientParam* instance;
	// 日志文件
	FILE* log;
};

#endif