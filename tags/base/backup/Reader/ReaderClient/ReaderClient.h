
#if !defined(AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_)
#define AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
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
	int sendData(char* data);
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
	 * @return ������ַ(struct sockaddr_in&)
	 */
	void getServerAddr(struct sockaddr_in&);
private:
	WSADATA wsaData;
	int readerId; // ����Ķ�����id
	char* serverName;
	int port;
	bool isLog;
	SOCKET client;
};

#endif // !defined(AFX_READERCLIENT_H__514705E1_1019_4F5D_B159_D83BB5F3A9F1__INCLUDED_)
