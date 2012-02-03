//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器ServerParam类是用来存放配置参数, 类的实现
//////////////////////////////////////////////////////////////////////////
#include "ServerParam.h"
#include "ServerUtils.h"
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	serverPort = getConfigInt("Server", "port");
	if (serverPort == 0) // 没有配置端口号, 使用默认端口号60000
	{
		serverPort = 60000; 
	}

	int count = getConfigInt("Readers", "count"); // 读卡器数量
	int i;
	char temp[512];

	for (i = 1; i <= count; ++i)
	{
		sprintf(temp, "%d", i);
		readers[i] = getConfigInt("Readers", temp);
	}
}

void ServerParam::saveConfig() 
{
	char temp[512];
	sprintf(temp, "%d", serverPort);
	writeConfig("Server", "port", temp);

	char temp2[512];
	for (map<int, int>::iterator iter = readers.begin(); iter != readers.end(); ++iter)
	{
		sprintf(temp, "%d", iter->first);
		sprintf(temp2, "%d", iter->second);
		writeConfig("Readers", temp, temp2);
	}

	int count = getConfigInt("Readers", "count");
	sprintf(temp, "%d", readers.size());
	writeConfig("Readers", "count", temp);
}