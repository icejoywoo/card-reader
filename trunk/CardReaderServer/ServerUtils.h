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
#include "Client.h"
#include <vector>

using namespace std;

#define MAX_OPERATION_DURATION (6000000) // ���������в������ʱ��

/**
 * @brief �ر�socket
 * @param 
 * SOCKET s
 * @return None
 */
void shutdownAndCloseSocket(SOCKET s);

/**
 * @brief ��intת��ΪCString
 * @param 
 * in a ��Ҫת��������
 * @return ת������ַ���
 */
CString i2str(int a);

/**
 * @brief ������������, �Զ�����������Ӧ�Ĳ���
 * @param 
 *	in client �ͻ��������socket
 *	in cardId ��������, ��com������ʾ, ��Ϊ����ͨ�ŷ�ʽһ��com��Ӧһ��������
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
 *		getDevIdAndReaderId	��ȡ�豸id�ͻ���	GetDevIdAndMacNo
 *		setReaderIdByDevID	�����豸id�ͻ���	SetMacNoByDevID
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
int parseCommand(Client* client, int readerId, char* command, string& operationName);

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
int receiveData(SOCKET s, int& data);

/**
 * @brief ʹ��,���и��ַ���, �����һ��vecotr�б�
 * @param 
 *	in splitedStr ��Ҫ�и���ַ���
 * @return �и����ַ���
 */
vector<string> splitString(const char* splitedStr);

void writeConfig(LPCTSTR lpAppName,  // section name
				 LPCTSTR lpKeyName,  // key name
				 LPCTSTR lpString   // string to add
				 );

void getConfig(LPCTSTR lpAppName,        // section name
			   LPCTSTR lpKeyName,        // key name
			   LPTSTR lpReturnedString,  // destination buffer
			   DWORD nSize              // size of destination buffer
			   );

UINT getConfigInt(LPCTSTR lpAppName,  // section name
				  LPCTSTR lpKeyName  // key name
				  );

// true�ǶϿ�, false����Ч
BOOL HasConnectionDropped(int sdin);

#endif