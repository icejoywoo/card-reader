#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"

/**
 * @brief ��CEdit��ĩβ��Ӽ�¼
 * @param
 *	mEdit Ҫ������CEdit
 *	text ��Ҫ��ӵļ�¼
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text);

/**
 * @brief ��intת��ΪCString
 * @param 
 * in a ��Ҫת��������
 * @return ת������ַ���
 */
CString i2str(int a);

/**
 * @brief ��¼��־���߳�
 */
UINT logHandler(LPVOID pParam);

/**
 * @brief ����־ǰ��ʱ��
 * @param 
 *	in log ��Ҫ��ʽ������־
 * @return ������������ں����־
 */
CString formatLog(CString log);

/**
 * @brief ���ڴ�ŷ���������
 */
class ServerParam
{
private:
	ServerParam() {}
public:
// 	CString ip1 = "192.168.1.138";
// 	CString ip2 = "192.168.1.139";
// 	CString ip3 = "192.168.1.140";
// 	CString ip4 = "192.168.1.141"; /// ��������ip, ÿ32����������Ӧһ��ip
	CString ip1, ip2, ip3, ip4;
	int readerCount; /// ������������
	int serverPort; /// �������Ķ˿�
	HWND mainFrame; // ���洰��
	static ServerParam* instance;
};


/**
 * @brief ��ȡ��Ӧ��������id��ip��ַ�Ͷ˿ں�port
 * @param
 *	out ip ��������id��Ӧ��ip��ַ
 *	out port ��������id��Ӧ��port
 *	in id ��������
 *	param �������˴�����õĲ���
 * @return None
 */
void GetIpAndPort(CString& ip, int& port, int id, ServerParam* param);

/**
 * @brief ��ȡ��Ӧip�ؼ���ip�ַ���
 * @param
 *	in ip MFC��ip�ؼ�CIPAddressCtrl
 * @return ip����ַ���
 */
CString getIpAdress(CIPAddressCtrl& ip);

#endif