//////////////////////////////////////////////////////////////////////////
// FileName: Client.h
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: 向服务器端请求的客户端类的定义
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "StdAfx.h"
#include <WINSOCK2.H> // win socket
#include "SmartComString.h"

#define DEFAULT_TIMEOUT_ADDITION (200000)

/**
 * @brief 向服务器请求的客户端, 保存了客户端的状态　
 */
class Client
{
public:
	Client(SOCKET s);
	virtual ~Client();
	/// 说明: return this是一种链式编程风格
	/**
	 * @brief 设置读卡器id
	 * @param None
	 * @return this
	 */
	Client& setReaderId(int readerId);

	/**
	 * @brief 设置延时
	 * @param None
	 * @return this
	 */
	Client& setTimeout(ULONG timeout);

	/**
	 * @brief 设置socket
	 * @param None
	 * @return this
	 */
	Client& setSocket(SOCKET s);

	/**
	 * @brief 获得读卡器id
	 * @param None
	 * @return 读卡器id
	 */
	int getReaderId();

	/**
	 * @brief 获得延时
	 * @param None
	 * @return 延时
	 */
	ULONG getTimeout();

	/**
	 * @brief 获得socket
	 * @param None
	 * @return socket
	 */
	SOCKET getSocket();

	/**
	 * @brief 更新timeoutStart
	 * @param None
	 * @return this
	 */
	Client& updateTimeout();

	/**
	 * @brief 判断是否已经超时
	 * @param None
	 * @return true表示超时, false表示未超时
	 */
	BOOL isOvertime();

	/**
	 * @brief 释放自己的socket
	 * @param None
	 * @return None
	 */
	void release();

	/**
	 * @brief 通过socket发送数据
	 * @param 
	 *	in data 需要发送的数据
	 * @return 发送的字符数
	 */
	int sendData(int data);
	int sendData(const char* data);
	int sendData(SmartCom::string data);

	/**
	 * @brief 接收数据
	 * @param 
	 *	out data , 出口参数, 需要接收的数据
	 *	len data的长度
	 * @return 接收的字符数
	 */
	int receiveData(char* data, int len);

	/**
	 * @brief 接收int数据
	 * @param 
	 *	out data , 出口参数, 需要接收的数据
	 * @return 接收的字符数
	 */
	int receiveData( int& data);

	bool operator ==(const Client& r) const
	{
		return s == r.s 
			&& readerId == r.readerId
			&& timeout == r.timeout;
	}

	bool operator <(const Client& r) const
	{
		return readerId < r.readerId;
	}
	
	/**
	 * 获取名字
	 */
	void getName(char* name);
	BOOL isAvailable();
	BOOL isQuit();
	void quit();
private:
	SOCKET s; // 与服务器的socket连接
	ULONG timeout; // 延时ms
	int readerId; // 请求的读卡器id
	ULONG timeoutStart; // 延时开始计时时间, 使用GetTickCount计时, 单位ms
	BOOL available; // 是否可用
	BOOL _quit; // 是否已经退出
};

#endif