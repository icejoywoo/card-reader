//////////////////////////////////////////////////////////////////////////
// FileName: ClientConnection.h
// Creator: icejoywoo
// Date: 2011.11.29
// $Revision: 12 $
// $LastChangedDate: 2011-11-30 09:45:44 +0800 (å‘¨ä¸‰, 30 åä¸€æœˆ 2011) $
// Comment: ¿Í»§¶ËÓÃÀ´Á¬½Óµ½·şÎñÆ÷µÄ·â×°, ²¢·¢ËÍÊı¾İ, Ä¬ÈÏ¿ªÆôÈÕÖ¾¼ÇÂ¼
//////////////////////////////////////////////////////////////////////////
#ifndef _CLIENTCONNECTION_H_
#define _CLIENTCONNECTION_H_

#include "StdAfx.h"

class ClientConnection
{
public:
	ClientConnection(char* servername, int p, int id);
	~ClientConnection();
	/**
	 * @brief ·¢ËÍÊı¾İ
	 * @param data Òª·¢ËÍµÄÊı¾İ
	 * @return ·¢ËÍ³É¹¦µÄÊı¾İ³¤¶È
	 */
	int recvData(char* data);
	/**
	 * @brief ²é¿´µ±Ç°ÈÕÖ¾×´Ì¬
	 * @return Èç¹û¼ÇÂ¼ÈÕÖ¾, ·µ»Øtrue, ·ñÔò·µ»Øfalse
	 */
	bool isLogged();
	/**
	 * @brief ÉèÖÃÊÇ·ñ±£´æÈÕÖ¾
	 * @return None
	 */
	void setLog(bool log);
private:
	/**
	 * @brief »ñµÃ¶ÔÓ¦servernameµÄÖ÷»úµØÖ·
	 * @param server Ö÷»úµØÖ·
	 * @return None
	 */
	void getServerAddr(struct sockaddr_in& server);
private:
	WSADATA wsaData;
	int readerId; // ÇëÇóµÄ¶Á¿¨Æ÷id
	char* serverName;
	int port;
	bool isLog;
	SOCKET client;
};

#endif