//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision: 12 $
// $LastChangedDate: 2011-11-30 09:45:44 +0800 (周三, 30 十一月 2011) $
// Comment: �ͻ����������ӵ��������ķ�װ, ����������, Ĭ�Ͽ�����־��¼
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENTCONNECTION_H_
#define _CLIENTCONNECTION_H_

#include "StdAfx.h"

class ClientConnection
{
public:
	ClientConnection(char* servername, int p, int id);
	~ClientConnection();
	/**
	 * @brief ��������
	 * @param data Ҫ���͵�����
	 * @return ���ͳɹ������ݳ���
	 */
	int recvData(char* data);
	/**
	 * @brief �鿴��ǰ��־״̬
	 * @return �����¼��־, ����true, ���򷵻�false
	 */
	bool isLogged();
	/**
	 * @brief �����Ƿ񱣴���־
	 * @return None
	 */
	void setLog(bool log);
private:
	/**
	 * @brief ��ö�Ӧservername��������ַ
	 * @param server ������ַ
	 * @return None
	 */
	void getServerAddr(struct sockaddr_in& server);
private:
	WSADATA wsaData;
	int readerId; // ����Ķ�����id
	char* serverName;
	int port;
	bool isLog;
	SOCKET client;
};

#endif