#ifndef __ContactManager_H__
#define __ContactManager_H__
#include <WINSOCK2.H>
#include <list>
#include <vector>

#define WORKSTATIONNUM 4 //目前一个条带机上工作站的数目为4
#define CONNECTIONS_NUM 256  //每一种连接方式最多可建立256个连接

//存放用于tcp通信方式所用的参数
struct TcpClientConn{
        char dstIP[32]; //目的ip
		int port;      //目的端口
		int waitSTX2Time; //第一个字符超时
		int normalWaitTime; //中间字符超时
		SOCKET s;    //与目的地址相连的socket
		struct TcpClientConn* next; //指向下个节点
};

//存放用于udp通信方式所用的参数
struct UdpConnection{
	  int localPort;   //绑定的本地端口
	  SOCKET s;      //绑定的本地socket
	  int waitSTX2Time;//第一个字符超时
	  int normalWaitTime;//中间字符超时

	  char dstIP[32];//目的ip
	  int dstPort;
	  int reference;
	  CRITICAL_SECTION cs_rw;
	  UdpConnection(int _localPort,char* dstIP,int dstPort,SOCKET _s,int _waitSTX2Time,int _normalWaitTime);

};

//存放用于com通信方式所用的参数
struct ComConnection{
	int comPort; //com端口
	int waitSTX2Time;//第一个字符超时
	int normalWaitTime;//中间字符超时
	int reference;
	CRITICAL_SECTION cs_initilize;
	CRITICAL_SECTION cs_rw;
	ComConnection();
};

//udpconn manager
struct UdpCommManager{
	char dstIP[32];
	CRITICAL_SECTION cs_workstation;
	int sendingThreadNum;//同时向工作站发送数据的线程数
	std::list<UdpConnection*> udpCommList;
	UdpCommManager(const char* dstIP);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////
//维护连接状态及各种连接参数

class Connections{
public:
	static TcpClientConn* tcpClientConnHead; //tcp连接参数头节点
	static ComConnection* comConnArr;//采用哈希表法存储数据
	static int commType;
	static BOOL udpCommInited;
	static BOOL comCommInited;
	//初始化互斥体
	static HANDLE hUDPInitMutex;   //初始化udp通信互斥对象
	static HANDLE hTCPCLientInitMutex;//初始化tcp通信互斥对象
	static unsigned long lastSendTime;
	static std::vector<UdpCommManager> udpCommManagerVector;

};
//
#endif
