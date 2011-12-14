#ifndef _CUSTOM_ERROR_CODE_H_
#define _CUSTOM_ERROR_CODE_H_

#define COMMAND_NOT_FOUND (-100) // ����δ�ҵ�
#define INIT_FAILED (-101) // �뿨Ƭ��д����ͨ�ų�ʼ��ʧ��
#define CLOSE_FAILED (-102) // �ر�ͨ��ʧ��

#define READER_ALREADY_USED (-103) // �������Ѿ���ʹ����
#define IN_WAIT_LIST (-104) //���뵽�ȴ�����, �ȴ���

#define CONNECT_FAILED (-105) // ���ӷ�����ʧ��
#define SETSOCKOPT_FAILED (-106) // ����socket��ʱʧ��
#define SEND_ERROR (-107) // socket�������ݴ���
#define RECV_ERROR (-108) // socket�������ݴ���

#define GET_COMMUNICATOR_FAILED (-109) // ��ȡͨ����ʧ��

#endif