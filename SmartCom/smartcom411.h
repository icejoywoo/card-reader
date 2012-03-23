#ifndef _SMARTCOM41_H_
#define _SMARTCOM41_H_
#define STX1 0xC0
#define STX2 0xC2
#define ETX1 0xC1
#define ETX2 0xC3

#define SMART_DATA_LENGTH_TOO_LARGE		-1 //-1:数据长度参数值太大或等于负值
#define	SMART_RCEIVE_DATA_ERRORE			-2 //接收数据错
#define	SMART_SEND_DATA_ERROR				-3 //发送数据错
#define	SMART_RECEIVE_DATA_TIMEOUT		-4 //接收数据超时
#define SMART_ADDRESS_NOT_MATCH			-5 //返回地址不匹配
#define SMART_TERMINAL_NO_RESPONSE		-6 //终端无反应
#define	SMART_ESTABLISH_CONNECT_TIMEOUT	-7 //建立SOCKET连接超时
#define	SMART_CLOSE_SOCKET_ERROR			-8 //关闭SOCKET错
#define SMART_DATA_CHECK_ERROR			-9 //数据校验错
#define	SMART_RECEIVE_DATA_PACKET_ERROR	-10 //接收数据数据包格式错
#define	SMART_NOT_FIND_WINSOCK_DLL		-11 //没有找到可用的WINSOCK动态库
#define	SMART_CLOSE_WINSOCK_ENV_ERROR		-12 //关闭WINSOCK环境出错
#define	SMART_IP_ADDRESS_ERROR			-13 //错误的IP地址
#define	SMART_INITIAL_SOCKET_ERROR		-14 //初始化SOCKET错
#define	SMART_CONNECT_CLOSED				-15 //WINSOCK连接已关闭
#define	SMART_CONNECT_BROKEN				-16 //WINSOCK连接断裂或虚电路已关闭




/************ calc_crc16 快表法*************/
extern void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab);

extern unsigned short  calc_crc16(unsigned char len,unsigned char *in);

extern void  SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);

extern void  SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);

extern int  IniCom(int ComPort,int BaudRate,int waitForSTX2Time,int normalWaitTime);

extern int  CloseCom(int ComPort);

extern int	 PrepareBytes(int Machine,unsigned char Commandbyte,unsigned char *SourceBuffer,int *len,unsigned char *Targetbuffer);

extern int	 SendBytes(int ComPort,unsigned char *PacketBuffer,int PacketLen);

extern int  ModemDial(int ComPort,unsigned char* DialString,int length);

extern int  CheckModemLink(int ComPort,int MaxWaitTime);

extern int	 ReceiveBytes (int ComPort,unsigned int waitforstx2,unsigned int _WaitTime,unsigned char *RecBuffer);

extern int	 CheckBytes (unsigned char *SourceBuffer);

extern int  StartWinSocketEnv();

extern int  CloseWinSocketEnv();

extern int  EstablishConnect(const char * IP_Address,int IP_Port,int TimeOut,unsigned int *Sock);

extern int  CloseConnect(unsigned int Sock);

extern int  SendData(unsigned int Sock,unsigned char *PacketBuffer,int PacketLen);

extern int  ReceiveData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer);
	
extern int  DirectReceiveData(unsigned int nCommPort,unsigned char *PacketBuffer,int nCommType);

extern int  BindPort(const char* IP_Address,int IP_Port,unsigned int *Sock);

extern int  GetOneLocalSocket(unsigned int * socket,int srcPort);  //获得一个本地主机的SOCK,用于发送和接受UDP包

extern int  SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen);

extern int  RecvUDPData(unsigned int Sock,unsigned int WaitForSTX2Time,unsigned int NormalWaitTime,unsigned char *PacketBuffer,int len);

extern int  CloseUDPSocketEnv(unsigned int sock);

extern int  CloseUDPSocket(unsigned int sock);


#endif