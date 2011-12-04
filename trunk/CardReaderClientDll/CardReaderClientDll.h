
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CARDREADERCLIENTDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CARDREADERCLIENTDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CARDREADERCLIENTDLL_EXPORTS
#define CARDREADERCLIENTDLL_API __declspec(dllexport)
#else
#define CARDREADERCLIENTDLL_API __declspec(dllimport)
#endif

#include "SmartComString.h"

// This class is exported from the CardReaderClientDll.dll
// class CARDREADERCLIENTDLL_API CCardReaderClientDll {
// public:
// 	CCardReaderClientDll(void);
// 	// TODO: add your methods here.
// };
// 
// extern CARDREADERCLIENTDLL_API int nCardReaderClientDll;
// 
// CARDREADERCLIENTDLL_API int fnCardReaderClientDll(void);

/**
 * @brief ��ʼ���ͻ��˵ķ���������
 * @param
 *	serverIp	������ip
 *	serverPort	�������˿ں�
 * @return 
 *	�ɹ�����0
 */
CARDREADERCLIENTDLL_API int initClient(char* serverIp, int serverPort);

/**
 * @brief ��ȡ������
 * @param
 *	cardId ��������
 *	userId �û���ʶ��
 * @return  
 *	0: �ɹ�
 */
CARDREADERCLIENTDLL_API int getReader(int cardId, char* userId);

/**
 * @brief �ͷŶ�����
 * @param
 *	cardId ��������
 * @return  
 *	0: �ɹ�
 */
CARDREADERCLIENTDLL_API int releaseReader(int cardId);

/**
 * @brief ��ȡ�ն��豸id�źͻ���
 * @param 
 *	devID		���7�ֽ�id��
 *	devIDBufLen devID����ĳ���
 *	macNo		1�ֽڻ���
 * @return 
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetDevIDAndMacNo(char* devID, int devIDBufLen, int& macNo);

/**
 * @brief ͨ���ն��豸ID�Ÿ��ն��豸���û���
 * @param
 *	devID ���7���ֽڵ��豸ID
 *	macNo Ҫ���õĻ���
 * @return
 *	 0: ���óɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int SetMacNoByDevID(const char* devID,int macNo);


/**
 * @brief ��ȡ����汾���ն�����
 * @param
 *	appVersion	����汾
 *	verLen		���appVersion�Ļ��峤��
 *	devType		�ն�����
 *	typelen		����ն����͵Ļ��峤��
 *	macNo		����
 * @return
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetAppVerAndDevType(char* appVersion,int Verlen,char* devType,int typeLen, int MacNo);

/**
 * @brief ��λ�ն��豸
 * @param
 *	macNo ����
 * @return
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int ResetDev(int macNo);

/** 
 * @brief ��ȡ�����ӿ�оƬID��
 * @param
 *	chipID		�ӿ�оƬID
 *	chipIDLen	��Žӿ�оƬID�Ļ��泤��
 *	macNo		����
 * @return 
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetChipID(char* chipID, int chipIDLen,int macNo);

/**
 * @brief ���A�����󿨣�����B����SIM�������Ƿ��п�
 * @param
 *	comm	����ͨ�ŵ�ͨ����
 *	macNO	����
 *	cardA	1,A�����п���0��A�����޿�
 *	cardB	1,B�����п���0��B�����޿�
 * @return 
 *	 0: ���ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ���ʧ��
 */
CARDREADERCLIENTDLL_API int IsCardReady(int& cardA,int& cardB,int macNo);

/**
 * @brief ��Ƭ��λӦ��
 * @param
 *	card		1:A����2��B��,Ĭ��ѡ��A��
 *	macNO		���ţ�Ĭ��255
 *	retCode		��λ����ķ���ֵ
 *		retCode="F9"�������޿�
 *		retCode="FD"������ʶ��
 *	����ֵ��
 *	0��ͨ�ųɹ�
 *	-1��ͨ�ų�ʱ����
 *	-2��ͨ������Ч  
 *	-3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int ResetCard(SmartCom::string& retCode,int card=1,int macNo=255);

/**
 * @brief ��Ƭ����-APDU
 * @param
 *	apdu		ʮ�������ַ�����ʾ��apdu����
 *	card		1:A����2��B��,Ĭ��ѡ��A��
 *	macNO		���ţ�Ĭ��255
 *	retCode		ִ��apduָ��ķ���ֵ
 *		retCode="F9"�������޿�
 *		retCode="FD"������ʶ��
 *		retCode="F2"����Ч7816�����
 *		retCode="F0"��û���ȸ��������ϵ縴λ
 * @return
 *	 0: ͨ�ųɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч 
 *	-3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int CardApdu(SmartCom::string& retCode,int card=1,int macNo=255);

/**
 * @brief ��Ƭ�µ�
 * @param
 *	macNO:���ţ�Ĭ��255
 * @return
 *	 0: �µ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �µ�ʧ��
 */
CARDREADERCLIENTDLL_API int ShutdownCard(int macNo=255);

/**
 * @brief �޸Ŀ�ͨ�Ų�����
 * @param
 *	braudRate	Ҫ�޸ĵĲ����ʣ�ֻ��ѡ����ֵ��115200��57600��38400��28800��23040��19200��14400��12800��9600
 *	macNO		���ţ�Ĭ��255
 * @return
 *	 0: �޸ĳɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �޸�ʧ��
 */
CARDREADERCLIENTDLL_API int ModifyCardBraudRate(int braudRate,int macNo=255);

/**
 * @brief ����ͨ�Ų�����
 * @param
 *	comm		����ͨ�ŵ�ͨ����
 *	macNO		���ţ�Ĭ��255
 *	braudRate	���ڲ���, ��ǰ����ͨ�Ų�����
 * @return
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetCardBraudRate(int& braudRate,int macNo=255);

/**
 * @brief �޸Ŀ�Ƭ��Դ
 * @param
 *	power	��Դ��power=1: 5v��power=2: 3v��power=3: 1.8v
 *	card	1:A����2��B��,Ĭ��ѡ��A��
 *	macNO	���ţ�Ĭ��255
 * @return
 *	 0: �޸ĳɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �޸�ʧ��
 */
CARDREADERCLIENTDLL_API int ModifyCardPower(int power,int card=1,int macNo=255);

/**
 * @brief ����ִ��������APDU����
 * @param
 *	comm	����ͨ�ŵ�ͨ����  
 *	card	ѡ��ִ�еĿ���card=1ΪA����2ΪB����Ĭ��A��
 *	cmdNum	Ҫִ�е�ָ������
 *	macNO	���ţ�Ĭ��255
 * @return
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int  ExcuteMulAPDU(int cmdNum,int card=1,int macNo=255);

/**
 * @brief ������������ƽű��ļ�
 * @param
 *	comm		����ͨ�ŵ�ͨ����
 *	bytes		Ҫ��ȡ���ֽ���
 *	macNO		���ţ�Ĭ��255 
 *	offset		��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
 *	strData		���ڲ���, ��ȡ��ת����ʮ�������ַ���������
 * @return
 *	  0: ��ȡ�ɹ�
 *	 -1: ͨ�ų�ʱ����
 *	 -2: ͨ������Ч
 *	 -3: ���ŷ�Χ����
 *	 -4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetScriptData(int offset,unsigned char bytes,SmartCom::string& strData,int macNo=255);

/**
 * @brief �����ļ�
 * @param
 *	flag		flag=1,�����������ļ���flag=2����������ͷ�ļ�
 *	fileName	�ļ���
 *	macNO		���ţ�Ĭ��255 
 * @return
 *	 0: ���سɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч 
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 *	-5: �ļ���ʧ��
 */
CARDREADERCLIENTDLL_API int DownloadFile(int flag,const char* fileName,int macNo=255);

/**
 * @brief ��ѯִ��������APDU���
 * @param
 *	macNO		���ţ�Ĭ��255 
 *	retCode		���ڲ���, ���һ��ָ��ķ���ֵ 
 *		retCode="F1": δѡ�������޿��򿨸�λʧ��(����ʧЧ)��APDU��Ӧ��ʱ������Ч��APDU����ȴ���
 * @return
 *	>=0: �������Ѿ�ִ�е���������
 *	 -1: ͨ�ų�ʱ����
 *	 -2: ͨ������Ч 
 *	 -3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int CheckBatchResult(SmartCom::string& retCode,int macNo=255);

/**
 * @brief ��SST25VF016B�洢��������Ƭ����
 * @param
 *	macNO	���ţ�Ĭ��255 
 * @return
 *	 0: �����ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int ClearMem(int macNo=255);