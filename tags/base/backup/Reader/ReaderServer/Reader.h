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
	int GetData();

public:
/*	static HANDLE mutex;*/
private:
	int _i;
};

/**
 * 读卡器和mutex组成的结构体, 模拟互斥访问读卡器
 */
typedef struct _CardReader{
	/// 读卡器
	Reader* reader;
	/// 等待处理队列
	HANDLE hMutex; 
} CardReader, *p_CardReader;

#endif