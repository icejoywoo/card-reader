#ifndef __Communicator_H__
#define __Communicator_H__

#ifdef COMMUNICATOR_EXPORTS_MACRO
#define COMMUNICATOR_API __declspec(dllexport)
#else
#define COMMUNICATOR_API __declspec(dllimport)
#endif
//与连接相关参数
struct UdpConnection;
struct TcpClientConn;
struct ComConnection;
//与连接相关参数
struct Communicator{
	  int m_nCommtype;     //当前选择通信的类型
	  int csIndex;        //当前通信所使用的临界区的序号
	  UdpConnection* udpConn;//指向udp通信使用的参数结构
	  TcpClientConn* tcpClientConn;//
	  ComConnection* comConn;
	  unsigned long waitTimeForGetComm;

	COMMUNICATOR_API Communicator();
};

#endif


