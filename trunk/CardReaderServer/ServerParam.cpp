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

using namespace std;

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	// 读取配置文件
	ifstream fin("readers.config");
	string config;
	if (!(fin >> config))
	{
		AfxMessageBox("读卡器配置文件读取错误");
	}
//	vector<string> result = splitString(config.c_str());
	vector<string> result = splitString("1,2,3,4,5,6,7,8");
	for (vector<string>::iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		int data = atoi((*iter).c_str());
		this->readerIdSet.insert(data);
	}
	fin.close();
}