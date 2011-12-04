#include "ServerUtils.h"

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	// 设置默认的split参数
	split.SetSplitFlag(",");
	split.SetSequenceAsOne(TRUE);
}

CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

UINT logHandler (LPVOID pParam)
{
	while (TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			CEdit* logWindow = (CEdit*) pParam;
			int len = logWindow->GetWindowTextLength();
			logWindow->SetSel(len,len);
			logWindow->ReplaceSel(Server::getInstance()->log);
			Server::getInstance()->log = ""; // 清空日志
		}
		Sleep(500);
	}
	
	return 0;
}

void GetIpAndPort(CString& ip, int& port, int id, ServerParam* param)
{
	// 每个ip对应32个读卡器, 每个读卡器对应一个port, port默认从10000开始
	const int defaultPort = 10000;
	if(id<=32&&id>=1)
	{
        ip=param->ip1;
		port=defaultPort+id;
	}
	else if(id>32&&id<=64)
	{
		ip=param->ip2;
		port=defaultPort+id-32;
	}
	else if(id>64&&id<96)
	{
		ip=param->ip3;
		port=defaultPort+id-64;
	}
	else if(id>96&&id<128)
	{
		ip=param->ip4;
		port=defaultPort+id-96;
	}
}

CString getIpAdress(CIPAddressCtrl& ip)
{
	BYTE b[4];
	ip.GetAddress(b[0], b[1], b[2], b[3]);
	CString result;
	result.Format("%d.%d.%d.%d", b[0], b[1], b[2], b[3]);
	return result;
}

int parseCommand(SOCKET client, char* command, CString& operationName)
{
	ServerParam::instance->split.SetData(CString(command));
	CStringArray requestParam; // operationName, cardId, params
	ServerParam::instance->split.GetSplitStrArray(requestParam);
	operationName = requestParam[0]; // 操作名称
	int cardId = atoi(requestParam[1]); // 读卡器号
	
	CString ip; // 读卡器对应的ip
	int port; // 读卡器对应的端口号
	Communicator communicator; // 与读卡器通信的通信
	
	GetIpAndPort(ip, port, cardId, ServerParam::instance); 
	GetOneUDPCommunicator(communicator, ip, port); // 获得通信器
	//GetOneCOMCommunicator(communicator, comPort); // 获取

	if (InitUDPComm() == -1) {
		AfxMessageBox("与卡片读写器的通信初始化失败");
		SimpleLog::error("与卡片读写器的通信初始化失败");
		return -101; // 与卡片读写器的通信初始化失败
	}

	// refer to SmartCom.h
	if (operationName == CString("reset")) { // 复位操作
		return ResetDev(communicator, cardId);
	} else if (operationName == CString("shutdown")) { // 卡片下电
		return ShutdownCard(communicator, cardId);
	} else if (operationName == CString("clearMemory")) { // 对SST25VF016B存储器进行整片擦除
		return ClearMem(communicator, cardId);
	} else if (operationName == CString("modifyBraudRate")) { // 修改比特率
		int braudRate = atoi(requestParam[2]);
		return ModifyCardBraudRate(communicator, braudRate, cardId);
	} else if (operationName == CString("getBraudRate")) { // 获得比特率
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate, cardId);
		sendData(client, braudRate);
		return resultCode;
	} else if (operationName == CString("downloadFile")) { // 下载文件
		int flag = atoi(requestParam[2]); // 1 下载命令体文件, 2 下载命令头文件
		char* fileName = (LPSTR)(LPCTSTR)requestParam[3]; // 文件名
		return DownloadFile(communicator, flag, fileName, cardId);
	} else if (operationName == CString("cardApdu")) { // 卡片操作-执行APDU命令
		char* apdu = (LPSTR)(LPCTSTR)requestParam[2]; // apdu命令
		int card = atoi(requestParam[3]); // 1 为A卡, 2 为B卡
		SmartCom::string retCode; // 输出参数, 执行apdu指令的返回值
		int resultCode = CardApdu(communicator, apdu, retCode, card, cardId);
		sendData(client, retCode);
		return resultCode;
	} else if (operationName == CString("executeMulApdu")) { // 卡片操作-执行批处理APDU命令
		int cmdNum = atoi(requestParam[2]);
		int card = atoi(requestParam[3]); // 1 为A卡, 2 为B卡
		return ExcuteMulAPDU(communicator, cmdNum, card);
	} else if (operationName == CString("getScript")) { // 卡片操作-执行批处理APDU命令
		int offset = atoi(requestParam[2]); // 读取数据的文件偏移地址
		char bytes = (char) atoi(requestParam[3]); // 要读取的字节数
		SmartCom::string strData; // 输出参数 读取的转换成十六进制字符串的数据
		int resultCode = GetScriptData(communicator, offset, bytes, strData, cardId);
		sendData(client, strData);
		return resultCode;
	} else if (operationName == CString("checkBatchResult")) { // 查询执行批处理APDU结果
		SmartCom::string retCode; // 输出参数, 最后一条指令的返回值
		int resultCode = CheckBatchResult(communicator, retCode, cardId);
		sendData(client, retCode);
		return resultCode;
	} else if (operationName == CString("modifyCardPower")) { // 修改卡片电源
		int power = atoi(requestParam[2]); // 
		int card = atoi(requestParam[3]);
		return ModifyCardPower(communicator, power, card, cardId);
	} else if (operationName == CString("getDevIdAndMacNo")) { // 读取终端设备id号和机号
		SmartCom::string devID; // out, 存放7字节id号
		int macNo; // out, 1字节机号
		int retCode = GetDevIDAndMacNo(communicator, devID, macNo);
		sendData(client, devID + "," + i2str(macNo));
		return retCode;
	} else if (operationName == CString("setMacNoByDevID")) { // 设置终端设备id号和机号
		char* devID = (LPSTR)(LPCTSTR) requestParam[2]; 
		int macNo = atoi(requestParam[3]);
		return SetMacNoByDevID(communicator, devID, macNo);
	} else if (operationName == CString("getAppVerAndDevType")) { // 读取程序版本和终端类型
		SmartCom::string appVersion; // 程序版本
		SmartCom::string devType; // 终端类型
		int resultCode = GetAppVerAndDevType(communicator, appVersion, devType, cardId);
		sendData(client, appVersion + "," + devType);
		return resultCode;
	} else if (operationName == CString("getChipID")) { // 获取读卡接口芯片ID号
		SmartCom::string chipID;
		int resultCode = GetChipID(communicator, chipID, cardId);
		sendData(client, chipID);
		return resultCode;
	} else if (operationName == CString("isCardReady")) { // 检测A卡和B卡座是否有卡
		int cardA; // out, 1,A卡座有卡；0，A卡座无卡
		int cardB; // out, 1,B卡座有卡；0，B卡座无卡
		int resultCode = IsCardReady(communicator, cardA, cardB, cardId);
		sendData(client, SmartCom::string(i2str(cardA)) + "," + i2str(cardB));
		return resultCode;
	} else if (operationName == CString("resetCard")) { // 卡片复位应答
		SmartCom::string retCode; // out 复位命令的返回值, "F9"：卡座无卡, "FD"：不可识别卡
		int card = atoi(requestParam[2]); // 1 A卡, 2 B卡
		int resultCode = ResetCard(communicator, retCode, card, cardId);
		sendData(client, retCode);
		return resultCode;
	}

// 	if (CloseUDPComm() == -1)
// 	{
// 		AfxMessageBox("关闭udp通信失败");
// 		SimpleLog::error("关闭udp通信失败");
// 		return -102; // 关闭udp通信失败
// 	}

	return -100; // 命令找不到
}

int sendData(SOCKET s, const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	if (-1 == size) {
		SimpleLog::info(CString("发送数据错误, 数据: ") + buff);
	} else {
		SimpleLog::info(CString("发送数据, 长度: ") + i2str(size) + ", 数据: " + buff);
	}
	
	return size;
}

int sendData(SOCKET s, int data)
{
	return sendData(s, i2str(data));
}

int sendData(SOCKET s, SmartCom::string data)
{
	return sendData(s, data.c_str());
}