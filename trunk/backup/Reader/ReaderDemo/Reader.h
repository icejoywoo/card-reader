//////////////////////////////////////////////////////////////////////////
// FileName: Reader.h
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : �������Ķ���
//////////////////////////////////////////////////////////////////////////
#ifndef _READER_H_
#define _READER_H_

#include <windows.h>

/**
 * ģ�����������, ��������Ӱ�
 * @brief ģ�������
 */
class Reader
{
public:
	/**
	 * ���캯��
	 * @param i ������id
	 */
	Reader(int i);
	/**
	 * ��������
	 */
	virtual ~Reader();
	/**
	 * ��ȡ����
	 * @return None
	 */
	void GetData();

public:
/*	static HANDLE mutex;*/
private:
	int _i;
};

#endif