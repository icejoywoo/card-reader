//////////////////////////////////////////////////////////////////////////
// FileName: ServerUtils.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 一些服务器的工具方法, 定义
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

#define MAX_OPERATION_DURATION (6000000) // 读卡器所有操作的最长时间

/**
 * @brief 关闭socket
 * @param 
 * SOCKET s
 * @return None
 */
void shutdownAndCloseSocket(SOCKET s);

/**
 * @brief 将int转换为CString
 * @param 
 * in a 需要转换的整型
 * @return 转换后的字符串
 */
CString i2str(int a);

/**
 * @brief 解析网络命令, 对读卡器进行相应的操作
 * @param 
 *	in client 客户端请求的socket
 *	in cardId 读卡器号, 用com号来表示, 因为串口通信方式一个com对应一个读卡器
 *	in command 命令
 *	out operationName 操作名称, 下面是operationName对照表
 *		*操作名称*			*对应操作*			*SmartCom函数*
 *		reset				复位操作			ResetDev
 *		shutdown			卡片下电			ShutDownCard
 *		clearMemory			擦除存储器			ClearMem
 *		modifyBraudRate		修改波特率			ModifyCardBraudRate
 *		downloadFile		下载文件			DownloadFile
 *		cardApdu			执行APDU命令		CardApdu
 *		executeMulApdu		执行APDU批处理		ExcuteMulAPDU
 *		getScript			读取脚本文件		GetScriptData
 *		checkBatchResult	批处理APDU结果		CheckBatchResult
 *		modifyCardPower		修改卡片电源		ModifyCardPower
 *		getDevIdAndReaderId	获取设备id和机号	GetDevIdAndMacNo
 *		setReaderIdByDevID	设置设备id和机号	SetMacNoByDevID
 *		getAppVerAndDevType	读取程序版本和终端类型		GetAppVerAndDevType
 *		getChipID			获取读卡接口芯片ID号		GetChipID
 *		isCardReady			检测A卡和B卡座是否有卡		IsCardReady
 *		resetCard			卡片复位应答		ResetCard
 * @return 
 *	成功为0
 *	部分错误码:
 *		-100, 命令找不到
 *		-101, 与卡片读写器的通信初始化失败
 *		-102, 关闭udp通信失败
 *		其他错误码, 具体参考SmartCom和operationName对照表中相应SmartCom函数中的错误码
 */
int parseCommand(Client* client, int readerId, char* command, string& operationName);

/**
 * @brief 通过socket发送数据
 * @param 
 *	in s 需要发送数据的socket
 *	in data 需要发送的数据
 * @return 发送的字符数
 */
int sendData(SOCKET s, int data);
int sendData(SOCKET s, const char* data);
int sendData(SOCKET s, SmartCom::string data);

/**
 * @brief 通过socket接收数据
 * @param 
 *	in s 需要接收数据的socket
 *	out data , 出口参数, 需要接收的数据
 *	len data的长度
 * @return 接收的字符数
 */
int receiveData(SOCKET s, char* data, int len);

/**
 * @brief 通过socket接收int数据
 * @param 
 *	in s 需要接收数据的socket
 *	out data , 出口参数, 需要接收的数据
 * @return 接收的字符数
 */
int receiveData(SOCKET s, int& data);

/**
 * @brief 使用,来切割字符串, 并获得一个vecotr列表
 * @param 
 *	in splitedStr 需要切割的字符串
 * @return 切割后的字符串
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

// true是断开, false是有效
BOOL HasConnectionDropped(int sdin);

#endif