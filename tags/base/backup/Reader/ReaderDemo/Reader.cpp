//////////////////////////////////////////////////////////////////////////
// FileName: Reader.cpp
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : 读卡器的实现
//////////////////////////////////////////////////////////////////////////
#include "Reader.h"
#include <iostream>
#include <windows.h>

extern HANDLE mutex;

Reader::Reader(int i)
{
	_i = i;
}

Reader::~Reader()
{

}
/// Reader的成员函数
void Reader::GetData()
{
	WaitForSingleObject(mutex, INFINITE);
	std::cout << "Get data from reader "<< _i << "." << std::endl;
	ReleaseMutex(mutex);
	Sleep(100);
}