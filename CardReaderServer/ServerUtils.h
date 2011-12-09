//////////////////////////////////////////////////////////////////////////
// FileName: ServerUtils.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: һЩ�������Ĺ��߷���, ����
//////////////////////////////////////////////////////////////////////////
#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"
#include "SplitStr.h"
#include "SmartComString.h"
#include "ServerParam.h"

/**
 * @brief ��intת��ΪCString
 * @param 
 * in a ��Ҫת��������
 * @return ת������ַ���
 */
CString i2str(int a);


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
 *	in client �ͻ��������socket
 *	in cardId ��������
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
 *		resetCard			��Ƭ��λӦ��		ResetCard
 * @return 
 *	�ɹ�Ϊ0
 *	���ִ�����:
 *		-100, �����Ҳ���
 *		-101, �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
 *		-102, �ر�udpͨ��ʧ��
 *		����������, ����ο�SmartCom��operationName���ձ�����ӦSmartCom�����еĴ�����
 */
int parseCommand(SOCKET client, int cardId, char* command, CString& operationName);

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

/**
 * @brief ͨ��socket��������
 * @param 
 *	in s ��Ҫ�������ݵ�socket
 *	out data , ���ڲ���, ��Ҫ���յ�����
 *	len data�ĳ���
 * @return ���յ��ַ���
 */
int receiveData(SOCKET s, char* data, int len);

/**
 * @brief ͨ��socket����int����
 * @param 
 *	in s ��Ҫ�������ݵ�socket
 *	out data , ���ڲ���, ��Ҫ���յ�����
 * @return ���յ��ַ���
 */
int receiveData(SOCKET s, int data);

#endif