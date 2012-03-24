//////////////////////////////////////////////////////////////////////////
// FileName: Client.h
// Creator: icejoywoo
// Date: 2011.12.16
// Comment: �������������Ŀͻ�����Ķ���
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "StdAfx.h"
#include <WINSOCK2.H> // win socket
#include "SmartComString.h"

#define DEFAULT_TIMEOUT_ADDITION (200000)

/**
 * @brief �����������Ŀͻ���, �����˿ͻ��˵�״̬��
 */
class Client
{
public:
	Client(SOCKET s);
	virtual ~Client();
	/// ˵��: return this��һ����ʽ��̷��
	/**
	 * @brief ���ö�����id
	 * @param None
	 * @return this
	 */
	Client& setReaderId(int readerId);

	/**
	 * @brief ������ʱ
	 * @param None
	 * @return this
	 */
	Client& setTimeout(ULONG timeout);

	/**
	 * @brief ����socket
	 * @param None
	 * @return this
	 */
	Client& setSocket(SOCKET s);

	/**
	 * @brief ��ö�����id
	 * @param None
	 * @return ������id
	 */
	int getReaderId();

	/**
	 * @brief �����ʱ
	 * @param None
	 * @return ��ʱ
	 */
	ULONG getTimeout();

	/**
	 * @brief ���socket
	 * @param None
	 * @return socket
	 */
	SOCKET getSocket();

	/**
	 * @brief ����timeoutStart
	 * @param None
	 * @return this
	 */
	Client& updateTimeout();

	/**
	 * @brief �ж��Ƿ��Ѿ���ʱ
	 * @param None
	 * @return true��ʾ��ʱ, false��ʾδ��ʱ
	 */
	BOOL isOvertime();

	/**
	 * @brief �ͷ��Լ���socket
	 * @param None
	 * @return None
	 */
	void release();

	/**
	 * @brief ͨ��socket��������
	 * @param 
	 *	in data ��Ҫ���͵�����
	 * @return ���͵��ַ���
	 */
	int sendData(int data);
	int sendData(const char* data);
	int sendData(SmartCom::string data);

	/**
	 * @brief ��������
	 * @param 
	 *	out data , ���ڲ���, ��Ҫ���յ�����
	 *	len data�ĳ���
	 * @return ���յ��ַ���
	 */
	int receiveData(char* data, int len);

	/**
	 * @brief ����int����
	 * @param 
	 *	out data , ���ڲ���, ��Ҫ���յ�����
	 * @return ���յ��ַ���
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
	 * ��ȡ����
	 */
	void getName(char* name);
	BOOL isAvailable();
	BOOL isQuit();
	void quit();
private:
	SOCKET s; // ���������socket����
	ULONG timeout; // ��ʱms
	int readerId; // ����Ķ�����id
	ULONG timeoutStart; // ��ʱ��ʼ��ʱʱ��, ʹ��GetTickCount��ʱ, ��λms
	BOOL available; // �Ƿ����
	BOOL _quit; // �Ƿ��Ѿ��˳�
};

#endif