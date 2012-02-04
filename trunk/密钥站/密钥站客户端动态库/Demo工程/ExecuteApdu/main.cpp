#include <stdio.h>
#include <iostream.h>
#include "CardReaderClientDll.h"

#pragma comment(lib, "CardReaderClientDll.lib")

int main(void)
{
	// 配置读卡器
	Reader* reader = new Reader();
	reader->readerId = 248; // 读卡器id
	
	// 获取读卡器
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}
	
	// 复位应答
	{
		SmartCom::string retCode = "empty";
		if (0 != ResetCard(reader, retCode))
		{
			printf("ResetCard failed.");
		}
		cout << "复位应答:" << retCode.c_str() << endl;
	}

	// 执行单条命令(执行前需要先复位应答)
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00820000083132333435363738";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed.");
		}
		cout << retCode.c_str() << endl;
	}

	// 卡片下电
	{
		if (0 != ShutdownCard(reader))
		{
			printf("ShutdownCard failed.");
		}
	}
	
	// 释放读卡器
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	
	// 释放内存
	delete reader;
	
	return 0;
}