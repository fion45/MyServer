#pragma once
#include "Symbols.h"
#include "MyMessage.h"

struct FCIIContent
{
	unsigned short	Identify;
	unsigned short	CheckSum;
	unsigned short	MainCMD;
	unsigned short	SubCMD;
	unsigned short	IsRequest;
	unsigned short	ErrCode;
	unsigned int	DataLen;
	char*	Data;
};

class MYPROTOCOL_API MyDataMessage : public MyMessage
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

