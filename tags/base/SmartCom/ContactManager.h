#ifndef __ContactManager_H__
#define __ContactManager_H__
#include <WINSOCK2.H>

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
	  struct UdpConnection* next; //指向下个节点

	  char dstIP[32];//目的ip
	  int dstPort;
	  UdpConnection(int _localPort,char* dstIP,int dstPort,SOCKET _s,int _waitSTX2Time,int _normalWaitTime,UdpConnection* _next);

};

//存放用于com通信方式所用的参数
struct ComConnection{
	int comPort; //com端口
	int braudRate;//波特率
	int waitSTX2Time;//第一个字符超时
	int normalWaitTime;//中间字符超时
	struct ComConnection* next;//指向下个节点
	ComConnection(int ,int,int,int,ComConnection*);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////
//维护连接状态及各种连接参数

class Connections{
public:
	static TcpClientConn* tcpClientConnHead; //tcp连接参数头节点
	static UdpConnection* udpConnHead;
	static ComConnection* comConnHead;
	static int commType;
	static BOOL udpCommInited;
	static BOOL comCommInited;
	//初始化互斥体
	static HANDLE hUDPInitMutex;   //初始化udp通信互斥对象
	static HANDLE hCOMInitMutex;   //初始化com通信互斥对象
	static HANDLE hTCPCLientInitMutex;//初始化tcp通信互斥对象
	static HANDLE timeIntervalMutex;
	static UINT lastSendTime;
};
//
#endif
