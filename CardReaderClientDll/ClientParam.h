//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam用来存放客户端配置参数, ClientParam的定义
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_PARAM_H_
#define _CLIENT_PARAM_H_

#include "StdAfx.h"

class ClientParam
{
private:
	ClientParam();
	virtual ~ClientParam();
public:
	// 服务器ip地址
	char* serverIp;
	// 服务器端口号
	int serverPort;
	// 单例
	static ClientParam* instance;
};

#endif