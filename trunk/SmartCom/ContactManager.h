#ifndef __ContactManager_H__
#define __ContactManager_H__
#include <WINSOCK2.H>
#include <list>
#include <vector>

#define WORKSTATIONNUM 4 //Ŀǰһ���������Ϲ���վ����ĿΪ4
#define CONNECTIONS_NUM 256  //ÿһ�����ӷ�ʽ���ɽ���256������

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

	  char dstIP[32];//Ŀ��ip
	  int dstPort;
	  int reference;
	  CRITICAL_SECTION cs_rw;
	  UdpConnection(int _localPort,char* dstIP,int dstPort,SOCKET _s,int _waitSTX2Time,int _normalWaitTime);

};

//�������comͨ�ŷ�ʽ���õĲ���
struct ComConnection{
	int comPort; //com�˿�
	int waitSTX2Time;//��һ���ַ���ʱ
	int normalWaitTime;//�м��ַ���ʱ
	int reference;
	CRITICAL_SECTION cs_initilize;
	CRITICAL_SECTION cs_rw;
	ComConnection();
};

//udpconn manager
struct UdpCommManager{
	char dstIP[32];
	CRITICAL_SECTION cs_workstation;
	int sendingThreadNum;//ͬʱ����վ�������ݵ��߳���
	std::list<UdpConnection*> udpCommList;
	UdpCommManager(const char* dstIP);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////
//ά������״̬���������Ӳ���

class Connections{
public:
	static TcpClientConn* tcpClientConnHead; //tcp���Ӳ���ͷ�ڵ�
	static ComConnection* comConnArr;//���ù�ϣ���洢����
	static int commType;
	static BOOL udpCommInited;
	static BOOL comCommInited;
	//��ʼ��������
	static HANDLE hUDPInitMutex;   //��ʼ��udpͨ�Ż������
	static HANDLE hTCPCLientInitMutex;//��ʼ��tcpͨ�Ż������
	static unsigned long lastSendTime;
	static std::vector<UdpCommManager> udpCommManagerVector;

};
//
#endif
