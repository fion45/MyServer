#ifndef _MYDATAMESSAGE_H
#define _MYDATAMESSAGE_H

#include "Symbols.h"
#include "MyMessage.h"

struct FCIIContent
{
	UINT16	Identify;
	UINT16	CheckSum;
	UINT16	MainCMD;
	UINT16	SubCMD;
	UINT16	IsRequest;
	UINT16	ErrCode;
	UINT32	DataLen;
	char*	Data;
};

class MyDataMessage : public MyMessage
{
public:
	const static int CONTENTLEN = sizeof(FCIIContent)-sizeof(char*);

	MyDataMessage(const char* buffer, int serviceId, int type = DataMessage);
	~MyDataMessage();
public:
	void SetServiceId(int serviceId);
	int GetServiceId();

	bool Encode();
	bool Decode();
	FCIIContent* GetEncodedData();

	static bool IsMyDataMessage(const char* buffer,int bLen);
private:
	int mServiceId;
	char* mBuffer;
	int mBLen;
};

#endif