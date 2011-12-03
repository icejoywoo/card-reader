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

	if (InitUDPComm() == -1) {
		AfxMessageBox("与卡片读写器的通信初始化失败");
		SimpleLog::error("与卡片读写器的通信初始化失败");
		return -101; // 与卡片读写器的通信初始化失败
	}

	if (operationName == CString("reset")) { // 复位操作
		return ResetDev(communicator, cardId);
	} else if (operationName == CString("shutdown")) { // 卡片下电
		return ShutdownCard(communicator, cardId);
	} else if (operationName == CString("clearMemory")) { // 对SST25VF016B存储器进行整片擦除
		return ClearMem(communicator);
	} else if (operationName == CString("modifyBraudRate")) { // 修改比特率
		int braudRate = atoi(requestParam[2]);
		return ModifyCardBraudRate(communicator, braudRate, cardId);
	} else if (operationName == CString("getBraudRate")) { // 获得比特率
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate, cardId);
		sendData(client, braudRate);
		return resultCode;
	}

	if (CloseUDPComm() == -1)
	{
		AfxMessageBox("关闭udp通信失败");
		SimpleLog::error("关闭udp通信失败");
		return -102; // 关闭udp通信失败
	}

	return -100; // 命令找不到
}

int sendData(SOCKET s, char* data)
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
	char buff[512];
	sprintf(buff, i2str(data));
	int size = send(s, buff, strlen(buff), 0);
	if (-1 == size) {
		SimpleLog::info(CString("发送数据错误, 数据: ") + buff);
	} else {
		SimpleLog::info(CString("发送数据, 长度: ") + i2str(size) + ", 数据: " + buff);
	}
	return size;
}