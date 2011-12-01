
#if !defined(AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_)
#define AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
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
	int sendData(char* data);
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
	 * @return 主机地址(struct sockaddr_in&)
	 */
	void getServerAddr(struct sockaddr_in&);
private:
	WSADATA wsaData;
	int readerId; // 请求的读卡器id
	char* serverName;
	int port;
	bool isLog;
	SOCKET client;
};

#endif // !defined(AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_)
