//////////////////////////////////////////////////////////////////////////
// FileName: ClientUrils.h
// Creator: icejoywoo
// Date: 2011.12.05
// $Revision$
// Comment: �ͻ���һЩ���������ӿڶ���
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_UTILS_H_
#define _CLIENT_UTILS_H_

#include "StdAfx.h"
#include <string>

using namespace std;

/**
 * @brief �ͻ��˵�һЩ��������
 */
class ClientUtils
{
private:
	ClientUtils();
	virtual ~ClientUtils();
public:
	/**
	 * @brief ����c-style�ַ�������
	 * @param
	 *	server ����ʹ�õ�socket
	 *	data Ҫ���͵�����
	 * @return
	 *	���ط��͵����ݳ���, ����ʧ�ܷ���-1
	 */
	static int sendData(SOCKET server, const char* data);
	
	/**
	 * @brief ��������
	 * @param
	 *	server ����ʹ�õ�socket
	 *	data Ҫ���͵�����
	 * @return
	 *	���ط��͵����ݳ���, ����ʧ�ܷ���-1
	 */
	static int sendData(SOCKET server, const string data);

	/**
	 * @brief ��������
	 * @param
	 *	server ����ʹ�õ�socket
	 *	data Ҫ���͵�����
	 * @return
	 *	���ط��͵����ݳ���, ����ʧ�ܷ���-1
	 */
	static int sendData(SOCKET server, int data);

	/**
	 * @brief ��int֤��ת��ΪSTL��string
	 * @param
	 *	a Ҫת��������
	 * @return
	 *	ת�����string
	 */
	static string i2str(int a);

	/**
	 * @brief ͨ��socket��������
	 * @param 
	 *	in s ��Ҫ�������ݵ�socket
	 *	out data ���ڲ���, ��Ҫ���յ�����
	 *	len data�ĳ���
	 * @return ���յ��ַ���
	 */
	static int receiveData(SOCKET s, char* data, int len);

	/**
	 * @brief ͨ��socket����int����
	 * @param 
	 *	in s		��Ҫ�������ݵ�socket
	 *	out data	���ڲ���, ��Ҫ���յ�����
	 * @return ���յ��ַ���
	 */
	static int receiveData(SOCKET s, int& data);

	/**
	 * @brief ��buf�е��ַ���, delimiterΪ����, ���зָ�
	 * @param 
	 *	in buf ��Ҫ�и���ַ���
	 *	out first �ָ�ĵ�һ������
	 *	out second �ָ���ĵڶ�������
	 * @return ���յ��ַ���
	 */
	static void splitString(char* buf, string& first, string& second);
	static void splitString(char* buf, string& first, int& second);
};

#endif