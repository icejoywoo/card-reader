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

int parseCommand(Client* client, int readerId, char* command, CString& operationName)
{
	ServerParam::instance->split.SetData(CString(command));
	vector<CString> requestParam; // operationName, cardId, params
	ServerParam::instance->split.GetSplitStrArray(requestParam);
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
	SimpleLog::info(CString("[������ ") + i2str(readerId) + "]ͨ������ʼ�����");

 	ULONG savedTimeout = client->getTimeout();
 	client->setTimeout(MAX_OPERATION_DURATION); // ��֤�������, ��Ĳ���������

	SimpleLog::info(CString("[������ ") + i2str(readerId) + "]���ڽ���[" + operationName + "]����...");
	
	int functionReturn = -1; // ����ִ�з���ֵ

	// refer to SmartCom.h
	if (operationName == CString("reset")) { // ��λ����
		functionReturn = ResetDev(communicator);
	} else if (operationName == CString("shutdown")) { // ��Ƭ�µ�
		functionReturn = ShutdownCard(communicator);
	} else if (operationName == CString("clearMemory")) { // ��SST25VF016B�洢��������Ƭ����
		functionReturn = ClearMem(communicator);
	} else if (operationName == CString("modifyBraudRate")) { // �޸ı�����
		int braudRate = atoi(requestParam[1]);
		functionReturn = ModifyCardBraudRate(communicator, braudRate);
	} else if (operationName == CString("getBraudRate")) { // ��ñ�����
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate);
		client->sendData(braudRate);
		functionReturn = resultCode;
	} else if (operationName == CString("downloadFile")) { // �����ļ�
		int flag = atoi(requestParam[1]); // 1 �����������ļ�, 2 ��������ͷ�ļ�
		char* fileName = (LPSTR)(LPCTSTR)requestParam[2]; // �ļ���
		functionReturn = DownloadFile(communicator, flag, fileName);
	} else if (operationName == CString("cardApdu")) { // ��Ƭ����-ִ��APDU����
		char* apdu = (LPSTR)(LPCTSTR)requestParam[1]; // apdu����
		int card = atoi(requestParam[2]); // 1 ΪA��, 2 ΪB��
		SmartCom::string retCode; // �������, ִ��apduָ��ķ���ֵ
		int resultCode = CardApdu(communicator, apdu, retCode, card);
		client->sendData(retCode);
		functionReturn = resultCode;
	} else if (operationName == CString("executeMulApdu")) { // ��Ƭ����-ִ��������APDU����
		int cmdNum = atoi(requestParam[1]);
		int card = atoi(requestParam[2]); // 1 ΪA��, 2 ΪB��
		functionReturn = ExcuteMulAPDU(communicator, cmdNum, card);
	} else if (operationName == CString("getScript")) { // ������������ƽű��ļ�
		int offset = atoi(requestParam[1]); // ��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
		char bytes = (char) atoi(requestParam[2]); // Ҫ��ȡ���ֽ���
		SmartCom::string strData; // ������� ��ȡ��ת����ʮ�������ַ���������
		int resultCode = GetScriptData(communicator, offset, bytes, strData);
		if (resultCode == 0) {
			client->sendData(strData);
		} else {
			client->sendData("getScript_wrong");
		}
		functionReturn = resultCode;
	} else if (operationName == CString("checkBatchResult")) { // ��ѯִ��������APDU���
		SmartCom::string retCode; // �������, ���һ��ָ��ķ���ֵ
		int resultCode = CheckBatchResult(communicator, retCode);
		if (resultCode >= 0) {
			client->sendData(retCode);
		} else {
			client->sendData("checkBatchResult_wrong");
		}
		functionReturn = resultCode;
	} else if (operationName == CString("modifyCardPower")) { // �޸Ŀ�Ƭ��Դ
		int power = atoi(requestParam[1]); // 
		int card = atoi(requestParam[2]);
		functionReturn = ModifyCardPower(communicator, power, card);
	} else if (operationName == CString("getDevIdAndReaderId")) { // ��ȡ�ն��豸id�źͻ���
		SmartCom::string devID; // out, ���7�ֽ�id��
		int macNo; // out, 1�ֽڻ���
		int retCode = GetDevIDAndMacNo(communicator, devID, macNo);
		client->sendData(devID + "," + i2str(macNo));
		functionReturn = retCode;
	} else if (operationName == CString("setReaderIdByDevID")) { // �����ն��豸id�źͻ���
		char* devID = (LPSTR)(LPCTSTR) requestParam[1]; 
		int _readerId = atoi(requestParam[2]);
		int ret = SetMacNoByDevID(communicator, devID, _readerId);
		if (0 == ret) {
			readerId = _readerId;
		}
		functionReturn = ret;
	} else if (operationName == CString("getAppVerAndDevType")) { // ��ȡ����汾���ն�����
		SmartCom::string appVersion; // ����汾
		SmartCom::string devType; // �ն�����
		int resultCode = GetAppVerAndDevType(communicator, appVersion, devType);
		client->sendData(appVersion + "," + devType);
		functionReturn = resultCode;
	} else if (operationName == CString("getChipID")) { // ��ȡ�����ӿ�оƬID��
		SmartCom::string chipID;
		int resultCode = GetChipID(communicator, chipID);
		client->sendData(chipID);
		functionReturn = resultCode;
	} else if (operationName == CString("isCardReady")) { // ���A����B�����Ƿ��п�
		int cardA = -1; // out, 1,A�����п���0��A�����޿�
		int cardB = -1; // out, 1,B�����п���0��B�����޿�
		int resultCode = IsCardReady(communicator, cardA, cardB);
		client->sendData(SmartCom::string(i2str(cardA)) + "," + i2str(cardB));
		functionReturn = resultCode;
	} else if (operationName == CString("resetCard")) { // ��Ƭ��λӦ��
		SmartCom::string retCode; // out ��λ����ķ���ֵ, "F9"�������޿�, "FD"������ʶ��
		int card = atoi(requestParam[1]); // 1 A��, 2 B��
		int resultCode = ResetCard(communicator, retCode, card);
		if (resultCode != 0)
		{
			client->sendData("ResetCard_wrong");
		} else {
			client->sendData(retCode);
		}
		functionReturn = resultCode;
	} else if (operationName == CString("quit")) { // �˳�
		// �˳�ֱ�ӷ���ûʲô��˵��
		SimpleLog::info(CString("[������ ") + i2str(readerId) + "]�������");
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

	if (-1 == size) {
		SimpleLog::error(CString("�������ݴ���, ����: [") + buff + "]");
	} else {
		SimpleLog::info(CString("��������, ����: ") + i2str(size) + ", ����: [" + buff + "]");
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
	if (-1 == size)
	{
		SimpleLog::error("�������ݳ���");
		return size;
	}
	data[size] = '\0';
	SimpleLog::info(CString("��������: [") + data + "]");
	return size;
}

int receiveData(SOCKET s, int& data)
{
	char str[512];
	int size = receiveData(s, str, 512);
	data = atoi(str);
	return size;
}