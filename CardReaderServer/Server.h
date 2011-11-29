//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
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
	int setPort(int port);
private:
	Server();
	int port;
	static Server* instance; // the singleton
	WSADATA wsaData;
	SOCKET server;

	UINT (*clientHandler) (LPVOID pParam );
	UINT defaultClientHandler (LPVOID pParam );

	UINT (*serverHandler) (LPVOID pParam );
	UINT defaultServerHandler (LPVOID pParam );
};

#endif