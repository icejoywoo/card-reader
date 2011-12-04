#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"
#include "SplitStr.h"
#include "SmartComString.h"

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
 * @brief ���ڴ�ŷ���������
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

/**
 * @brief ������������, �Զ�����������Ӧ�Ĳ���
 * @param 
 *	in command ����
 *	out operationName ��������, ������operationName���ձ�
 *		*��������*			*��Ӧ����*			*SmartCom����*
 *		reset				��λ����			ResetDev
 *		shutdown			��Ƭ�µ�			ShutDownCard
 *		clearMemory			�����洢��			ClearMem
 *		modifyBraudRate		�޸Ĳ�����			ModifyCardBraudRate
 *		downloadFile		�����ļ�			DownloadFile
 *		cardApdu			ִ��APDU����		CardApdu
 *		executeMulApdu		ִ��APDU������		ExcuteMulAPDU
 *		getScript			��ȡ�ű��ļ�		GetScriptData
 *		checkBatchResult	������APDU���		CheckBatchResult
 *		modifyCardPower		�޸Ŀ�Ƭ��Դ		ModifyCardPower
 *		getDevIdAndMacNo	��ȡ�豸id�ͻ���	GetDevIdAndMacNo
 *		setMacNoByDevID		�����豸id�ͻ���	SetMacNoByDevID
 *		getAppVerAndDevType	��ȡ����汾���ն�����		GetAppVerAndDevType
 *		getChipID			��ȡ�����ӿ�оƬID��		GetChipID
 *		isCardReady			���A����B�����Ƿ��п�		IsCardReady
 *		resetDev			��Ƭ��λӦ��		ResetDev
 * @return 
 *	�ɹ�Ϊ0
 *	���ִ�����:
 *		-100, �����Ҳ���
 *		-101, �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
 *		-102, �ر�udpͨ��ʧ��
 *	ʧ��Ϊ����, ����ο�SmartCom��operationName���ձ�
 */
int parseCommand(SOCKET client, char* command, CString& operationName);

/**
 * @brief ͨ��socket��������
 * @param 
 *	in s ��Ҫ�������ݵ�socket
 *	in data ��Ҫ���͵�����
 * @return ���͵��ַ���
 */
int sendData(SOCKET s, int data);
int sendData(SOCKET s, const char* data);
int sendData(SOCKET s, SmartCom::string data);

#endif