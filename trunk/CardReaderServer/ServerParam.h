//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ������ServerParam��������������ò���, ��Ķ���
//////////////////////////////////////////////////////////////////////////
#ifndef _SERVER_PARAM_H_
#define _SERVER_PARAM_H_

#include "StdAfx.h"
#include "ServerParam.h"
#include <set>

using namespace std;

/**
 * @brief ���ڴ�ŷ��������ò���, ���õ���ģʽ
 * 
 * ����˶�������ip��ַ, ������������, �������Ķ˿ں�
 */
class ServerParam
{
private:
	ServerParam();
public:
	virtual ~ServerParam() {}
	void saveConfig();
	set<int> readerIdSet; // ������id����, �����������id
	int serverPort; /// �������Ķ˿�
	HWND mainFrame;
	static ServerParam* instance;
};

#endif