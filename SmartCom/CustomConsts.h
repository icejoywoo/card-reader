#ifndef _CUSTOMCONSTS_H_
#define _CUSTOMCONSTS_H_

//自定义消息
#define WM_USER 0x0400
#define WM_USER_COMM_IN_PROGRESS (WM_USER + 1)
#define WM_USER_COMM_DONE (WM_USER + 2)
#define WM_USER_COMM_NOW (WM_USER + 3)
#define WM_DLG_CREATED  (WM_USER + 4)

//通信方式
#define  COMM_COM     0      //串口方式
#define  COMM_MODEM   1      //Modem方式      
#define  COMM_TCPCLIENT     2      //TCP CLIENT方式
#define  COMM_UDP     3      //UDP方式
#define  COMM_TCPSERVER     4      //TCP SERVER方式
#define  NOT_CONNECT   5         //没有连接
#define  COMM_TCP     6

//消息内分类
#define CREATE_SOCKET_FAILED   1
#define CREATE_SOCKET_SUCCEED  2
#define SEND_DATA_RESULT  3
#define REV_DATA_RESULT   4
#define LOAD_PROC_RESULT  5
#define LOAD_PROC_MAX     6
#define LOAD_PROC_IN_PROGRESS  7
#define MANUAL_REV_RESULT 8
#define TASK_COMPLETE 9

//通信用途
#define COMM_GENERAL       0
#define COMM_LOAD_PROGRAM  1
#define COMM_MANUAL_REV    2 

//应用层与内核驱动通信结构
struct KIOCTRL{
	HANDLE hFile;
	HANDLE hDevice;
	UCHAR flag;
	UCHAR macNo;
	ULONG timeout;
};

struct KIOCTRL_APDU{
	KIOCTRL kioctrl;
    UCHAR* apduStr;
	UCHAR card;
};

struct KIOCTRLEX{
	KIOCTRL kioctrl;
	ULONG   timeout_count;//线程需要等待的时间单位计数（每单位10毫秒）
	LARGE_INTEGER sleep_time;//线程每次睡眠时间
};

#define  DEVICE_NAME  "SmartComProxyDevice"

#ifdef _DEBUG
   #define  SCPrint(_x_)  printf _x_ 
#else
   #define  SCPrint(_x_)  
#endif

#endif//_CustomConsts_ end