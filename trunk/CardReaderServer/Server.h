//////////////////////////////////////////////////////////////////////////
// FileName: Server.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: �������˵ļ򵥷�װ
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
	 * @brief ��ȡ����������
	 * @return ����
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
	/**
	 * @brief ��ȡserver��socket
	 * @return 
	 *		server��socket
	 */
	SOCKET getServer()
	{
		return this->server;
	}
	
	/**
	 * @brief ��ȡ�������˿�
	 * @return
	 *	�������˿�
	 */
	int getPort()
	{
		return this->port;
	}
	
	//////////////////////////////////////////////////////////////////////////
	/// �ȴ����еķ���

	// ��������socket
	void addToWaitList(int cardId, SOCKET s);
	// ��ȡ���е��׸�Ԫ��
	SOCKET getSocketByCardId(int cardId);

private:
	Server();
	static Server* instance; // the singleton
	WSADATA wsaData;
	int port;
	CEdit mEdit; // �ڽ����������־��Ϣ
	
public:
	SOCKET server;
	CString log;
	// ȫ���ٽ��� �������ķ��ʿ���
	CRITICAL_SECTION g_cs;
	// ����Ŀǰ������ʹ�����, 1��ʾ��ʹ��, 0��ʾδʹ��
	vector<int> readerUsage;
	// ����������
	int readerCount;
	// �ȴ�����
	map< int, vector<SOCKET> > waitList;

	/************************************************************************/
	/* �滻������handler���Ըı����������Ϊ                                */
	/************************************************************************/

	// ����ͻ�������
	UINT (*clientHandler) (LPVOID pParam );
	
	// ������handler ��������
	UINT (*serverHandler) (LPVOID pParam );

	// ������handler ��������
	UINT (*waitListHandler) (LPVOID pParam );
};

#endif