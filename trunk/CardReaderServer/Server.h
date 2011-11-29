//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
// Comment: �������˵ļ򵥷�װ
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
	 * @brief ��ȡ����
	 * @return instance
	 */
	static Server* getInstance() {
		return instance;
	}
	/**
	 * @brief ����������
	 * @return 
	 *		socket����ʧ��, ����-1
	 *		bindʧ��, �����Ƕ˿ڱ�ռ��, ����-2
	 *		listenʧ��, ����-3
	 *		�ɹ�, ����0
	 */
	int start();
	/**
	 * @brief �رշ�����
	 * @return 
	 *		shutdownʧ��, ����-1
	 *		closesocketʧ��, ����-2
	 *		�ɹ�, ����0
	 */
	int stop();
	/**
	 * @brief ����������
	 * @return 
	 *		ʧ��, ���ط�0, �������start��stop
	 *		�ɹ�, ����0
	 */
	int restart();
	/**
	 * @brief �޸Ķ˿�, ���Զ�����������
	 * @return 
	 *		ʧ��, ���ط�0, �������restart
	 *		�ɹ�, ����0
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