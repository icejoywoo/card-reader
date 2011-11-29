//////////////////////////////////////////////////////////////////////////
// FileName: Reader.cpp
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : 读卡器的实现
//////////////////////////////////////////////////////////////////////////
#include "Reader.h"
#include <iostream>
#include <windows.h>

Reader::Reader(int i)
{
	_i = i;
	this->hMutex = CreateMutex(NULL, FALSE, NULL);
}

Reader::~Reader()
{

}
/// Reader的成员函数
int Reader::GetData()
{
	return this->_i;
}