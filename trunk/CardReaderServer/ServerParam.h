//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器ServerParam类是用来存放配置参数, 类的定义
//////////////////////////////////////////////////////////////////////////
#ifndef _SERVER_PARAM_H_
#define _SERVER_PARAM_H_

#include "StdAfx.h"
#include "ServerParam.h"
#include <set>

using namespace std;

/**
 * @brief 用于存放服务器配置参数, 采用单例模式
 * 
 * 存放了读卡器的ip地址, 读卡器的数量, 服务器的端口号
 */
class ServerParam
{
private:
	ServerParam();
public:
	virtual ~ServerParam() {}
	void saveConfig();
	set<int> readerIdSet; // 读卡器id集合, 保存读卡器的id
	int serverPort; /// 服务器的端口
	HWND mainFrame;
	static ServerParam* instance;
};

#endif