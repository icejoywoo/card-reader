#include "ServerUtils.h"

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	// ����Ĭ�ϵ�split����
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
			Server::getInstance()->log = ""; // �����־
		}
		Sleep(500);
	}
	
	return 0;
}

void GetIpAndPort(CString& ip, int& port, int id, ServerParam* param)
{
	// ÿ��ip��Ӧ32��������, ÿ����������Ӧһ��port, portĬ�ϴ�10000��ʼ
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
	operationName = requestParam[0]; // ��������
	int cardId = atoi(requestParam[1]); // ��������
	
	CString ip; // ��������Ӧ��ip
	int port; // ��������Ӧ�Ķ˿ں�
	Communicator communicator; // �������ͨ�ŵ�ͨ��
	
	GetIpAndPort(ip, port, cardId, ServerParam::instance); 
	GetOneUDPCommunicator(communicator, ip, port); // ���ͨ����

	if (InitUDPComm() == -1) {
		AfxMessageBox("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		SimpleLog::error("�뿨Ƭ��д����ͨ�ų�ʼ��ʧ��");
		return -101; // �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
	}

	if (operationName == CString("reset")) { // ��λ����
		return ResetDev(communicator, cardId);
	} else if (operationName == CString("shutdown")) { // ��Ƭ�µ�
		return ShutdownCard(communicator, cardId);
	} else if (operationName == CString("clearMemory")) { // ��SST25VF016B�洢��������Ƭ����
		return ClearMem(communicator);
	} else if (operationName == CString("modifyBraudRate")) { // �޸ı�����
		int braudRate = atoi(requestParam[2]);
		return ModifyCardBraudRate(communicator, braudRate, cardId);
	} else if (operationName == CString("getBraudRate")) { // ��ñ�����
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate, cardId);
		sendData(client, braudRate);
		return resultCode;
	}

	if (CloseUDPComm() == -1)
	{
		AfxMessageBox("�ر�udpͨ��ʧ��");
		SimpleLog::error("�ر�udpͨ��ʧ��");
		return -102; // �ر�udpͨ��ʧ��
	}

	return -100; // �����Ҳ���
}

int sendData(SOCKET s, char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(s, buff, strlen(buff), 0);
	if (-1 == size) {
		SimpleLog::info(CString("�������ݴ���, ����: ") + buff);
	} else {
		SimpleLog::info(CString("��������, ����: ") + i2str(size) + ", ����: " + buff);
	}
	
	return size;
}

int sendData(SOCKET s, int data)
{
	char buff[512];
	sprintf(buff, i2str(data));
	int size = send(s, buff, strlen(buff), 0);
	if (-1 == size) {
		SimpleLog::info(CString("�������ݴ���, ����: ") + buff);
	} else {
		SimpleLog::info(CString("��������, ����: ") + i2str(size) + ", ����: " + buff);
	}
	return size;
}