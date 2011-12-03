//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: 服务器端的简单封装
//////////////////////////////////////////////////////////////////////////

#ifndef _SERVER_H_
#define _SERVER_H_

#include "StdAfx.h"

// the classic server pattern: bind -> listen -> accept -> handle the request
/// I wanna use the singleton.
class Server
{
public:
	virtual ~Server();
	/**
	 * @brief 获取单例
	 * @return instance
	 */
	static Server* getInstance() {
		return instance;
	}
	/**
	 * @brief 启动服务器
	 * @return 
	 *		socket创建失败, 返回-1
	 *		bind失败, 可能是端口被占用, 返回-2
	 *		listen失败, 返回-3
	 *		成功, 返回0
	 */
	int start();
	/**
	 * @brief 关闭服务器
	 * @return 
	 *		shutdown失败, 返回-1
	 *		closesocket失败, 返回-2
	 *		成功, 返回0
	 */
	int stop();
	/**
	 * @brief 重启服务器
	 * @return 
	 *		失败, 返回非0, 具体参照start和stop
	 *		成功, 返回0
	 */
	int restart();
	/**
	 * @brief 修改端口, 会自动重启服务器
	 * @return 
	 *		失败, 返回非0, 具体参照restart
	 *		成功, 返回0
	 */
	int setPort(int &port);

	SOCKET getServer()
	{
		return this->server;
	}

	int getPort()
	{
		return this->port;
	}

private:
	Server();
	static Server* instance; // the singleton
	WSADATA wsaData;
	int port;
	CEdit mEdit; // 在界面中输出日志信息
public:
	SOCKET server;
	CString log;
	/************************************************************************/
	/* 替换这两个handler可以改变服务器的行为                                */
	/************************************************************************/

	// 处理客户端请求
	UINT (*clientHandler) (LPVOID pParam );
	
	// 服务器handler 接收请求
	UINT (*serverHandler) (LPVOID pParam );
};
/************************************************************************/
/* 默认的handlers                                                       */
/************************************************************************/
// 默认的请求处理
UINT defaultClientHandler (LPVOID pParam );
// 默认的服务器
UINT defaultServerHandler (LPVOID pParam );

// 客户端需要的变量
typedef struct _clientParam 
{
	Server* server;
	SOCKET client;
} ClientParam;

#endif