#ifndef __ContactManager_H__
#define __ContactManager_H__
#include <WINSOCK2.H>

//�������tcpͨ�ŷ�ʽ���õĲ���
struct TcpClientConn{
        char dstIP[32]; //Ŀ��ip
		int port;      //Ŀ�Ķ˿�
		int waitSTX2Time; //��һ���ַ���ʱ
		int normalWaitTime; //�м��ַ���ʱ
		SOCKET s;    //��Ŀ�ĵ�ַ������socket
		struct TcpClientConn* next; //ָ���¸��ڵ�
};

//�������udpͨ�ŷ�ʽ���õĲ���
struct UdpConnection{
	  int localPort;   //�󶨵ı��ض˿�
	  SOCKET s;      //�󶨵ı���socket
	  int waitSTX2Time;//��һ���ַ���ʱ
	  int normalWaitTime;//�м��ַ���ʱ
	  struct UdpConnection* next; //ָ���¸��ڵ�

	  char dstIP[32];//Ŀ��ip
	  int dstPort;
	  UdpConnection(int _localPort,char* dstIP,int dstPort,SOCKET _s,int _waitSTX2Time,int _normalWaitTime,UdpConnection* _next);

};

//�������comͨ�ŷ�ʽ���õĲ���
struct ComConnection{
	int comPort; //com�˿�
	int braudRate;//������
	int waitSTX2Time;//��һ���ַ���ʱ
	int normalWaitTime;//�м��ַ���ʱ
	struct ComConnection* next;//ָ���¸��ڵ�
	ComConnection(int ,int,int,int,ComConnection*);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////
//ά������״̬���������Ӳ���

class Connections{
public:
	static TcpClientConn* tcpClientConnHead; //tcp���Ӳ���ͷ�ڵ�
	static UdpConnection* udpConnHead;
	static ComConnection* comConnHead;
	static int commType;
	static BOOL udpCommInited;
	static BOOL comCommInited;
	//��ʼ��������
	static HANDLE hUDPInitMutex;   //��ʼ��udpͨ�Ż������
	static HANDLE hCOMInitMutex;   //��ʼ��comͨ�Ż������
	static HANDLE hTCPCLientInitMutex;//��ʼ��tcpͨ�Ż������
	static HANDLE timeIntervalMutex;
	static UINT lastSendTime;
};
//
#endif
