#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <time.h>
#include "CardReaderClientDll.h"

using namespace std;

#pragma comment(lib, "CardReaderClientDll.lib")

/**
在操作读卡器之前, 获取读卡器, 最后进行释放, 对读卡器的操作夹在中间, 例子如下:
	// 配置读卡器
	Reader* reader = new Reader();
	reader->readerId = 248; // 读卡器id

	// 获取读卡器
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}

	// 进行读卡器的操作...

	// 释放读卡器
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}

	// 释放内存
	delete reader;
*/
int main(int argc, char* args[])
{
	// 配置读卡器
	Reader* reader = new Reader();
	reader->readerId = 1; // 读卡器id

	// 获取读卡器
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}


	// 修改读卡器id
// 	{
// 		char devID[512];
// 		int readerId;
// 		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
// 		{
// 			printf("GetDevIDAndReaderId Failed.");
// 		}
// 		cout << devID << ", " << readerId << endl;
// 	
// 		
// 		if (0 != SetReaderIdByDevID(reader, devID, 4))
// 		{
// 			printf("SetReaderIdByDevID Failed.");
// 		}
// 	}
	
	// 获取读卡器id
	{
		char devID[512] = {0};
		int readerId = 0;
		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
		{
			printf("GetDevIDAndReaderId Failed.");
		}
 		cout << devID << ", " << readerId << endl;
	}

	// 读取程序版本和终端类型
	{
		char appVer[512] = {0};
		char devType[512] = {0};
		if (0 != GetAppVerAndDevType(reader, appVer, 512, devType, 512))
		{
			printf("GetAppVerAndDevType Failed.");
		}
		cout << appVer << ", " << devType << endl;
	}

	// 获取芯片id(调用复位之后调用这个, 会出错)
	{
		char chipID[512] = {0};
		if (0 != GetChipID(reader, chipID, 512))
		{
			printf("GetChipID failed.");
		}
		cout << chipID << endl;
	}

	// 检测A卡和B卡座是否有卡
	{
		int cardA = -1;
		int cardB = -1;
		if (0 != IsCardReady(reader, cardA, cardB))
		{
			printf("IsCardReady failed.");
		}
		cout << cardA << ", " << cardB << endl;
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

	// 修改波特率
// 	{
// 		if (0 != ModifyCardBraudRate(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}

	// 查看波特率
	{
		int braudRate = 0;
		if (0 != GetCardBraudRate(reader, braudRate))
		{
			printf("ModifyCardBraudRate failed.");
		}
		cout << braudRate << endl;
	}

	// 修改电源
// 	{
// 		if (0 != ModifyCardPower(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}
	
	// 擦除存储器
// 	{
// 		if (0 != ClearMem(reader)) 
// 		{
// 			printf("擦除存储器失败\n");
// 		}
// 	}

	// 下载文件(Attention:文件应该放在服务器端的, 下载文件之前先擦除存储器)
// 	{
// 		if (0 != DownloadFile(reader, 2, "apdu_head.bin")) // 下载头文件
// 		{
// 			printf("下载头文件失败\n");
// 		}
// 		if (0 != DownloadFile(reader, 1, "apdu_body.bin")) // 下载体文件
// 		{
// 			printf("下载体文件失败\n");
// 		}
// 	}
	
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

	// CheckBatchResult
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

	// 释放读卡器
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	
	delete reader; // 释放内存
	
	return 0;
}
