//////////////////////////////////////////////////////////////////////////
// FileName: Reader.cpp
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : ��������ʵ��
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
/// Reader�ĳ�Ա����
void Reader::GetData()
{
	WaitForSingleObject(mutex, INFINITE);
	std::cout << "Get data from reader "<< _i << "." << std::endl;
	ReleaseMutex(mutex);
	Sleep(100);
}