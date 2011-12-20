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
	// 读取配置文件
	ifstream fin("readers.config");
	string config;
	if (!(fin >> config))
	{
		AfxMessageBox("读卡器配置文件读取错误");
	}
	vector<string> result = splitString(config.c_str());
	for (vector<string>::iterator iter = result.begin(); iter != result.end(); ++iter)
	{
		int data = atoi((*iter).c_str());
		this->readerIdSet.insert(data);
	}
	fin.close();
}

void ServerParam::saveConfig() 
{
	// 保存配置到
	ofstream fout("readers.config");
	for (set<int>::iterator iter = this->readerIdSet.begin(); iter != this->readerIdSet.end(); ++iter)
	{
		fout << (*iter) << ",";
	}
	fout.close();
}