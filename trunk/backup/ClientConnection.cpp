//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.cpp
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision: 12 $
// $LastChangedDate: 2011-11-30 09:45:44 +0800 (å‘¨ä¸‰, 30 åä¸€æœˆ 2011) $
// Comment: ¿Í»§¶ËÓÃÀ´Á¬½Óµ½·þÎñÆ÷µÄ·â×°, ²¢·¢ËÍÊý¾Ý, Ä¬ÈÏ¿ªÆôÈÕÖ¾¼ÇÂ¼
//////////////////////////////////////////////////////////////////////////
#include "ClientConnection.h"

ClientConnection::ClientConnection(char* servername, int p, int id)
{
	ASSERT(!WSAStartup(0x101, &this->wsaData)); //³õÊ¼»¯winsock»·¾³
	this->serverName = servername;
	ASSERT(p >= 0 && p <= 65535); //±£Ö¤¶Ë¿ÚµÄÊäÈë·¶Î§ÊÇÕýÈ·µÄ
	this->port = p;

	this->isLog = true; // default ¼ÇÂ¼ÈÕÖ¾
	this->readerId = id;

	this->client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server;
	this->getServerAddr(server);
	connect(this->client, (struct sockaddr*)&server, sizeof(server)); // Á¬½Ósocket
	if (this->isLogged())
	{
		SimpleLog::info(CString("Á¬½Ó·þÎñÆ÷") + this->serverName + "³É¹¦"); // log
	}
	
}

ClientConnection::~ClientConnection()
{
	closesocket(this->client);
	WSACleanup(); // ÇåÀíwinsock»·¾³
}

void ClientConnection::getServerAddr(struct sockaddr_in& server)
{
	// ÉèÖÃserverµØÖ·
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
	sprintf(buff, "%d", this->readerId); // ÇëÇó¶Á¿¨Æ÷µÄid
	if (this->isLogged())
		SimpleLog::info(CString("ÇëÇóid: ") + buff);
	send(this->client, buff, sizeof(buff), 0);
	
	memset(buff, 0, 512);
	int z = recv(this->client, buff, 512, 0);
	ASSERT(z != -1); // ½ÓÊÕµ½µÄÊý¾Ý³¤¶ÈÎª-1, ±íÃ÷³ÌÐò´íÎó
	buff[z] = '\0'; // c-style×Ö·û´®
	if (this->isLogged())
	{
		SimpleLog::info(CString("´Ó·þÎñÆ÷½ÓÊÕµ½µÄÊý¾Ý: ") + buff);
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
