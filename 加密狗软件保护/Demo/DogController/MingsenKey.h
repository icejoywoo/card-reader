#ifndef _MINGSEN_KEY_
#define _MINGSEN_KEY_

// key信息
typedef struct _KeyInformation
{
	long last_modify_time; // 最后修改时间
	long count; // 计数器
	long contract_start_time; // 协议开始时间
	long contract_end_time; // 协议结束时间
} KeyInformation, *PKeyInformation; 

#endif