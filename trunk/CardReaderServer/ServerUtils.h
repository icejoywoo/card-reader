#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"
#include "SplitStr.h"

/**
 * @brief 向CEdit中末尾添加记录
 * @param
 *	mEdit 要操作的CEdit
 *	text 需要添加的记录
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text);

/**
 * @brief 将int转换为CString
 * @param 
 * in a 需要转换的整型
 * @return 转换后的字符串
 */
CString i2str(int a);

/**
 * @brief 记录日志的线程
 */
UINT logHandler(LPVOID pParam);

/**
 * @brief 在日志前加时间
 * @param 
 *	in log 需要格式化的日志
 * @return 返回添加了日期后的日志
 */
CString formatLog(CString log);

/**
 * @brief 用于存放服务器参数
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
// 	CString ip4 = "192.168.1.141"; /// 读卡器的ip, 每32个读卡器对应一个ip
	CString ip1, ip2, ip3, ip4;
	int readerCount; /// 读卡器的数量
	int serverPort; /// 服务器的端口
	HWND mainFrame; // 保存窗口
	CSplitStr split;
	static ServerParam* instance;
};


/**
 * @brief 获取对应读卡器号id的ip地址和端口号port
 * @param
 *	out ip 读卡器号id对应的ip地址
 *	out port 读卡器号id对应的port
 *	in id 读卡器号
 *	param 服务器端存放设置的参数
 * @return None
 */
void GetIpAndPort(CString& ip, int& port, int id, ServerParam* param);

/**
 * @brief 获取对应ip控件的ip字符串
 * @param
 *	in ip MFC的ip控件CIPAddressCtrl
 * @return ip点分字符串
 */
CString getIpAdress(CIPAddressCtrl& ip);

/**
 * @brief 解析网络命令, 对读卡器进行相应的操作
 * @param 
 *	in command 命令
 *	out operationName 操作名称, 下面是对照表
 *		操作名称			对应操作			SmartCom函数
 *		reset				复位操作			ResetDev
 *		shutdown			卡片下电			ShutDownCard
 *		clearMemory			擦除存储器			ClearMem
 *		modifyBraudRate		修改波特率			ModifyCardBraudRate
 
 *		shutdown			卡片下电			ShutDownCard
 *		shutdown			卡片下电			ShutDownCard
 *		shutdown			卡片下电			ShutDownCard
 *		shutdown			卡片下电			ShutDownCard
 * @return 成功为0, 失败为其他, 具体参考SmartCom和operationName
 */
int parseCommand(SOCKET client, char* command, CString& operationName);

#endif