                -----------------------------------------------------------------------------------------------------------------
                    �깷��װ Windows 2K (32 λ)/Windows XP (32/x64 λ)/Windows Server 2003 (32/x64 λ)/Windows Vista (32/x64 λ)
                    /Windows 7 (32/x64 λ)/Windows Server 2008 (32/x64 λ)/Windows 2008 R2 (x64 λ)������װж�س���ʹ��˵��
                -----------------------------------------------------------------------------------------------------------------
                                            ��Ȩ���� (C)  2010  �����ͣ���������Ϣ�������޹�˾

 
  ���ܺ�� Windows Ӧ�ó����� Windows 2K (32 λ)/Windows XP (32/x64 λ)/Windows Server 2003 (32/x64 λ)
  /Windows Vista (32/x64 λ)/Windows 7 (32/x64 λ)/Windows Server 2008 (32/x64 λ)/Windows 2008 R2 (x64 λ)
  ������ʱ����Ҫ��װӲ�������豸��������

  �����ṩ�˺깷������װ��̬��GrandDogSetup.dll���ö�̬���ṩ��������װ��ж���Լ���������汾�Ľӿڡ�
  ��ж�ع�����ʱ��������Ѿ�������Ӳ��������ε�������ж�ع�������
 	
==========
�ļ��嵥
==========

  readme-chn.txt     			���ĵ�
  DogInst.exe				������װִ�г���
  GrandDogSetup.dll	 		������װ��̬��
  Delphi<dir> 				����������װ��̬���Delphi���ӳ���
  VB<dir> 				����������װ��̬���VB���ӳ���
  VC<dir> 				����������װ��̬���VC���ӳ���
==================
GrandDogSetup.dll ���
==================

GrandDogSetup.dll��WIN32�¶�̬���ӿ�,�����̿���������ܵ������װ������ʹ�����½ӿں�����
  
  (1)������װ�ĺ����ӿ�Install����������:
  unsigned long PASCAL Install(int iFlag)��
  ������
  	iFlag = 1 ֻ��װUSB������
	iFlag = 2 ֻ��װ���ڹ�����(���汾��֧��)
	iFlag = 3 ��װ���ڹ�������USB������
  ����ֵ��
  ������гɹ��򷵻�0,���򷵻ش���ֵ��

  (2)����ж�صĺ����ӿ�Uninstall����������:
  unsigned long PASCAL Uninstall(int iFlag)��
  ������
  	iFlag = 1 ֻж��USB������
	iFlag = 2 ֻж�ز��ڹ����������汾��֧�֣�
	iFlag = 3 ж�ز��ڹ�������USB������
  ����ֵ��
  ������гɹ��򷵻�0,���򷵻ش���ֵ��
  (3)��������汾�Ľӿ�CheckVersion����������:
  unsigned long PASCAL CheckVersion(BOOL bShowMessageBox,
					int* piUsbVerStatus,
					int* piParVerStatus)
  ������
	bShowMessageBox = TRUE 	��ʾ��ȡ�汾�ĵ�������
	bShowMessageBox = FALSE ����ʾ��ȡ�汾�ĵ�������
	piUsbVerStatus	�洢USB������״̬��ָ��
	piParVerStatus	�洢���ڹ�����״̬��ָ�루Ϊ�����汾������

  ����ֵ��
  ������гɹ��򷵻�0,���򷵻ش���ֵ��
  ������гɹ���*piUsbVerStatus=0 ������û�а�װusb������
		*piUsbVerStatus=1 ��������װ�������汾�����װ�������汾һ��
 		*piUsbVerStatus=2 ��������װ�������汾�ȴ���װ�������汾��
		*piUsbVerStatus=3 ��������װ�������汾�ȴ���װ�������汾��

		
  ������μ����ӳ����Դ���롣

=========
 ������
=========

E_RC_MAPPING_SYSTEM_LIBRARY_FUNCTION (0xA8162001)	ӳ��ϵͳ�⺯������
E_RC_LOAD_SYSTEM_LIBRARY	     (0xA8162002)	����ϵͳ�����
E_RC_FIND_USB_DOG_DEVICE	     (0xA8162003)	û�з���USB���豸
E_RC_UPDATE_USB_DOG		     (0xA8162004)	����usb������ʧ��
E_RC_OPERATING_SYSTEM		     (0xA8162005)	��֧�ֵĲ���ϵͳ
E_RC_NO_PARALLEL_PORT_OR_DISABLED    (0xA8162006)	û�в��ڻ򲢿ڱ�����
E_RC_REMOVE_FILE_FAILED    	     (0xA8162007)	ɾ���ļ�ʧ��
E_RC_OPEN_DRIVER_SERVICE_FAILED	     (0xA8162008)	�򿪷���ʧ��
E_RC_START_DRIVER_SERVICE_FAILED     (0xA8162009)	��������ʧ��
E_RC_COPY_FILE_FAILED		     (0xA816200A)	�����ļ�ʧ��
E_RC_OPERATE_REGISTRY_FAILED         (0xA816200B)	����ע���ʧ��
E_RC_NOT_ADMINISTRATOR               (0xA816200C)	���ǹ���Ա���


========
ע������
========
 1. �ڰ�װ��ж�غ깷����ǰ����ر�ʹ�ú깷��Ӧ�ó���


---------------------------------------------------------------------------------------------------
�������Ǳ�������������չ���޹�˾��ע���̱꣬����Ȩ�����ͣ���������Ϣ�������޹�˾��
----------------------------------------------------------------------------------------------------