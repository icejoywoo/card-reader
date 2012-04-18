//////////////////////////////////////////////////////////////////////////
// FileName: ClientUrils.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// $Revision$
// Comment: 客户端一些辅助操作的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ClientUtils.h"
#include "ClientParam.h"
#include <string>
#include <time.h>

using namespace std;

ClientUtils::ClientUtils() {}
ClientUtils::~ClientUtils() {}

int ClientUtils::sendData(SOCKET server, const char* data)
{
	char buff[512];
	sprintf(buff, data);
	int size = send(server, data, strlen(buff), 0);
	if (size == -1 || size == 0)
	{
		return SOCKET_ERROR;
	}
	return 0;
}

int ClientUtils::sendData(SOCKET server, const string data)
{
	return ClientUtils::sendData(server, data.c_str());;
}

int ClientUtils::sendData(SOCKET server, int data)
{
	return ClientUtils::sendData(server, ClientUtils::i2str(data));
}

string ClientUtils::i2str(int a)
{
	char* str = new char[10];
	sprintf(str, "%d", a);
	string str2(str);
	delete str; // 删除堆内存
	return str2; // 返回string对象
}

int ClientUtils::receiveData(SOCKET s, char* data, int len)
{
	int size = recv(s, data, len, 0);
	if (-1 == size)
	{
		return size;
	}
	data[size] = '\0';
	return size;
}

int ClientUtils::receiveData(SOCKET s, int &data)
{
	char str[512];
	int size = receiveData(s, str, 512);
	// 当接收数据出错时
	if (-1 == size)
	{
		data = -1;
	}
	else
	{
		data = atoi(str);
	}
	return size;
}

void ClientUtils::splitString(const char* buf, string& first, string& second)
{
	string str(buf);
	string::size_type loc = str.find(",", 0);
	first = str.substr(0, loc);
	second = str.substr(loc + 1);
}

void ClientUtils::splitString(const char* buf, string& first, int& second)
{
	string str(buf);
	string::size_type loc = str.find(",", 0);
	first = str.substr(0, loc);
	string secondstr = str.substr(loc + 1);
	second = atoi(secondstr.c_str());
}

void ClientUtils::writeConfig(LPCTSTR lpAppName,  // section name
				 LPCTSTR lpKeyName,  // key name
				 LPCTSTR lpString   // string to add
				 )
{
	::WritePrivateProfileString(lpAppName, lpKeyName, lpString, CONFIG_PATH);
}

void ClientUtils::getConfig(LPCTSTR lpAppName,        // section name
			   LPCTSTR lpKeyName,        // key name
			   LPTSTR lpReturnedString,  // destination buffer
			   DWORD nSize              // size of destination buffer
			   )
{
	::GetPrivateProfileString(lpAppName, lpKeyName, "", lpReturnedString, nSize, CONFIG_PATH);
}

UINT ClientUtils::getConfigInt(LPCTSTR lpAppName,  // section name
				  LPCTSTR lpKeyName  // key name
				  )
{
	return ::GetPrivateProfileInt(lpAppName, lpKeyName, 0, CONFIG_PATH);
}

void ClientUtils::shutdownAndCloseSocket(SOCKET s)
{
	Sleep(10);
	shutdown(s, SD_SEND);
	Sleep(10);
	closesocket(s);
}

void ClientUtils::error(char* errMsg, int readerId, char* operationName)
{
	time_t t;
	time(&t);
	tm * current_tm = localtime(&t);
	fprintf(ClientParam::instance->errLog, "%04d.%02d.%02d %02d:%02d:%02d| [读卡器%d] [%s] Error: %s 错误码: %d\n", 
		current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec,
		readerId, operationName, errMsg, WSAGetLastError());
	fflush(ClientParam::instance->errLog);
}

void ClientUtils::info(char* infoMsg, int readerId, char* operationName)
{
	time_t t;
	time(&t);
	tm * current_tm = localtime(&t);
	fprintf(ClientParam::instance->log, "%04d.%02d.%02d %02d:%02d:%02d| [读卡器%d] [%s]: %s\n", 
		current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec,
		readerId, operationName, infoMsg);
	fflush(ClientParam::instance->log);
}
