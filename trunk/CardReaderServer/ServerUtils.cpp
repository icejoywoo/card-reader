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
	CStringArray requestParam; // cardId, operationName, params
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

	if (operationName == CString("reset")) { // ��λ����, ����ip��Ӧ��32��������
		return ResetDev(communicator);
	} else if (operationName == CString("shutdown")) { // ��Ƭ�µ�, ����ip��Ӧ��32��������
		return ShutdownCard(communicator);
	} else if (operationName == CString("clearMemory")) { // ��SST25VF016B�洢��������Ƭ����
		return ClearMem(communicator);
	} else if (operationName == CString("modifyBraudRate")) { // �޸ı�����, ����ip��Ӧ��32��������
		int braudRate = atoi(requestParam[2]);
		return ModifyCardBraudRate(communicator, braudRate);
	} else if (operationName == CString("getBraudRate")) { // ��ñ�����, ����ip��Ӧ��32��������
		int braudRate;
		int resultCode = GetCardBraudRate(communicator, braudRate);
		char buff[512];
		sprintf(buff, i2str(braudRate));
		int size = send(client, buff, strlen(buff), 0);
		return resultCode;
	}

	return -100; // �����Ҳ���
}
