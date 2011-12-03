//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
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
	CEdit mEdit; // �ڽ����������־��Ϣ
public:
	SOCKET server;
	CString log;
	/************************************************************************/
	/* �滻������handler���Ըı����������Ϊ                                */
	/************************************************************************/

	// ����ͻ�������
	UINT (*clientHandler) (LPVOID pParam );
	
	// ������handler ��������
	UINT (*serverHandler) (LPVOID pParam );
};
/************************************************************************/
/* Ĭ�ϵ�handlers                                                       */
/************************************************************************/
// Ĭ�ϵ�������
UINT defaultClientHandler (LPVOID pParam );
// Ĭ�ϵķ�����
UINT defaultServerHandler (LPVOID pParam );

// �ͻ�����Ҫ�ı���
typedef struct _clientParam 
{
	Server* server;
	SOCKET client;
} ClientParam;

#endif