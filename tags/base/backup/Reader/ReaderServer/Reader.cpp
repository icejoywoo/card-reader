//////////////////////////////////////////////////////////////////////////
// FileName: Reader.cpp
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : ��������ʵ��
//////////////////////////////////////////////////////////////////////////
#include "Reader.h"
#include <iostream>
#include <windows.h>

Reader::Reader(int i)
{
	_i = i;
}

Reader::~Reader()
{

}
/// Reader�ĳ�Ա����
int Reader::GetData()
{
	return this->_i;
}