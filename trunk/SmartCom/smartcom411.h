#ifndef _SMARTCOM41_H_
#define _SMARTCOM41_H_
#define STX1 0xC0
#define STX2 0xC2
#define ETX1 0xC1
#define ETX2 0xC3

#define SMART_DATA_LENGTH_TOO_LARGE		-1 //-1:���ݳ��Ȳ���ֵ̫�����ڸ�ֵ
#define	SMART_RCEIVE_DATA_ERRORE			-2 //�������ݴ�
#define	SMART_SEND_DATA_ERROR				-3 //�������ݴ�
#define	SMART_RECEIVE_DATA_TIMEOUT		-4 //�������ݳ�ʱ
#define SMART_ADDRESS_NOT_MATCH			-5 //���ص�ַ��ƥ��
#define SMART_TERMINAL_NO_RESPONSE		-6 //�ն��޷�Ӧ
#define	SMART_ESTABLISH_CONNECT_TIMEOUT	-7 //����SOCKET���ӳ�ʱ
#define	SMART_CLOSE_SOCKET_ERROR			-8 //�ر�SOCKET��
#define SMART_DATA_CHECK_ERROR			-9 //����У���
#define	SMART_RECEIVE_DATA_PACKET_ERROR	-10 //�����������ݰ���ʽ��
#define	SMART_NOT_FIND_WINSOCK_DLL		-11 //û���ҵ����õ�WINSOCK��̬��
#define	SMART_CLOSE_WINSOCK_ENV_ERROR		-12 //�ر�WINSOCK��������
#define	SMART_IP_ADDRESS_ERROR			-13 //�����IP��ַ
#define	SMART_INITIAL_SOCKET_ERROR		-14 //��ʼ��SOCKET��
#define	SMART_CONNECT_CLOSED				-15 //WINSOCK�����ѹر�
#define	SMART_CONNECT_BROKEN				-16 //WINSOCK���Ӷ��ѻ����·�ѹر�




/************ calc_crc16 ���*************/
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

extern int  GetOneLocalSocket(unsigned int * socket,int srcPort);  //���һ������������SOCK,���ڷ��ͺͽ���UDP��

extern int  SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen);

extern int  RecvUDPData(unsigned int Sock,unsigned int WaitForSTX2Time,unsigned int NormalWaitTime,unsigned char *PacketBuffer,int len);

extern int  CloseUDPSocketEnv(unsigned int sock);

extern int  CloseUDPSocket(unsigned int sock);


#endif