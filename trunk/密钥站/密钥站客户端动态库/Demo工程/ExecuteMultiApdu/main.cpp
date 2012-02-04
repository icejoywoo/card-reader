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
	

	// 擦除存储器
	{
		if (0 != ClearMem(reader)) 
		{
			printf("擦除存储器失败\n");
		}
	}

	// 下载文件(Attention:文件应该放在服务器端的, 下载文件之前先擦除存储器)
	{
		if (0 != DownloadFile(reader, 2, "apdu_head.bin")) // 下载头文件
		{
			printf("下载头文件失败\n");
		}
		if (0 != DownloadFile(reader, 1, "apdu_body.bin")) // 下载体文件
		{
			printf("下载体文件失败\n");
		}
	}
	
	// 获取脚本数据(需要先下载文件)
	{
		SmartCom::string strData = "empty";
		if (0 != GetScriptData(reader, 0, 128, strData))
		{
			printf("GetScriptData失败\n");
		}
		cout << strData.c_str() << endl;
	}

	// 执行多条apdu(需要先下载文件)
	{
		int ret = ExcuteMulAPDU(reader, 5);
		if (0 != ret) // 下载头文件
		{
			printf("ExcuteMulAPDU失败\n");
		}
	}

	// 检查批处理结果
	{
		SmartCom::string retCode = "empty"; // 状态返回码
		int result = -1000; // 已执行的条数
		if ((result = CheckBatchResult(reader, retCode)) < 0)
		{
			printf("CheckBatchResult失败\n");
		}
		cout << result << "执行," <<retCode.c_str() << endl;
	}
	
	// 卡片下电
	{
		if (0 != ShutdownCard(reader))
		{
			printf("ShutdownCard failed.");
		}
	}

	// 释放内存
	delete reader;

	return 0;
}