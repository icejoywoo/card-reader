//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision: 12 $
// $LastChangedDate: 2011-11-30 09:45:44 +0800 (周三, 30 十一月 2011) $
// Comment: �ͻ����������ӵ��������ķ�װ, ����������, Ĭ�Ͽ�����־��¼
//////////////////////////////////////////////////////////////////////////
#include "ClientConnection.h"

ClientConnection::ClientConnection(char* servername, int p, int id)
{
	ASSERT(!WSAStartup(0x101, &this->wsaData)); //��ʼ��winsock����
	this->serverName = servername;
	ASSERT(p >= 0 && p <= 65535); //��֤�˿ڵ����뷶Χ����ȷ��
	this->port = p;

	this->isLog = true; // default ��¼��־
	this->readerId = id;

	this->client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server;
	this->getServerAddr(server);
	connect(this->client, (struct sockaddr*)&server, sizeof(server)); // ����socket
	if (this->isLogged())
	{
		SimpleLog::info(CString("���ӷ�����") + this->serverName + "�ɹ�"); // log
	}
	
}

ClientConnection::~ClientConnection()
{
	closesocket(this->client);
	WSACleanup(); // ����winsock����
}

void ClientConnection::getServerAddr(struct sockaddr_in& server)
{
	// ����server��ַ
	struct hostent *hp;
	unsigned int addr;
	
	if(inet_addr(this->serverName)==INADDR_NONE)
	{
		hp=gethostbyname(this->serverName);
	}
	else
	{
		addr=inet_addr(this->serverName);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(this->port);
}

int ClientConnection::recvData(char* data)
{
	char buff[512];
	sprintf(buff, "%d", this->readerId); // �����������id
	if (this->isLogged())
		SimpleLog::info(CString("����id: ") + buff);
	send(this->client, buff, sizeof(buff), 0);
	
	memset(buff, 0, 512);
	int z = recv(this->client, buff, 512, 0);
	ASSERT(z != -1); // ���յ������ݳ���Ϊ-1, �����������
	buff[z] = '\0'; // c-style�ַ���
	if (this->isLogged())
	{
		SimpleLog::info(CString("�ӷ��������յ�������: ") + buff);
	}
	data = buff;
	return z;
}

bool ClientConnection::isLogged()
{
	return this->isLog;
}

void ClientConnection::setLog(bool log)
{
	this->isLog = log;
}
