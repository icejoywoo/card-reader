#ifndef _MINGSEN_KEY_
#define _MINGSEN_KEY_

// key��Ϣ
typedef struct _KeyInformation
{
	long last_modify_time; // ����޸�ʱ��
	long count; // ������
	long contract_start_time; // Э�鿪ʼʱ��
	long contract_end_time; // Э�����ʱ��
} KeyInformation, *PKeyInformation; 

#endif