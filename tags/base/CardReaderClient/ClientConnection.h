//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: 客户端用来连接到服务器的封装, 并发送数据, 默认开启日志记录
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENTCONNECTION_H_
#define _CLIENTCONNECTION_H_

#include "StdAfx.h"

class ClientConnection
{
public:
	ClientConnection(char* servername, int p, int id);
	~ClientConnection();
	/**
	 * @brief 发送数据
	 * @param data 要发送的数据
	 * @return 发送成功的数据长度
	 */
	int recvData(char* data);
	/**
	 * @brief 查看当前日志状态
	 * @return 如果记录日志, 返回true, 否则返回false
	 */
	bool isLogged();
	/**
	 * @brief 设置是否保存日志
	 * @return None
	 */
	void setLog(bool log);
private:
	/**
	 * @brief 获得对应servername的主机地址
	 * @param server 主机地址
	 * @return None
	 */
	void getServerAddr(struct sockaddr_in& server);
private:
	WSADATA wsaData;
	int readerId; // 请求的读卡器id
	char* serverName;
	int port;
	bool isLog;
	SOCKET client;
};

#endif