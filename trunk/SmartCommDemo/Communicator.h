#ifndef __Communicator_H__
#define __Communicator_H__

#ifdef COMMUNICATOR_EXPORTS_MACRO
#define COMMUNICATOR_API __declspec(dllexport)
#else
#define COMMUNICATOR_API __declspec(dllimport)
#endif
//��������ز���
struct UdpConnection;
struct TcpClientConn;
struct ComConnection;
//��������ز���
struct Communicator{
	  int m_nCommtype;     //��ǰѡ��ͨ�ŵ�����
	  int csIndex;        //��ǰͨ����ʹ�õ��ٽ��������
	  UdpConnection* udpConn;//ָ��udpͨ��ʹ�õĲ����ṹ
	  TcpClientConn* tcpClientConn;//
	  ComConnection* comConn;
	  unsigned long waitTimeForGetComm;

	COMMUNICATOR_API Communicator();
};

#endif


