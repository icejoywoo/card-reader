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

/**
 * @brief 用于存放服务器配置参数, 采用单例模式
 * 
 * 存放了读卡器的ip地址, 读卡器的数量, 服务器的端口号
 */
class ServerParam
{
private:
	ServerParam();
	virtual ~ServerParam() {delete instance;}
public:
// 	CString ip1 = "192.168.1.138";
// 	CString ip2 = "192.168.1.139";
// 	CString ip3 = "192.168.1.140";
// 	CString ip4 = "192.168.1.141"; /// 读卡器的ip, 每32个读卡器对应一个ip
	CString ip1, ip2, ip3, ip4;
	int readerCount; /// 读卡器的数量
	int serverPort; /// 服务器的端口
	HWND mainFrame; // 保存窗口
	CSplitStr split;
	static ServerParam* instance;
};

#endif