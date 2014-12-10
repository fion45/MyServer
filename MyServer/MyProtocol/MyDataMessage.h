#pragma once
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
	UINT8*	Data;
};

class MyDataMessage : public MyMessage
{
public:
	MyDataMessage(const char* buffer, int serviceId, int type = DataMessage);
	~MyDataMessage();

	int GetServiceId();
	void SetServiceId(int serviceId);

	bool Encode();
	bool Decode();
	FCIIContent* GetEncodedData();

	static bool IsMyDataMessage(const char* buffer,int bLen);
private:
	int mServiceId;
	char* mBuffer;
	int mBLen;
};

