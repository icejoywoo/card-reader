//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ������ServerParam��������������ò���, ���ʵ��
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
	// ��ȡ�����ļ�
	ifstream fin("readers.config");
	string config;
	if (!(fin >> config))
	{
		AfxMessageBox("�����������ļ���ȡ����");
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
	// �������õ�
	ofstream fout("readers.config");
	for (set<int>::iterator iter = this->readerIdSet.begin(); iter != this->readerIdSet.end(); ++iter)
	{
		fout << (*iter) << ",";
	}
	fout.close();
}