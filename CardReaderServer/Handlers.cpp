//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器的线程实现
//////////////////////////////////////////////////////////////////////////
#include "Handlers.h"
#include "ServerParam.h"
#include "ServerUtils.h"
#include <vector>

using namespace std;

// GUI上控制日志显示的线程
UINT logHandler (LPVOID pParam)
{
	while (TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			CEdit* logWindow = (CEdit*) pParam;
			int len = logWindow->GetWindowTextLength();
			logWindow->SetSel(len,len);
			logWindow->ReplaceSel(Server::getInstance()->log);
			Server::getInstance()->log = ""; // 清空日志
		}
		Sleep(500); // 延迟0.5s
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// 默认的handlers定义 
//////////////////////////////////////////////////////////////////////////

// TODO: 修改handler
UINT defaultServerHandler(LPVOID pParam)
{
	Server* serv = (Server*) pParam;
	
	if ((serv->server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		SimpleLog::error("服务器创建Socket失败");
		return -1;
	}

	struct sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(serv->getPort());
	
	if (bind(serv->server, (struct sockaddr*)&local, sizeof(local)) != 0)
	{
		SimpleLog::error("服务器绑定端口失败");
		return -2;
	}
	
	if (listen(serv->server, 64) != 0)
	{
		SimpleLog::error("服务器监听端口失败");
		return -3;
	}
	
	// 对读卡器的访问控制, 在服务器启动的时候进行初始化设置
	if (serv->readerCount != ServerParam::instance->readerCount) // 当读卡器数量发生变化时
	{
		serv->readerCount = ServerParam::instance->readerCount;
		serv->readerUsage.resize(serv->readerCount);
		for (vector<int>::iterator iter = serv->readerUsage.begin(); iter != serv->readerUsage.end(); ++iter)
		{
			*iter = 0; // 初始化控制列表
		}
	}

	SOCKET client;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);
	SimpleLog::info(CString("服务器启动成功, 端口: ") + i2str(serv->getPort()));
	AfxBeginThread(serv->waitListHandler, NULL); // 启动等待队列线程, 处理等待队列的
	while (true)
	{
		client = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (client == INVALID_SOCKET) // 接受客户端socket失败
		{
			SimpleLog::warn(CString("接收客户端请求失败, 来自") + inet_ntoa(from.sin_addr));
			break;
		}
		SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));

		char buff[512]; // buffer

		// 接收客户端的请求, 首先读取读卡器id
		int size = recv(client, buff, 512, 0);
		buff[size] = '\0';
		
		int cardId = atoi(buff); // 读卡器号
		if (cardId > 0 && cardId <= serv->readerCount) // 判断cardId是否合法
		{
			SimpleLog::info(CString("接收读卡器号: ") + i2str(cardId));
			serv->addToWaitList(cardId, client); // 添加到等待处理队列
			SimpleLog::info(CString("将请求添加到读卡器[") + i2str(cardId) + "]等待队列中...");
		}
		else
		{
			SimpleLog::info(CString("接收读卡器号无效, 读卡器号: ") + i2str(cardId));
			closesocket(client); // 关闭socket
		}
		
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam )
{
	while (true)
	{
		// 进入临界区, 寻找是否有读卡器处在等待状态
		EnterCriticalSection(&(Server::getInstance()->g_cs));
		for (int i = 0; i < Server::getInstance()->readerUsage.size(); ++i) // 寻找未使用的读卡器
		{
			if (0 == Server::getInstance()->readerUsage[i] && !Server::getInstance()->waitList[i].empty())
			{
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)i);
				Server::getInstance()->readerUsage[i] = 1; // 标记读卡器为正在使用
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->g_cs));
		Sleep(100); // 休眠100ms, 根据情况适当修改
	}

	return 0;
}


// TODO: 修改handler, 读取读卡器的数据
UINT defaultClientHandler (LPVOID pParam)
{
	int cardId = ((int) pParam);
	SOCKET client = Server::getInstance()->getSocketByCardId(cardId); // 取出相应读卡器队列中的socket
	char buff[512]; // buffer

	sendData(client, "Ready"); // 告诉客户端已经准备就绪可以操作

	CString operationName;
	int resultCode;
	while(operationName != "quit")
	{
		// 接收客户端的请求
		receiveData(client, buff, 512);
		if ((resultCode= parseCommand(client, cardId, buff, operationName)) == 0)
		{
			SimpleLog::info("[" + operationName + "]操作成功");
		} else {
			SimpleLog::info("[" + operationName + "]操作失败, 错误码: " + i2str(resultCode));
		}
		// 将结果发送到客户端
		sendData(client, resultCode);
	}
	
	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);

	// 将读卡器设置为可用
	EnterCriticalSection(&(Server::getInstance()->g_cs));
	Server::getInstance()->readerUsage[cardId] = 0;  // 操作完成后, 设置为空闲状态
	LeaveCriticalSection(&(Server::getInstance()->g_cs));

	return 0;
}

// 测试用
UINT helloClientHandler (LPVOID pParam)
{
	SOCKET client = (SOCKET) pParam;
	char buff[512]; // buffer
	
 	sprintf(buff, "Hello."); // 测试数据, 仅发送Hello
// 	int size = send(client, buff, strlen(buff), 0);
// 	SimpleLog::info(CString("发送数据: ") + buff);

	sendData(client, buff);
	
	//Sleep(10000);
	shutdown(client, SD_BOTH);
	closesocket(client);
	
	return 0;
}
