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
	virtual ~ServerParam() {delete instance;}
public:
	set<int> readerIdSet; // ������id����, �����������id
	int serverPort; /// �������Ķ˿�
	CSplitStr split;
	HWND mainFrame;
	static ServerParam* instance;
};

#endif