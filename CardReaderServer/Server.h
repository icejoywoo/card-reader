//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: 服务器端的简单封装
//////////////////////////////////////////////////////////////////////////
#pragma warning( disable: 4786 )
#ifndef _SERVER_H_
#define _SERVER_H_

#include "StdAfx.h"
#include "Handlers.h"
#include <map>
#include <vector>

using namespace std;

// the classic server pattern: bind -> listen -> accept -> handle the request
/// I wanna use the singleton.
class Server
{
public:
	virtual ~Server();
	/**
	 * @brief 获取服务器单例
	 * @return 单例
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
	/**
	 * @brief 获取server的socket
	 * @return 
	 *		server的socket
	 */
	SOCKET getServer()
	{
		return this->server;
	}
	
	/**
	 * @brief 获取服务器端口
	 * @return
	 *	服务器端口
	 */
	int getPort()
	{
		return this->port;
	}
	
	//////////////////////////////////////////////////////////////////////////
	/// 等待队列的方法

	// 向队列添加socket
	void addToWaitList(int cardId, SOCKET s);
	// 获取队列的首个元素
	SOCKET getSocketByCardId(int cardId);

private:
	Server();
	static Server* instance; // the singleton
	WSADATA wsaData;
	int port;
	CEdit mEdit; // 在界面中输出日志信息
	
public:
	SOCKET server;
	CString log;
	// 全局临界区 读卡器的访问控制
	CRITICAL_SECTION g_cs;
	// 保存目前读卡器使用情况, 1表示在使用, 0表示未使用
	vector<int> readerUsage;
	// 读卡器数量
	int readerCount;
	// 等待队列
	map< int, vector<SOCKET> > waitList;

	/************************************************************************/
	/* 替换这两个handler可以改变服务器的行为                                */
	/************************************************************************/

	// 处理客户端请求
	UINT (*clientHandler) (LPVOID pParam );
	
	// 服务器handler 接收请求
	UINT (*serverHandler) (LPVOID pParam );

	// 服务器handler 接收请求
	UINT (*waitListHandler) (LPVOID pParam );
};

#endif