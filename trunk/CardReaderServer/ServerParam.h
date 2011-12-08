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
// 	CString ip1 = "192.168.1.138";
// 	CString ip2 = "192.168.1.139";
// 	CString ip3 = "192.168.1.140";
// 	CString ip4 = "192.168.1.141"; /// ��������ip, ÿ32����������Ӧһ��ip
	CString ip1, ip2, ip3, ip4;
	int readerCount; /// ������������
	int serverPort; /// �������Ķ˿�
	HWND mainFrame; // ���洰��
	CSplitStr split;
	static ServerParam* instance;
};

#endif