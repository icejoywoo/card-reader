//////////////////////////////////////////////////////////////////////////
// FileName: ClientUrils.h
// Creator: icejoywoo
// Date: 2011.12.05
// $Revision$
// Comment: 客户端一些辅助操作接口定义
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_UTILS_H_
#define _CLIENT_UTILS_H_

#include "StdAfx.h"
#include <string>

using namespace std;

/**
 * @brief 客户端的一些辅助操作
 */
class ClientUtils
{
private:
	ClientUtils();
	virtual ~ClientUtils();
public:
	/**
	 * @brief 发送c-style字符串数据
	 * @param
	 *	server 连接使用的socket
	 *	data 要发送的数据
	 * @return
	 *	返回发送的数据长度, 发送失败返回-1
	 */
	static int sendData(SOCKET server, const char* data);
	
	/**
	 * @brief 发送数据
	 * @param
	 *	server 连接使用的socket
	 *	data 要发送的数据
	 * @return
	 *	返回发送的数据长度, 发送失败返回-1
	 */
	static int sendData(SOCKET server, const string data);

	/**
	 * @brief 发送数据
	 * @param
	 *	server 连接使用的socket
	 *	data 要发送的数据
	 * @return
	 *	返回发送的数据长度, 发送失败返回-1
	 */
	static int sendData(SOCKET server, int data);

	/**
	 * @brief 将int证书转换为STL的string
	 * @param
	 *	a 要转换的整数
	 * @return
	 *	转换后的string
	 */
	static string i2str(int a);

	/**
	 * @brief 通过socket接收数据
	 * @param 
	 *	in s 需要接收数据的socket
	 *	out data , 出口参数, 需要接收的数据
	 *	len data的长度
	 * @return 接收的字符数
	 */
	static int receiveData(SOCKET s, char* data, int len);

	/**
	 * @brief 通过socket接收int数据
	 * @param 
	 *	in s 需要接收数据的socket
	 *	out data , 出口参数, 需要接收的数据
	 * @return 接收的字符数
	 */
	static int receiveData(SOCKET s, int& data);
};

#endif