//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam������ſͻ������ò���, ClientParam�Ķ���
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENT_PARAM_H_
#define _CLIENT_PARAM_H_

#include "StdAfx.h"

class ClientParam
{
private:
	ClientParam();
	virtual ~ClientParam();
public:
	// ������ip��ַ
	char* serverIp;
	// �������˿ں�
	int serverPort;
	// ����
	static ClientParam* instance;
};

#endif