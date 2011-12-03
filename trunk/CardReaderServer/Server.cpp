//////////////////////////////////////////////////////////////////////////
// FileName: Server.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision$
// $LastChangedDate$
// Comment: �������˵ļ򵥷�װ
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CardReaderServerDlg.h"

Server* Server::instance = new Server();

Server::Server()
{
	WSAStartup(MAKEWORD(2,2), &this->wsaData); // init winsock
	this->port = DEFAULT_PORT;
	this->log = "";

	this->clientHandler = defaultClientHandler;
	this->serverHandler = defaultServerHandler;
}

Server::~Server()
{
	WSACleanup(); // clean up winsock
	delete this->instance;
}

int Server::start()
{
	HANDLE thread = AfxBeginThread(this->serverHandler, this);
	return 0;
}

int Server::stop()
{
	// shutdown��ʧ��
// 	if (shutdown(this->server, SD_BOTH) != 0)
// 	{
// 		return -1;
// 	}
	if (closesocket(this->server) != 0)
	{
		SimpleLog::error("�ر�ʧ��");
		return -2;
	}
	SimpleLog::info("�������ѹر�");
	return 0;
}

int Server::restart()
{
	int result = 0;
	this->stop();
	if ((result = this->start()) != 0)
	{
		SimpleLog::error("����ʧ��");
		return result;
	}
	//SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(Server::getInstance()->getPort()));
	return 0;
}

int Server::setPort(int &port)
{
	this->port = port;
	// return this->restart();
	//WSACleanup();
	//WSAStartup(MAKEWORD(2,2), &this->wsaData);
	return 0;
}
/// Server�������

//////////////////////////////////////////////////////////////////////////
/// Ĭ�ϵ�handlers���� 
//////////////////////////////////////////////////////////////////////////

// TODO: �޸�handler
UINT defaultServerHandler(LPVOID pParam)
{
	Server* serv = (Server*) pParam;
	
	if ((serv->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		return -1;
	}
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(serv->getPort());
	
	if (bind(serv->server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return -2;
	}
	
	if (listen(serv->server, 64) != 0)
	{
		return -3;
	}
	
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);
	SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(serv->getPort()));
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET)
		{
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		AfxBeginThread(serv->clientHandler, (LPVOID)client);
	}
	return 0;
}

// TODO: �޸�handler, ��ȡ������������
UINT defaultClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	char buff[512]; // buffer

// 	sprintf(buff, "Hello."); // ��������, ������Hello
// 	int size = send(clientParam->client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("��������: ") + buff);
// 	clientParam->server->log += formatLog(CString("��������: ") + buff);

	// ���ն�������cardId
	int size = recv(client, buff, 512, 0);
	buff[size] = '\0';

	SimpleLog::info(CString("��������: ") + buff);

	CString operationName;
	int resultCode;
	if ((resultCode= parseCommand(client, buff, operationName)) == 0)
	{
		SimpleLog::info(operationName + CString("�����ɹ�"));
	} else {
		SimpleLog::info("[" + operationName + CString("]����ʧ��, ������: ") + i2str(resultCode));
	}
	
	// ��������͵��ͻ���
	sprintf(buff, i2str(resultCode));
	if ((size = send(client, buff, strlen(buff), 0)) == -1)
	{
		AfxMessageBox("���ݷ���ʧ��");
		SimpleLog::error(CString("���ݷ���ʧ��"));
	} else {
		SimpleLog::info(CString("��������, ����: ") + i2str(size) + ", ����: " + buff);
	}

	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);

	return 0;
}
