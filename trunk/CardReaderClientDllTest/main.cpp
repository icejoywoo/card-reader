#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include "CardReaderClientDll.h"

using namespace std;

#pragma comment(lib, "CardReaderClientDll.lib")

string i2str(int a)
{
	char* str = new char[10];
	sprintf(str, "%d", a);
	return string(str);
}

int main(void)
{
// 	int   number   =   12345;  
// 	char   string[25];  
// 	
// 	itoa(number,   string,   10);  
// 
// 	printf( "integer   =   %d   string   =   %s\n ",   number,   i2str(number).c_str());
// 	return   0;

// 	char* buf = "00 03 00 E7 00 2F 75,1";
// 	char devID[512];
// 	int readerId;
// 	string str(buf);
// 
// 	string::size_type loc = str.find(",", 0);
// 	string first = str.substr(0, loc);
// 	strcpy(devID, first.c_str());
// 	string second = str.substr(loc + 1);
// 	readerId = atoi(second.c_str());
// 	cout << devID << ", " << readerId << endl;
// 	return 0;

	Reader* reader = new Reader();
	reader->readerId = 1;

	// 初始化客户端
	InitClient("127.0.0.1", 60000);

	// 获取读卡器
	if (0 != GetReader(reader, 1000, 1000))
	{
		printf("getReader Failed.");
	}


	// 获取读卡器id
	{
		char devID[512];
		int readerId;
		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
		{
			printf("GetDevIDAndReaderId Failed.");
		}
		cout << devID << ", " << readerId << endl;
	}
	
	// 修改读卡器id
// 	{
// 		if (0 != SetReaderIdByDevID(reader, devID, 1))
// 		{
// 			printf("SetReaderIdByDevID Failed.");
// 		}
// 	}
	
	// 获取读卡器id
// 	{
// 		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
// 		{
// 			printf("GetDevIDAndReaderId Failed.");
// 		}
//  		cout << devID << ", " << readerId << endl;
// 	}
	
	// 读取程序版本和终端类型
// 	{
// 		char appVer[512];
// 		char devType[512];
// 		if (0 != GetAppVerAndDevType(reader, appVer, 512, devType, 512))
// 		{
// 			printf("GetAppVerAndDevType Failed.");
// 		}
// 		cout << appVer << ", " << devType << endl;
// 	}

	// 获取芯片id(调用复位之后调用这个, 会出错)
// 	{
// 		char chipID[512];
// 		if (0 != GetChipID(reader, chipID, 512))
// 		{
// 			printf("GetChipID failed.");
// 		}
// 		cout << chipID << endl;
// 	}

	// 检测A卡和B卡座是否有卡
// 	{
// 		int cardA;
// 		int cardB;
// 		if (0 != IsCardReady(reader, cardA, cardB))
// 		{
// 			printf("IsCardReady failed.");
// 		}
// 		cout << cardA << ", " << cardB << endl;
// 	}
	
	// 复位应答
	{
		SmartCom::string retCode;
		if (0 != ResetCard(reader, retCode))
		{
			printf("ResetCard failed.");
		}
		cout << "复位应答:" << retCode.c_str() << endl;
	}

	// 执行单条命令(执行前需要先复位应答)
// 	{
// 		SmartCom::string retCode;
// 		char* apdu = "00820000083132333435363738";
// 		if (0 != CardApdu(reader, apdu, retCode, 1))
// 		{
// 			printf("CardApdu failed.");
// 		}
// 		cout << retCode.c_str() << endl;
// 	}

	// 修改波特率
// 	{
// 		if (0 != ModifyCardBraudRate(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}

	// 查看波特率
// 	{
// 		int braudRate;
// 		if (0 != GetCardBraudRate(reader, braudRate))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 		cout << braudRate << endl;
// 	}

	// 修改电源
// 	{
// 		if (0 != ModifyCardPower(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}
	
	// 擦除存储器
	{
		if (0 != ClearMem(reader)) 
		{
			printf("擦除存储器失败\n");
		}
	}

	// 下载文件(Attention:文件应该放在服务器端的)
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
		SmartCom::string retCode; // 状态返回码
		int result; // 已执行的条数
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

	// 清理客户端资源
	CleanUpClient();
	delete reader; // 释放内存

	return 0;
}