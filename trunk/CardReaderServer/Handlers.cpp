//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器的线程实现
//////////////////////////////////////////////////////////////////////////
#include "Handlers.h"
#include "ServerParam.h"
#include "ServerUtils.h"
#include "CustomMessage.h"
#include <vector>
#include <algorithm>

using namespace std;

// GUI上控制日志显示的线程, 大概没0.5s更新一次日志显示
UINT logHandler (LPVOID pParam)
{
	while (Server::getInstance()->status == TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			::PostMessage(ServerParam::instance->mainFrame, LOG_UPDATE_MSG, 1, 1);
		}
		Sleep(100); // 延迟0.1s
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

	// TODO: 初始化读卡器(用udp测试的时候使用, 现在已经转用udp)
	if (InitUDPComm() == -1) {
		AfxMessageBox("与卡片读写器的通信初始化失败");
		SimpleLog::error("与卡片读写器的通信初始化失败");
		return INIT_FAILED; // 与卡片读写器的通信初始化失败
	}
	
	// 对读卡器的访问控制, 在服务器启动的时候进行初始化设置
	for (set<int>::iterator iter = ServerParam::instance->readerIdSet.begin(); 
			iter != ServerParam::instance->readerIdSet.end(); ++iter) // 遍历当前读卡器id的集合
	{
		serv->readerUsage[*iter] = 0; // 初始化控制列表, 都未使用
	}

	SOCKET clientSocket;
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	int fromlen = sizeof(from);

	char log[512]; // 存放日志的临时字符串

	sprintf(log, "服务器启动成功, 端口: %d", serv->getPort());
	SimpleLog::info(log);

	CWinThread* waitListThread = AfxBeginThread(serv->waitListHandler, NULL); // 启动等待队列线程, 处理等待队列的
	waitListThread->m_bAutoDelete = TRUE;
	CWinThread* timeoutListThread = AfxBeginThread(serv->timeoutListHandler, NULL); // 启动延时处理线程, 手动调试的时候可以关闭
	waitListThread->m_bAutoDelete = TRUE;

	while (Server::getInstance()->status == TRUE)
	{
		clientSocket = accept(serv->server, (struct sockaddr*) &from, &fromlen);
		if (clientSocket == INVALID_SOCKET) // 接受客户端socket失败, 是在关闭服务器的时候
		{
			sprintf(log, "接收客户端请求失败, 来自: %s", inet_ntoa(from.sin_addr));
			SimpleLog::warn(log);

			break;
		}

		sprintf(log, "接收客户端请求, 来自: %s:%d", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
		SimpleLog::info(log);
		

		// 接收客户端的请求, 首先读取读卡器id
		int readerId; // 读卡器号
		receiveData(clientSocket, readerId);
		if (ServerParam::instance->readerIdSet.count(readerId) > 0 )
		{
			sprintf(log, "接收读卡器com号: [%d]", readerId);
			SimpleLog::info(log);
			
			sendData(clientSocket, "id_ok");
		} else {
			sprintf(log, "接收读卡器com号: [%d], 读卡器不存在", readerId);
			SimpleLog::error(log);		
			
			sendData(clientSocket, "id_wrong");
			closesocket(clientSocket);
			continue;
		}
		

		// 读取延时
		int timeout; // 读卡器延时
		receiveData(clientSocket, timeout);

		sprintf(log, "[读卡器 %d]的延时为: %d", readerId, timeout);
		SimpleLog::info(log);

		sendData(clientSocket, "timeout_ok");
		Client* client = new Client(clientSocket); // new一个client, 在处理完client后delete
		client->setReaderId(readerId);
		client->setTimeout(timeout);
		EnterCriticalSection(&(Server::getInstance()->readerUsage_cs));
		Server::getInstance()->addToWaitList(client);
		LeaveCriticalSection(&(Server::getInstance()->readerUsage_cs));

		sprintf(log, "将请求添加到[读卡器 %d]的等待队列中...", readerId);
		SimpleLog::info(log);
	}
	return 0;
}

UINT defaultWaitListHandler (LPVOID pParam ) 
{
	while (Server::getInstance()->status == TRUE)
	{
		// 进入临界区, 寻找是否有读卡器处在等待状态
		EnterCriticalSection(&(Server::getInstance()->readerUsage_cs));
		for (map<int,int>::iterator iter = Server::getInstance()->readerUsage.begin();
			iter != Server::getInstance()->readerUsage.end(); ++iter) // 寻找未使用的读卡器
		{
			if (0 == iter->second && !Server::getInstance()->waitList[iter->first].empty())
			{
				Server::getInstance()->getClientByReaderId(iter->first)->updateTimeout();
				AfxBeginThread(Server::getInstance()->clientHandler, (LPVOID)iter->first)->m_bAutoDelete = TRUE;
				Server::getInstance()->readerUsage[iter->first] = 1; // 标记读卡器为正在使用
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->readerUsage_cs));
		Sleep(100); // 休眠100ms, 根据情况适当修改
	}
	return 0;
}

UINT defaultTimeoutListHandler (LPVOID pParam )
{
	char log[512];
	while (Server::getInstance()->status == TRUE) // 读卡器的延时队列只针对当前访问读卡器的客户端
	{
		// 遍历所有客户端
// outter:
// 		for (map<int, list<Client*> >::iterator miter = Server::getInstance()->waitList.begin();
// 			miter != Server::getInstance()->waitList.end() ; ++miter)
// 		{
// 			list<Client*> l = miter->second;
// 
// 			for (list<Client*>::iterator liter = l.begin(); liter != l.begin(); ++liter)
// 			{
// 				if ((*liter)->isOvertime()) // 客户端如果超时, 就直接关闭其socket
// 				{
// 					(*liter)->release();
// 					Server::getInstance()->waitList[miter->first].remove((*liter)); // 删除等待列表中的超时的客户端, 在这里添加后可能会内存泄漏
// 					delete (*liter); // 删除内存
// 					sprintf(log, "[读卡器 %d]的客户端[%d]超时, 从等待队列中删除", (*liter)->getReaderId(), (*liter)->getSocket());
// 					SimpleLog::error(log);
// 					goto outter;// 删除元素后, 跳出所有循环, iterator需要更新
// 				}
// 			}
// 		}
		EnterCriticalSection(&(Server::getInstance()->clients_cs));
	
		for (list<Client*>::iterator iter = Server::getInstance()->clients.begin();
			iter != Server::getInstance()->clients.end(); ++iter)
		{
			if((*iter)->isOvertime())
			{
				char name[50];
				(*iter)->getName(name);
				sprintf(log, "[读卡器 %d]的客户端[%s]超时, 即刻删除", (*iter)->getReaderId(), name);
				SimpleLog::warn(log);
				(*iter)->release();
				Server::getInstance()->clients.remove(*iter);
				break;
			}
		}
		LeaveCriticalSection(&(Server::getInstance()->clients_cs));	
		Sleep(10); // 休眠100ms, 根据情况适当修改
	}
	
	return 0;
}

// TODO: 修改handler, 读取读卡器的数据
UINT defaultClientHandler (LPVOID pParam)
{
	int readerId = ((int) pParam);
	Client* client = Server::getInstance()->getClientByReaderId(readerId); // 取出相应读卡器队列中的socket

	char buff[512]; // buffer
	char log[512];

	if (client->isAvailable()) // 如果客户端有效就发送
	{
		client->sendData("Ready"); // 告诉客户端已经准备就绪可以操作
		sprintf(log, "[读卡器 %d]开始处理请求...", client->getReaderId());
		SimpleLog::info(log);
	} else {

	}
	
	client->updateTimeout();

	string operationName;
	int resultCode;
	while(operationName.compare("quit") != 0)
	{
		// 接收客户端的请求
		if (!client->isAvailable() || client->receiveData(buff, 512) == -1) // 接收数据错误即刻关闭
		{
			break;
		}
		client->updateTimeout();
		if ((resultCode= parseCommand(client, readerId, buff, operationName)) >= 0)
		{
			if (Server::getInstance()->status == TRUE)
			{
				sprintf(log, "[读卡器 %d][%s]操作成功", readerId, operationName.c_str());
				SimpleLog::info(log);
			}
		} else {
			sprintf(log, "[读卡器 %d][%s]操作失败, 错误码: %d", readerId, operationName.c_str(), resultCode);
			SimpleLog::error(log);
		}
		client->updateTimeout();
		// 将结果发送到客户端
		if (!client->isAvailable() || client->sendData(resultCode) == -1) // 发送数据出错即刻关闭
		{
			break;
		}
	}

	// 释放读卡器
	Server::getInstance()->releaseReader(readerId);
	if (client->isAvailable()) 
	{
		sprintf(log, "释放[读卡器 %d]", readerId);
		SimpleLog::info(log);
	}
	client->release();
	delete client; // 不要的指针删掉

	return 0;
}
