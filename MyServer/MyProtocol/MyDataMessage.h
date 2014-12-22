#ifndef _MYDATAMESSAGE_H
#define _MYDATAMESSAGE_H

#include "Symbols.h"
#include "MyMessage.h"

enum MainCMDEnum
{
	MC_Manager = 0
};

enum ManagerSubCMDEnum
{
	M_SC_Heartbeat = 0
};

struct MYPROTOCOL_API FCIIContent
{
	UINT16	Identify;
	UINT16	CheckSum;
	UINT16	MainCMD;
	UINT16	SubCMD;
	UINT16	IsRequest;
	UINT16	ErrCode;
	UINT16	NextIdentify;
	UINT16	Reserve;
	UINT32	DataLen;
	char	Data;
};

class MYPROTOCOL_API MyDataMessage : public MyMessage
{
	friend class WebsocketDataMessage;
	friend class MyHeartbeatMessage;
public:
	const static int CONTENTLEN = sizeof(FCIIContent)-sizeof(char*);

	MyDataMessage(int serviceId, int type = DataMessage);
	MyDataMessage(const char* buffer, int bufLen, int serviceId, int type = DataMessage);
	~MyDataMessage();
public:
	void SetServiceId(int serviceId);
	int GetServiceId();

	bool IsEnd();

	char* GetContentData();

	//bool Encode();
	//bool Decode();
	FCIIContent* GetEncodedData()
	{
		//如果是多包的组合则只获得第一个包
		return mContent;
	}
	int GetBufLen();

	static bool IsMyDataMessage(const char* buffer,int bLen);
private:
	int mServiceId;
	char* mBuffer;
	int mBLen;

	FCIIContent* mContent;

	char* mDataBuf;
};

#endif