//////////////////////////////////////////////////////////////////////////
// FileName: Reader.h
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : 读卡器的定义
//////////////////////////////////////////////////////////////////////////
#ifndef _READER_H_
#define _READER_H_

#include <windows.h>

/**
 * 模拟读卡器的类, 就这个样子吧
 * @brief 模拟读卡器
 */
class Reader
{
public:
	/**
	 * 构造函数
	 * @param i 读卡器id
	 */
	Reader(int i);
	/**
	 * 析构函数
	 */
	virtual ~Reader();
	/**
	 * 获取数据
	 * @return None
	 */
	void GetData();

public:
/*	static HANDLE mutex;*/
private:
	int _i;
};

#endif