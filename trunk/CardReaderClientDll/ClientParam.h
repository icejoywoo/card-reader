//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam������ſͻ������ò���, ClientParam�Ķ���
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_PARAM_H_
#define _CLIENT_PARAM_H_

#include "StdAfx.h"
#include <stdio.h>

class ClientParam
{
private:
	ClientParam();
public:
	virtual ~ClientParam();

public:
	// ���һ���ͻ���
	void addClient();
	// ɾ��һ���ͻ���
	void deleteClient();
	// ����ǰ�Ƿ��пͻ���
	BOOL isClientEmpty();

public:
	// ������ip��ַ
	char* serverIp;
	// �������˿ں�
	int serverPort;
	// ������, ��֤�ͻ�������ԭ���Ե��޸�
	HANDLE mutex;
	// �ͻ�������
	unsigned int clientNum;
	// �Ƿ��ʼ��socket����
	volatile bool isInit;
	// ����
	static ClientParam* instance;
	// ��־�ļ�
	FILE* log;
};

#endif