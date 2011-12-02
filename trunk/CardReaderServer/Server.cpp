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

typedef struct _clientParam 
{
	Server* server;
	SOCKET client;
} ClientParam;

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
	SimpleLog::info(CString("�����������ɹ�, �˿�: ") + i2str(Server::getInstance()->getPort()));
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
	serv->log += formatLog(CString("�����������ɹ�, �˿�: ") + i2str(serv->getPort()));
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET)
		{
			break;
		}
		SimpleLog::info(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		serv->log += formatLog(CString("���յ�һ���ͻ�������, ����") + inet_ntoa(from.sin_addr));
		ClientParam clientParam;
		clientParam.server = serv;
		clientParam.client = client;
		AfxBeginThread(serv->clientHandler, (LPVOID)&clientParam);
	}
	return 0;
}

// TODO: �޸�handler, ��ȡ������������
UINT defaultClientHandler (LPVOID pParam)
{
	ClientParam* clientParam = (ClientParam *) pParam;
	char buff[512];
	SOCKET client = clientParam->client;

// 	sprintf(buff, "Hello."); // ��������, ������Hello
// 	int size = send(clientParam->client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("��������: ") + buff);
// 	clientParam->server->log += formatLog(CString("��������: ") + buff);

	// ���ն�������cardId
	int size = recv(client, buff, 512, 0);
	buff[size] = '\0';
	int cardId = atoi(buff);

	CString ip; // ��������Ӧ��ip
	int port; // ��������Ӧ�Ķ˿ں�
	Communicator communicator; // �������ͨ�ŵ�ͨ����
	
	GetIpAndPort(ip, port, cardId, ServerParam::instance); 
	GetOneUDPCommunicator()


	//Sleep(10000);
	shutdown(clientParam->client, SD_BOTH);
	closesocket(clientParam->client);

	return 0;
}
