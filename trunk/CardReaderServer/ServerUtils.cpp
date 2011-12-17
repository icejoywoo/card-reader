//////////////////////////////////////////////////////////////////////////
// FileName: ServerUtils.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: һЩ�������Ĺ��߷���, ʵ��
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
	operationName = requestParam[0]; // ��������
	
	// ȡ�����ߵĿհ�
// 	operationName.TrimLeft();
// 	operationName.TrimRight();

	Communicator communicator; // �������ͨ�ŵ�ͨ��

	// readerId�ĺ���, ��ʾ��������Ӧ��com��
// 	if (GetOneCOMCommunicator(communicator, readerId) != 0) // ��ȡͨ����, �ڶ���������
// 	{
// 		SimpleLog::error("ͨ������ʼ��ʧ��");
// 		return GET_COMMUNICATOR_FAILED;
// 	}
	// TODO: ����ʹ��, ʹ��udpͨ����
	const char* dstIP = "192.168.1.138";
	int port = 10000 + readerId;
	if (GetOneUDPCommunicator(communicator, dstIP, port) != 0)// ��ȡͨ����, �ڶ���������
	{
		SimpleLog::error("ͨ������ʼ��ʧ��");
		return GET_COMMUNICATOR_FAILED;
	}
	sprintf(log, "[������ %d]ͨ������ʼ�����", readerId);
	SimpleLog::info(log);

 	ULONG savedTimeout = client->getTimeout();
 	client->setTimeout(MAX_OPERATION_DURATION); // ��֤�������, ��Ĳ���������
	sprintf(log, "[������ %d]���ڽ���[%s]����...", readerId, operationName.c_str());
	SimpleLog::info(log);
	
	int functionReturn = -1; // ����ִ�з���ֵ

	// refer to SmartCom.h
	if (operationName.compare("reset") == 0) { // ��λ����
		functionReturn = ResetDev(communicator);

	} else if (operationName.compare("shutdown") == 0) { // ��Ƭ�µ�
		functionReturn = ShutdownCard(communicator);

	} else if (operationName.compare("clearMemory") == 0) { // ��SST25VF016B�洢��������Ƭ����
		functionReturn = ClearMem(communicator);

	} else if (operationName.compare("modifyBraudRate") == 0) { // �޸ı�����
		int braudRate = atoi(requestParam[1].c_str());
		functionReturn = ModifyCardBraudRate(communicator, braudRate);

	} else if (operationName.compare("getBraudRate") == 0) { // ��ñ�����
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate);
		client->sendData(braudRate);
		functionReturn = resultCode;

	} else if (operationName.compare("downloadFile") == 0) { // �����ļ�
		int flag = atoi(requestParam[1].c_str()); // 1 �����������ļ�, 2 ��������ͷ�ļ�
		const char* fileName = requestParam[2].c_str(); // �ļ���
		functionReturn = DownloadFile(communicator, flag, fileName);

	} else if (operationName.compare("cardApdu") == 0) { // ��Ƭ����-ִ��APDU����
		const char* apdu = requestParam[1].c_str(); // apdu����
		int card = atoi(requestParam[2].c_str()); // 1 ΪA��, 2 ΪB��
		SmartCom::string retCode; // �������, ִ��apduָ��ķ���ֵ
		int resultCode = CardApdu(communicator, apdu, retCode, card);
		client->sendData(retCode);
		functionReturn = resultCode;

	} else if (operationName.compare("executeMulApdu") == 0) { // ��Ƭ����-ִ��������APDU����
		int cmdNum = atoi(requestParam[1].c_str());
		int card = atoi(requestParam[2].c_str()); // 1 ΪA��, 2 ΪB��
		functionReturn = ExcuteMulAPDU(communicator, cmdNum, card);

	} else if (operationName.compare("getScript") == 0) { // ������������ƽű��ļ�
		int offset = atoi(requestParam[1].c_str()); // ��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
		char bytes = (char) atoi(requestParam[2].c_str()); // Ҫ��ȡ���ֽ���
		SmartCom::string strData; // ������� ��ȡ��ת����ʮ�������ַ���������
		int resultCode = GetScriptData(communicator, offset, bytes, strData);
		if (resultCode == 0) {
			client->sendData(strData);
		} else {
			client->sendData("getScript_wrong");
		}
		functionReturn = resultCode;

	} else if (operationName.compare("checkBatchResult") == 0) { // ��ѯִ��������APDU���
		SmartCom::string retCode; // �������, ���һ��ָ��ķ���ֵ
		int resultCode = CheckBatchResult(communicator, retCode);
		if (resultCode >= 0) {
			client->sendData(retCode);
		} else {
			client->sendData("checkBatchResult_wrong");
		}
		functionReturn = resultCode;

	} else if (operationName.compare("modifyCardPower") == 0) { // �޸Ŀ�Ƭ��Դ
		int power = atoi(requestParam[1].c_str()); // 
		int card = atoi(requestParam[2].c_str());
		functionReturn = ModifyCardPower(communicator, power, card);

	} else if (operationName.compare("getDevIdAndReaderId") == 0) { // ��ȡ�ն��豸id�źͻ���
		SmartCom::string devID; // out, ���7�ֽ�id��
		int macNo; // out, 1�ֽڻ���
		int retCode = GetDevIDAndMacNo(communicator, devID, macNo);
		client->sendData(devID + "," + i2str(macNo));
		functionReturn = retCode;

	} else if (operationName.compare("setReaderIdByDevID") == 0) { // �����ն��豸id�źͻ���
		const char* devID = requestParam[1].c_str(); 
		int _readerId = atoi(requestParam[2].c_str());
		int ret = SetMacNoByDevID(communicator, devID, _readerId);
		if (0 == ret) {
			readerId = _readerId;
		}
		functionReturn = ret;

	} else if (operationName.compare("getAppVerAndDevType") == 0) { // ��ȡ����汾���ն�����
		SmartCom::string appVersion; // ����汾
		SmartCom::string devType; // �ն�����
		int resultCode = GetAppVerAndDevType(communicator, appVersion, devType);
		client->sendData(appVersion + "," + devType);
		functionReturn = resultCode;

	} else if (operationName.compare("getChipID") == 0) { // ��ȡ�����ӿ�оƬID��
		SmartCom::string chipID;
		int resultCode = GetChipID(communicator, chipID);
		client->sendData(chipID);
		functionReturn = resultCode;

	} else if (operationName.compare("isCardReady") == 0) { // ���A����B�����Ƿ��п�
		int cardA = -1; // out, 1,A�����п���0��A�����޿�
		int cardB = -1; // out, 1,B�����п���0��B�����޿�
		int resultCode = IsCardReady(communicator, cardA, cardB);
		client->sendData(SmartCom::string(i2str(cardA)) + "," + i2str(cardB));
		functionReturn = resultCode;

	} else if (operationName.compare("resetCard") == 0) { // ��Ƭ��λӦ��
		SmartCom::string retCode; // out ��λ����ķ���ֵ, "F9"�������޿�, "FD"������ʶ��
		int card = atoi(requestParam[1].c_str()); // 1 A��, 2 B��
		int resultCode = ResetCard(communicator, retCode, card);
		if (resultCode != 0)
		{
			client->sendData("ResetCard_wrong");
		} else {
			client->sendData(retCode);
		}
		functionReturn = resultCode;

	} else if (operationName.compare("quit") == 0) { // �˳�
		// �˳�ֱ�ӷ���ûʲô��˵��
		sprintf(log, "[������ %d]�������", readerId);
		SimpleLog::info(log);
		functionReturn = 0;
	} else {
		functionReturn = COMMAND_NOT_FOUND; // �����Ҳ���
	}

// 	if (CloseUDPComm() == -1)
// 	{
// 		AfxMessageBox("�ر�udpͨ��ʧ��");
// 		SimpleLog::error("�ر�udpͨ��ʧ��");
// 		return -102; // �ر�udpͨ��ʧ��
// 	}
	
	requestParam.clear(); // ɾ������
 	client->updateTimeout();
 	client->setTimeout(savedTimeout); // �ظ�ԭ����timeout

	return functionReturn;
}

int sendData(SOCKET s, const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	char log[512];
	if (-1 == size) {
		sprintf(log, "�������ݴ���, ����: [%s]", buff);
		SimpleLog::error(log);
	} else {
		sprintf(log, "��������, ����: %d, ����: [%s]", size, buff);
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
		SimpleLog::error("�������ݳ���");
		return size;
	}
	data[size] = '\0';
	sprintf(log, "��������: [%s]", data);
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