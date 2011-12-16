//////////////////////////////////////////////////////////////////////////
// FileName:	CardReaderClientDll.h
// Creator:		icejoywoo
// Date:		2011.12.03
// $Revision$
// Comment: �ͻ��˲����������Ľӿڶ���
//////////////////////////////////////////////////////////////////////////

#ifdef CARDREADERCLIENTDLL_EXPORTS
#define CARDREADERCLIENTDLL_API __declspec(dllexport)
#else
#define CARDREADERCLIENTDLL_API __declspec(dllimport)
#endif

#include <WINSOCK2.H> // win socket
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
 * @brief ���������id������������ӵ�socket
 *
 * ͨ��������id��socket�İ�, ���Է������, �鿴��ǰ������id
 */
typedef struct _Reader
{
	SOCKET s;
	int readerId;
} Reader;

/**
 * @brief ��ʼ���ͻ��˵ķ�����ȫ������, Reader������Щ���ý������������ͨ��
 * @param
 *	serverIp	������ip
 *	serverPort	�������˿ں�
 * @return 
 *	�ɹ�����0
 */
CARDREADERCLIENTDLL_API int InitClient(char* serverIp, int serverPort);

/**
 * @brief ����ͻ���, ��ʹ�����������������
 * @param None
 * @return 
 *	�ɹ�����0
 */
CARDREADERCLIENTDLL_API int CleanUpClient();

/**
 * @brief ��ȡ������
 * @param
 *	reader			�������, ������
 *	socketTimeout	socket���ӵĳ�ʱ
 *	customTimeout	Ӧ�ñ�����Ҫ����ʱ
 * @return  
 *	0: �ɹ�
 */
CARDREADERCLIENTDLL_API int GetReader(Reader* reader, long socketTimeout = 5000, long customTimeout = 60000);

/**
 * @brief �ͷŶ�����
 * @param
 *	reader			������
 * @return  
 *	0: �ɹ�
 */
CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader);

/**
 * @brief ��ȡ�ն��豸id�źͻ���
 * @param 
 *	reader			������, ʹ��reader���ͷ�����ͨ��
 *	devID			�������, ���7�ֽ�id��
 *	devIDBufLen		devID����ĳ���
 *	readerMacId		�������, 1�ֽڻ���(������Ų���readerId, �벻Ҫ����, Ϊ������չ��������׼����)
 * @return 
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetDevIDAndReaderId(Reader* reader, char* devID, int devIDBufLen, int& readerMacId);

/**
 * @brief ͨ���ն��豸ID�Ÿ��ն��豸���û���
 * @param
 *	reader		������, ʹ��reader���ͷ�����ͨ��
 *	devID		���7���ֽڵ��豸ID
 *	readerMacId	Ҫ���õĻ���(������Ų���readerId, �벻Ҫ����, Ϊ������չ��������׼����)
 * @return
 *	 0: ���óɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int SetReaderIdByDevID(Reader* reader, const char* devID, int readerMacId);


/**
 * @brief ��ȡ����汾���ն�����
 * @param
 *	reader			������
 *	appVer			����汾
 *	appVerlen		���appVersion�Ļ��峤��
 *	devType			�ն�����
 *	devTypeLen		����ն����͵Ļ��峤��
 * @return
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetAppVerAndDevType(Reader* reader, char* appVer, int appVerlen, char* devType, int devTypeLen);

/**
 * @brief ��λ�ն��豸(��ʱ����, ��Ҫʹ��, ��ʹ��ResetCard���������и�λ)
 * @param
 *	reader		������
 * @return
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int ResetDev(Reader* reader);

/** 
 * @brief ��ȡ�����ӿ�оƬID��
 * @param
 *	reader			������
 *	chipID			�ӿ�оƬID
 *	chipIDLen		��Žӿ�оƬID�Ļ��泤��
 * @return 
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetChipID(Reader* reader, char* chipID, int chipIDLen);

/**
 * @brief ���A�����󿨣�����B����SIM�������Ƿ��п�
 * @param
 *	reader		������
 *	cardA		���ڲ���, 1,A�����п���0��A�����޿�
 *	cardB		���ڲ���, 1,B�����п���0��B�����޿�
 * @return 
 *	 0: ���ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ���ʧ��
 */
CARDREADERCLIENTDLL_API int IsCardReady(Reader* reader, int& cardA,int& cardB);

/**
 * @brief ��Ƭ��λӦ��
 * @param
 *	reader			������
 *	card			1:A����2��B��,Ĭ��ѡ��A��
 *	retCode			���ڲ���, ��λ����ķ���ֵ
 *		retCode="F9"�������޿�
 *		retCode="FD"������ʶ��
 *	����ֵ��
 *	0��ͨ�ųɹ�
 *	-1��ͨ�ų�ʱ����
 *	-2��ͨ������Ч  
 *	-3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int ResetCard(Reader* reader, SmartCom::string& retCode,int card = 1);

/**
 * @brief ��Ƭ����-APDU
 * @param
 *	reader			������
 *	apdu			ʮ�������ַ�����ʾ��apdu����
 *	card			1:A����2��B��,Ĭ��ѡ��A��
 *	readerId		���ţ�Ĭ��255
 *	retCode			���ڲ���, ִ��apduָ��ķ���ֵ
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
CARDREADERCLIENTDLL_API int CardApdu(Reader* reader, char* apdu, SmartCom::string& retCode,int card=1);

/**
 * @brief ��Ƭ�µ�
 * @param
 *	reader		������
 * @return
 *	 0: �µ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �µ�ʧ��
 */
CARDREADERCLIENTDLL_API int ShutdownCard(Reader* reader);

/**
 * @brief �޸Ŀ�ͨ�Ų�����
 * @param
 *	reader			������
 *	braudRate		Ҫ�޸ĵĲ����ʣ�ֻ��ѡ����ֵ��115200��57600��38400��28800��23040��19200��14400��12800��9600
 * @return
 *	 0: �޸ĳɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �޸�ʧ��
 */
CARDREADERCLIENTDLL_API int ModifyCardBraudRate(Reader* reader, int braudRate);

/**
 * @brief ����ͨ�Ų�����
 * @param
 *	reader			������
 *	braudRate		���ڲ���, ��ǰ����ͨ�Ų�����
 * @return
 *	 0: ��ȡ�ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetCardBraudRate(Reader* reader, int& braudRate);

/**
 * @brief �޸Ŀ�Ƭ��Դ
 * @param
 *	reader			������
 *	power			��Դ��power=1: 5v��power=2: 3v��power=3: 1.8v
 *	card			1:A����2��B��,Ĭ��ѡ��A��
 * @return
 *	 0: �޸ĳɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: �޸�ʧ��
 */
CARDREADERCLIENTDLL_API int ModifyCardPower(Reader* reader, int power,int card=1);

/**
 * @brief ����ִ��������APDU����
 * @param
 *	reader		������
 *	card		ѡ��ִ�еĿ���card=1ΪA����2ΪB����Ĭ��A��
 *	cmdNum		Ҫִ�е�ָ������
 * @return
 *	 0: �ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int  ExcuteMulAPDU(Reader* reader, int cmdNum,int card=1);

/**
 * @brief ������������ƽű��ļ�
 * @param
 *	reader			������
 *	bytes			Ҫ��ȡ���ֽ���
 *	readerId		���ţ�Ĭ��255 
 *	offset			��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
 *	strData			���ڲ���, ��ȡ��ת����ʮ�������ַ���������
 * @return
 *	  0: ��ȡ�ɹ�
 *	 -1: ͨ�ų�ʱ����
 *	 -2: ͨ������Ч
 *	 -3: ���ŷ�Χ����
 *	 -4: ��ȡʧ��
 */
CARDREADERCLIENTDLL_API int GetScriptData(Reader* reader, int offset,unsigned char bytes,SmartCom::string& strData);

/**
 * @brief �����ļ�
 * @param
 *	reader			������
 *	flag			flag=1,�����������ļ���flag=2����������ͷ�ļ�
 *	fileName		�ļ���
 * @return
 *	 0: ���سɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч 
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 *	-5: �ļ���ʧ��
 */
CARDREADERCLIENTDLL_API int DownloadFile(Reader* reader, int flag,const char* fileName);

/**
 * @brief ��ѯִ��������APDU���
 * @param
 *	reader			������
 *	retCode			���ڲ���, ���һ��ָ��ķ���ֵ 
 *		retCode="F1": δѡ�������޿��򿨸�λʧ��(����ʧЧ)��APDU��Ӧ��ʱ������Ч��APDU����ȴ���
 * @return
 *	>=0: �������Ѿ�ִ�е���������
 *	 -1: ͨ�ų�ʱ����
 *	 -2: ͨ������Ч 
 *	 -3: ���ŷ�Χ����
 */
CARDREADERCLIENTDLL_API int CheckBatchResult(Reader* reader, SmartCom::string& retCode);

/**
 * @brief ��SST25VF016B�洢��������Ƭ����
 * @param
 *	reader			������
 * @return
 *	 0: �����ɹ�
 *	-1: ͨ�ų�ʱ����
 *	-2: ͨ������Ч
 *	-3: ���ŷ�Χ����
 *	-4: ����ʧ��
 */
CARDREADERCLIENTDLL_API int ClearMem(Reader* reader);