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
	//设置CPU亲和力//////////////////////////////////////////////////////////////////////////
    CString strPath = ".\\SystemConfig\\SystemConfig.ini";
	CString temstr;
	int CpuId;
    char buf[128];
	memset(buf,0,128);
	GetPrivateProfileString("CPUTYPE","IsEnableSingleCpu","",buf,MAX_PATH,strPath);
	temstr = buf;
	temstr.ReleaseBuffer();
	if ("1" == temstr)
	{
		memset(buf,0,128);
		GetPrivateProfileString("CPUTYPE","CpuId","",buf,MAX_PATH,strPath);
		temstr = buf;
		temstr.ReleaseBuffer();
		if ("" == temstr)
		{
			CpuId  = 1;
		}
		else
		{
			CpuId = atoi(temstr);
		}
		int p=SetProcessAffinityMask(GetCurrentProcess(),CpuId);    //设置CPU的亲和力将CpuId的值分别设置为1，2
	}
 //设置CPU亲和力//////////////////////////////////////////////////////////////////////////End
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