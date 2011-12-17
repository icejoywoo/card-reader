//////////////////////////////////////////////////////////////////////////
// FileName: ServerUtils.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 一些服务器的工具方法, 实现
//////////////////////////////////////////////////////////////////////////
#include "ServerUtils.h"

CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

int parseCommand(Client* client, int readerId, char* command, string& operationName)
{
	char log[512];
	vector<string> requestParam; // operationName, cardId, params
	requestParam = splitString(command);
	operationName = requestParam[0]; // 操作名称
	
	// 取出两边的空白
// 	operationName.TrimLeft();
// 	operationName.TrimRight();

	Communicator communicator; // 与读卡器通信的通信

	// readerId的含义, 表示读卡器相应的com号
// 	if (GetOneCOMCommunicator(communicator, readerId) != 0) // 获取通信器, 第二个参数与
// 	{
// 		SimpleLog::error("通信器初始化失败");
// 		return GET_COMMUNICATOR_FAILED;
// 	}
	// TODO: 测试使用, 使用udp通信器
	const char* dstIP = "192.168.1.138";
	int port = 10000 + readerId;
	if (GetOneUDPCommunicator(communicator, dstIP, port) != 0)// 获取通信器, 第二个参数与
	{
		SimpleLog::error("通信器初始化失败");
		return GET_COMMUNICATOR_FAILED;
	}
	sprintf(log, "[读卡器 %d]通信器初始化完成", readerId);
	SimpleLog::info(log);

 	ULONG savedTimeout = client->getTimeout();
 	client->setTimeout(MAX_OPERATION_DURATION); // 保证操作完成, 最长的操作是下载
	sprintf(log, "[读卡器 %d]正在进行[%s]操作...", readerId, operationName.c_str());
	SimpleLog::info(log);
	
	int functionReturn = -1; // 函数执行返回值

	// refer to SmartCom.h
	if (operationName.compare("reset") == 0) { // 复位操作
		functionReturn = ResetDev(communicator);

	} else if (operationName.compare("shutdown") == 0) { // 卡片下电
		functionReturn = ShutdownCard(communicator);

	} else if (operationName.compare("clearMemory") == 0) { // 对SST25VF016B存储器进行整片擦除
		functionReturn = ClearMem(communicator);

	} else if (operationName.compare("modifyBraudRate") == 0) { // 修改比特率
		int braudRate = atoi(requestParam[1].c_str());
		functionReturn = ModifyCardBraudRate(communicator, braudRate);

	} else if (operationName.compare("getBraudRate") == 0) { // 获得比特率
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate);
		client->sendData(braudRate);
		functionReturn = resultCode;

	} else if (operationName.compare("downloadFile") == 0) { // 下载文件
		int flag = atoi(requestParam[1].c_str()); // 1 下载命令体文件, 2 下载命令头文件
		const char* fileName = requestParam[2].c_str(); // 文件名
		functionReturn = DownloadFile(communicator, flag, fileName);

	} else if (operationName.compare("cardApdu") == 0) { // 卡片操作-执行APDU命令
		const char* apdu = requestParam[1].c_str(); // apdu命令
		int card = atoi(requestParam[2].c_str()); // 1 为A卡, 2 为B卡
		SmartCom::string retCode; // 输出参数, 执行apdu指令的返回值
		int resultCode = CardApdu(communicator, apdu, retCode, card);
		client->sendData(retCode);
		functionReturn = resultCode;

	} else if (operationName.compare("executeMulApdu") == 0) { // 卡片操作-执行批处理APDU命令
		int cmdNum = atoi(requestParam[1].c_str());
		int card = atoi(requestParam[2].c_str()); // 1 为A卡, 2 为B卡
		functionReturn = ExcuteMulAPDU(communicator, cmdNum, card);

	} else if (operationName.compare("getScript") == 0) { // 读批处理二进制脚本文件
		int offset = atoi(requestParam[1].c_str()); // 读取数据的文件偏移地址
		char bytes = (char) atoi(requestParam[2].c_str()); // 要读取的字节数
		SmartCom::string strData; // 输出参数 读取的转换成十六进制字符串的数据
		int resultCode = GetScriptData(communicator, offset, bytes, strData);
		if (resultCode == 0) {
			client->sendData(strData);
		} else {
			client->sendData("getScript_wrong");
		}
		functionReturn = resultCode;

	} else if (operationName.compare("checkBatchResult") == 0) { // 查询执行批处理APDU结果
		SmartCom::string retCode; // 输出参数, 最后一条指令的返回值
		int resultCode = CheckBatchResult(communicator, retCode);
		if (resultCode >= 0) {
			client->sendData(retCode);
		} else {
			client->sendData("checkBatchResult_wrong");
		}
		functionReturn = resultCode;

	} else if (operationName.compare("modifyCardPower") == 0) { // 修改卡片电源
		int power = atoi(requestParam[1].c_str()); // 
		int card = atoi(requestParam[2].c_str());
		functionReturn = ModifyCardPower(communicator, power, card);

	} else if (operationName.compare("getDevIdAndReaderId") == 0) { // 读取终端设备id号和机号
		SmartCom::string devID; // out, 存放7字节id号
		int macNo; // out, 1字节机号
		int retCode = GetDevIDAndMacNo(communicator, devID, macNo);
		client->sendData(devID + "," + i2str(macNo));
		functionReturn = retCode;

	} else if (operationName.compare("setReaderIdByDevID") == 0) { // 设置终端设备id号和机号
		const char* devID = requestParam[1].c_str(); 
		int _readerId = atoi(requestParam[2].c_str());
		int ret = SetMacNoByDevID(communicator, devID, _readerId);
		if (0 == ret) {
			readerId = _readerId;
		}
		functionReturn = ret;

	} else if (operationName.compare("getAppVerAndDevType") == 0) { // 读取程序版本和终端类型
		SmartCom::string appVersion; // 程序版本
		SmartCom::string devType; // 终端类型
		int resultCode = GetAppVerAndDevType(communicator, appVersion, devType);
		client->sendData(appVersion + "," + devType);
		functionReturn = resultCode;

	} else if (operationName.compare("getChipID") == 0) { // 获取读卡接口芯片ID号
		SmartCom::string chipID;
		int resultCode = GetChipID(communicator, chipID);
		client->sendData(chipID);
		functionReturn = resultCode;

	} else if (operationName.compare("isCardReady") == 0) { // 检测A卡和B卡座是否有卡
		int cardA = -1; // out, 1,A卡座有卡；0，A卡座无卡
		int cardB = -1; // out, 1,B卡座有卡；0，B卡座无卡
		int resultCode = IsCardReady(communicator, cardA, cardB);
		client->sendData(SmartCom::string(i2str(cardA)) + "," + i2str(cardB));
		functionReturn = resultCode;

	} else if (operationName.compare("resetCard") == 0) { // 卡片复位应答
		SmartCom::string retCode; // out 复位命令的返回值, "F9"：卡座无卡, "FD"：不可识别卡
		int card = atoi(requestParam[1].c_str()); // 1 A卡, 2 B卡
		int resultCode = ResetCard(communicator, retCode, card);
		if (resultCode != 0)
		{
			client->sendData("ResetCard_wrong");
		} else {
			client->sendData(retCode);
		}
		functionReturn = resultCode;

	} else if (operationName.compare("quit") == 0) { // 退出
		// 退出直接返回没什么好说的
		sprintf(log, "[读卡器 %d]操作完毕", readerId);
		SimpleLog::info(log);
		functionReturn = 0;
	} else {
		functionReturn = COMMAND_NOT_FOUND; // 命令找不到
	}

// 	if (CloseUDPComm() == -1)
// 	{
// 		AfxMessageBox("关闭udp通信失败");
// 		SimpleLog::error("关闭udp通信失败");
// 		return -102; // 关闭udp通信失败
// 	}
	
	requestParam.clear(); // 删除所有
 	client->updateTimeout();
 	client->setTimeout(savedTimeout); // 回复原来的timeout

	return functionReturn;
}

int sendData(SOCKET s, const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	char log[512];
	if (-1 == size) {
		sprintf(log, "发送数据错误, 数据: [%s]", buff);
		SimpleLog::error(log);
	} else {
		sprintf(log, "发送数据, 长度: %d, 数据: [%s]", size, buff);
		SimpleLog::info(log);
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

int receiveData(SOCKET s, char* data, int len)
{
	int size = recv(s, data, len, 0);
	char log[512];
	if (-1 == size || 0 == size)
	{
		SimpleLog::error("接收数据出错");
		return size;
	}
	data[size] = '\0';
	sprintf(log, "接收数据: [%s]", data);
	SimpleLog::info(log);
	return size;
}

int receiveData(SOCKET s, int& data)
{
	char str[512];
	int size = receiveData(s, str, 512);
	data = atoi(str);
	return size;
}

vector<string> splitString(char* splitedStr)
{
	string str(splitedStr);
	str.append(",");
	string::size_type first;
	string::size_type second;
	vector<string> result;

	first = str.find(",", 0);
	string one = str.substr(0, first);
	result.push_back(one);

	while ((second = str.find(",", first + 1)) != string::npos)
	{
		string others = str.substr(first + 1, (second - first - 1));
		first = second;
		result.push_back(others);
	}
	return result;
}